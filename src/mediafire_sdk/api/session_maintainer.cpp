/**
 * @file session_maintainer.cpp
 * @author Herbert Jones
 *
 * @copyright Copyright 2014 Mediafire
 */
#include "session_maintainer.hpp"

#include <algorithm>
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "boost/variant/apply_visitor.hpp"
#include "boost/variant/get.hpp"

#include "mediafire_sdk/api/detail/session_maintainer_locker.hpp"
#include "mediafire_sdk/api/error.hpp"
#include "mediafire_sdk/utils/variant_comparison.hpp"

#if ! defined(NDEBUG)
// Counter to keep track of number of HttpRequests
boost::atomic<int> mf::api::detail::session_maintainer_request_count(0);
#endif

namespace hl = mf::http;

using mf::api::detail::STRequest;
using mf::api::detail::SessionMaintainerRequest;

namespace {
namespace session_state = mf::api::session_state;
using mf::api::SessionState;

#ifdef OUTPUT_DEBUG // Debug code
std::ostream& operator<<(
        std::ostream& out,
        const mf::api::SessionState & state
    )
{
    class DebugVisitor : public boost::static_visitor<std::string>
    {
    public:
        std::string operator()(session_state::Uninitialized) const
        {
            return "session_state::Uninitialized";
        }

        std::string operator()(session_state::Initialized) const
        {
            return "session_state::Initialized";
        }

        std::string operator()(session_state::CredentialsFailure) const
        {
            return "session_state::CredentialsFailure";
        }

        std::string operator()(session_state::Running) const
        {
            return "session_state::Running";
        }
    };

    out << boost::apply_visitor( DebugVisitor(), state );
    return out;
}
#endif

bool IsInitialized(const SessionState & state)
{
    return (boost::get<session_state::Initialized>(&state));
}
bool IsRunning(const SessionState & state)
{
    return (boost::get<session_state::Running>(&state));
}
}  // namespace

