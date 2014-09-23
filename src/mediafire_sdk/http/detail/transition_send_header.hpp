/**
 * @file transition_config.hpp
 * @author Herbert Jones
 * @brief Config state machine transitions
 * @copyright Copyright 2014 Mediafire
 *
 * Detailed message...
 */
#pragma once

#include <chrono>
#include <memory>
#include <sstream>

#include "boost/algorithm/string/case_conv.hpp"
#include "boost/algorithm/string/predicate.hpp"
#include "boost/asio.hpp"

#include "mediafire_sdk/http/error.hpp"
#include "mediafire_sdk/http/url.hpp"
#include "mediafire_sdk/http/detail/http_request_events.hpp"
#include "mediafire_sdk/http/detail/race_preventer.hpp"
#include "mediafire_sdk/http/detail/types.hpp"

namespace mf {
namespace http {
namespace detail {

using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

template <typename FSM>
void HandleHeaderWrite(
        std::shared_ptr<FSM> fsmp,
        RacePreventer race_preventer,
        const TimePoint start_time,
        const std::size_t bytes_transferred,
        const boost::system::error_code& err
    )
{
    using mf::http::http_error;

    // Skip if cancelled due to timeout.
    if ( ! race_preventer.IsFirst() ) return;

    fsmp->ClearAsyncTimeout();  // Must stop timeout timer.

    if (fsmp->get_bw_analyser())
    {
        fsmp->get_bw_analyser()->RecordOutgoingBytes( bytes_transferred, start_time,
            sclock::now() );
    }

    if (!err)
    {
        fsmp->ProcessEvent(HeadersWrittenEvent{});
    }
    else
    {
        std::stringstream ss;
        ss << "Failure while writing headers url(" << fsmp->get_url() << ").";
        ss << " Error: " << err.message();
        fsmp->ProcessEvent(
            ErrorEvent{
                make_error_code(
                    http_error::WriteFailure ),
                ss.str()
            });
    }
}

struct SendHeaderAction
{
    template <typename Event, typename FSM,typename SourceState,typename TargetState>
    void operator()(
            Event const & /*evt*/,
            FSM & fsm,
            SourceState&,
            TargetState&
        )
    {
        const Url * url = fsm.get_parsed_url();

        assert(url);

        const bool is_ssl = fsm.get_is_ssl();

        // When a proxy is used, the full path must be sent.
        std::string path = url->full_path();
        if (     ( is_ssl && fsm.get_https_proxy() )
            || ( ! is_ssl && fsm.get_http_proxy() ) )
        {
            path = url->url();
        }

        std::ostringstream request_stream_local;
        request_stream_local << fsm.get_request_method() << " "
            << path << " HTTP/1.1\r\n";
        request_stream_local << "Host: " << url->host() << "\r\n";

        if ( ! is_ssl && fsm.get_http_proxy()
            && ! fsm.get_http_proxy()->username.empty() )
        {
            std::string to_encode = fsm.get_http_proxy()->username;
            to_encode += ':';
            to_encode += fsm.get_http_proxy()->password;
            std::string encoded = mf::utils::Base64Encode(
                    to_encode.c_str(), to_encode.size() );

            request_stream_local << "Proxy-Authorization: Basic " << encoded
                << "\r\n";
        }

        for ( const auto & pair : fsm.get_headers() )
        {
            if ( is_ssl && boost::iequals(pair.first, "accept-encoding" ) )
            {
                // Compression over SSL is not allowed as it is a vulnerability.
                // See BREACH.
                continue;
            }

            request_stream_local
                << pair.first << ": "  // name
                << pair.second  // value
                << "\r\n";  // HTTP header newline
        }

        request_stream_local << "\r\n";  // End header with blank line.

        std::shared_ptr<boost::asio::streambuf> request(
            std::make_shared<boost::asio::streambuf>());

        std::ostream request_stream(request.get());
        request_stream << request_stream_local.str();

        // Must prime timeout for async actions.
        auto race_preventer = fsm.SetAsyncTimeout("write request header",
            fsm.get_timeout_seconds());
        auto fsmp = fsm.AsFrontShared();
        auto start_time = sclock::now();

        boost::asio::async_write(
            *fsm.get_socket_wrapper(),
            *request,
            [fsmp, race_preventer, request, start_time](
                   const boost::system::error_code& ec,
                   std::size_t bytes_transferred
                )
            {
                // request passed to prevent it from getting freed
                HandleHeaderWrite(fsmp, race_preventer, start_time,
                    bytes_transferred, ec);
            });
    }
};

}  // namespace detail
}  // namespace http
}  // namespace mf