namespace mf {
namespace api {

SessionMaintainer::SessionMaintainer(
        mf::http::HttpConfig::ConstPointer http_config
    ) : SessionMaintainer(http_config, "www.mediafire.com")
{
}

SessionMaintainer::SessionMaintainer(
        mf::http::HttpConfig::ConstPointer http_config,
        std::string hostname
    ) :
    locker_(
        new detail::SessionMaintainerLocker(
            http_config->GetWorkIoService(),
            http_config->GetDefaultCallbackIoService(),
            [this](
                    STRequest request,
                    const std::error_code & ec
                )
            {
                if (!ec)
                    AddWaitingRequest(request);
            })),
    http_config_(http_config),
    session_token_failure_timer_(*http_config_->GetWorkIoService()),
    requester_(http_config_, hostname),
    timeout_seconds_(60),
    is_running_(std::make_shared<Running>(Running::Yes))
{
    assert(http_config);

    auto running_ptr = is_running_;

    // Setup request callbacks
    on_stop_request_callback_ = [this, running_ptr](
            detail::STRequest request,
            ResponseBase * response
        )
    {
        if (*running_ptr == Running::Yes)
            HandleCompletion(request, response);
        else
            request->Cancel();
    };

    on_retry_request_callback_ = [this, running_ptr](
            detail::STRequest request,
            ResponseBase * response
        )
    {
        if (*running_ptr == Running::Yes)
            HandleRetryRequest(request, response);
        else
            request->Cancel();
    };

    info_update_callback_ = [this, running_ptr](
            detail::STRequest request,
            ResponseBase * response
        )
    {
        if (*running_ptr == Running::Yes)
            HandleCompletionNotification(request, response);
    };
}

SessionMaintainer::~SessionMaintainer()
{
    *is_running_ = Running::No;
    session_token_failure_timer_.cancel();
}

void SessionMaintainer::SetLoginCredentials(
        const Credentials & credentials
    )
{
    locker_->SetCredentials(credentials);

    // Credentials updated.  There may be requests ready to send.
    AttemptRequests();
}

void SessionMaintainer::HandleCompletion(
        STRequest request,
        ResponseBase * response
    )
{
    locker_->RemoveInProgressRequest(request);

    // Reuse token later if possible
    if ( IsInvalidSessionTokenError(response->error_code) )
        locker_->DeleteCheckedOutToken(request);
    else
        locker_->ReuseToken(request, response);

    // Request done, start another if possible
    AttemptRequests();
}

void SessionMaintainer::HandleRetryRequest(
        STRequest request,
        ResponseBase * response
    )
{
    // Put the request back on the queue. Give it a new token when available.
    {
        if ( IsInvalidSessionTokenError(response->error_code) )
        {   // Token invalid- delete it
            locker_->MoveInProgressToWaiting( request );
            locker_->DeleteCheckedOutToken( request );
        }
        else
        {   // Reuse token later
            locker_->MoveInProgressToDelayed(request, 1);
            locker_->ReuseToken(request, response);
        }
    }

    // Request done, start another if possible
    AttemptRequests();
}

void SessionMaintainer::HandleCompletionNotification(
        STRequest /* request */,
        ResponseBase * response
    )
{
    UpdateStateFromErrorCode(response->error_code);
}

void SessionMaintainer::UpdateStateFromErrorCode(
        const std::error_code & ec
    )
{
    using hl::http_error;

    if (ec)
    {
        if ( ec.category() == hl::http_category()
            && (    ec == http_error::UnableToConnect
                ||  ec == http_error::UnableToConnectToProxy
                ||  ec == http_error::UnableToResolve
                ||  ec == http_error::SslHandshakeFailure
                ||  ec == http_error::WriteFailure
                ||  ec == http_error::ReadFailure
                ||  ec == http_error::ProxyProtocolFailure
                ||  ec == http_error::IoTimeout
            ))
        {
            connection_state::Unconnected new_state = {ec};

            SetConnectionState(new_state);
        }
        else
        {
            SetConnectionState(connection_state::Connected());
        }
    }
    else
    {
        SetConnectionState(connection_state::Connected());
    }
}

#ifdef OUTPUT_DEBUG
#  define ATTEMPT_REQUEST_DEBUG(x) std::cout << "SessionMaintainer::AttemptRequests: " << x;
#else
#  define ATTEMPT_REQUEST_DEBUG(x)
#endif
void SessionMaintainer::AttemptRequests()
{
    ATTEMPT_REQUEST_DEBUG("-- BEGIN --\n")
    // Handle requests that do not use session tokens.
    boost::optional< STRequest > opt_request;
    while ( (opt_request = locker_->NextWaitingNonSessionTokenRequest()) )
    {
        STRequest & request = *opt_request;

        request->Init(&requester_);
        locker_->AddInProgressRequest(std::move(request));
        ATTEMPT_REQUEST_DEBUG("Started non-session token request.\n")
    }

    // Handle requests that have session tokens.
    boost::optional< std::pair<STRequest, SessionTokenData> > request_pair;
    ATTEMPT_REQUEST_DEBUG("Session state: "
        << GetSessionState() << " is running: " << IsRunning(GetSessionState())
        << "\n")
    while ( IsRunning(GetSessionState())
        && (request_pair = locker_->NextWaitingSessionTokenRequest()) )
    {
        ATTEMPT_REQUEST_DEBUG("Found waiting session token request.\n")
        SessionTokenData & st = request_pair->second;
        STRequest & request = request_pair->first;

        request->SetSessionToken(
                st.session_token,
                st.time,
                st.secret_key
            );
        request->Init(&requester_);

        locker_->AddInProgressRequest(std::move(request), std::move(st));
        ATTEMPT_REQUEST_DEBUG("Started session token request.\n")
    }

    // Request more session tokens for those that need it.
    const boost::optional<Credentials> credentials( locker_->GetCredenials() );
    if (credentials)
    {
        while ( locker_->PermitSessionTokenCheckout() )
        {
            RequestSessionToken(*credentials);
            ATTEMPT_REQUEST_DEBUG("Requested session token.\n")
        }
    }
    else
    {
        ATTEMPT_REQUEST_DEBUG("No credentials.\n")
    }

    ATTEMPT_REQUEST_DEBUG("-- END --\n")
}
#undef ATTEMPT_REQUEST_DEBUG

void SessionMaintainer::RequestSessionToken(
        const Credentials & credentials
    )
{
#   ifdef OUTPUT_DEBUG // Debug code
    std::cout << "SessionMaintainer: Requesting new session token."
        << std::endl;
#   endif

    auto running_ptr = is_running_;

    hl::HttpRequest::Pointer http_request =
        requester_.Call(
            user::get_session_token::Request(credentials),
            [this, running_ptr, credentials](
                    const user::get_session_token::Response & response
                )
            {
                if (*running_ptr == Running::Yes)
                    HandleSessionTokenResponse(response, credentials);
            },
            RequestStarted::No
        );

    // The timeout for these can be shorter.
    http_request->SetTimeout(15);

    http_request->Start();
}

void SessionMaintainer::HandleSessionTokenResponse(
        const user::get_session_token::Response & response,
        const Credentials & old_credentials
    )
{
    locker_->DecrementSessionTokenInProgressCount();

    SessionState session_state;
    uint32_t session_state_change_count;

    std::tie(session_state, session_state_change_count) =
        locker_->GetSessionState();

    UpdateStateFromErrorCode(response.error_code);

    if ( response.error_code )
    {
#       ifdef OUTPUT_DEBUG // Debug code
        std::cout << "SessionMaintainer: Session token request failed: "
            << response.error_code.message() << std::endl;
#       endif

        // Fail and set timeout before retry.
        session_token_failure_timer_.expires_from_now(
            boost::posix_time::milliseconds(
                session_token_failure_wait_timeout_ms) );

        session_token_failure_timer_.async_wait(
            boost::bind(
                &SessionMaintainer::HandleSessionTokenFailureTimeout,
                this,
                boost::asio::placeholders::error
            )
        );

        // If username or password is incorrect, stop.
        if ( IsInvalidCredentialsError(response.error_code) )
        {
            if (IsInitialized(session_state) || IsRunning(session_state))
            {
                // State is valid.

                const boost::optional<Credentials> credentials(
                    locker_->GetCredenials() );

                // Equality check ensures this isn't an old request
                if ( credentials &&
                    mf::utils::AreVariantsEqual(old_credentials, *credentials))
                {
                    session_state::CredentialsFailure new_state;
                    new_state.session_token_response = response;
                    new_state.error_code = response.error_code;

                    // If the pkey was sent, then the password may have been
                    // changed.  Let the class user figure this out if so.
                    if ( ! response.pkey.empty() )
                        new_state.pkey = response.pkey;

                    // This async call used the same credentials we currently
                    // have!  This means the username and password is bad.
                    locker_->SetSessionStateSafe(
                        new_state,
                        session_state_change_count
                        );
                }
            }
        }
    }
    else
    {
        // Session token is good.

#       ifdef OUTPUT_DEBUG // Debug code
        std::cout << "SessionMaintainer: Session token request success."
            << std::endl;
#       endif

        SessionTokenData st = {
            response.session_token,
            response.pkey,
            response.time,
            response.secret_key };

        if ( locker_->AddSessionToken(std::move(st), old_credentials) )
        {
            // Fix state if we are just starting.
            if (IsInitialized(session_state))
            {
                session_state::Running new_state = {response};

                locker_->SetSessionStateSafe(
                    new_state,
                    session_state_change_count );
            }
        }
        else
        {
#ifdef OUTPUT_DEBUG
            std::cout << "SessionMaintainer: Adding session token failed."
                << std::endl;
#endif
        }

        AttemptRequests();
    }
#ifdef OUTPUT_DEBUG
    std::cout << "SessionMaintainer: " << GetSessionState() << std::endl;
#endif
}

void SessionMaintainer::HandleSessionTokenFailureTimeout(
        const boost::system::error_code & err
    )
{
    if (!err)
    {
        AttemptRequests();
    }
}

void SessionMaintainer::AddWaitingRequest(
        STRequest request
    )
{
    locker_->AddWaitingRequest(request);
    AttemptRequests();
}

SessionState
SessionMaintainer::GetSessionState()
{
    return locker_->GetSessionState().first;
}

void SessionMaintainer::SetSessionState(SessionState state)
{
    return locker_->SetSessionState(state);
}

ConnectionState
SessionMaintainer::GetConnectionState()
{
    return locker_->GetConnectionState();
}

void SessionMaintainer::SetConnectionState(
        const ConnectionState & state
    )
{
    return locker_->SetConnectionState(state);
}

void SessionMaintainer::SetSessionStateChangeCallback(
        SessionStateChangeCallback callback
    )
{
    return locker_->SetSessionStateChangeCallback(callback);
}

void SessionMaintainer::SetConnectionStateChangeCallback(
        ConnectionStateChangeCallback callback
    )
{
    return locker_->SetConnectionStateChangeCallback(callback);
}

void SessionMaintainer::StopTimeouts()
{
    locker_->StopTimeouts();
}

}  // namespace api
}  // namespace mf
