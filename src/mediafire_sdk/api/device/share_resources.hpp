/**
 * @file api/device/share_resources.hpp
 * @brief API request: /api/device/share_resources
 *
 * @copyright Copyright 2014 Mediafire
 *
 * This file was generated by gen_api_template.py. Do NOT edit by hand.
 */
#pragma once

#include <string>
#include <vector>

#include "mediafire_sdk/http/shared_buffer.hpp"
#include "mediafire_sdk/http/headers.hpp"
#include "mediafire_sdk/api/response_base.hpp"

#include "boost/date_time/posix_time/ptime.hpp"

namespace mf {
namespace api {
/** API action path "device" */
namespace device {
/** API action "device/share_resources" */
namespace share_resources {
/** API path "/api/device/share_resources" */
namespace v0 {

enum class Permissions
{
    /** API value "1" */
    Read,
    /** API value "2" */
    ReadWrite,
    /** API value "4" */
    Manage
};

/**
 * @class Response
 * @brief Response from API request "device/share_resources"
 */
class Response : public ResponseBase
{
public:
    /** API response field "response.device_revision" */
    uint32_t device_revision;
};

class Impl;

/**
 * @class Request
 * @brief Make API request "device/share_resources"
 */
class Request
{
public:
    /**
     * API request "device/share_resources"
     *
     * @param resources API parameter "resources"
     * @param contacts API parameter "contacts"
     */
    Request(
            std::string resources,
            std::string contacts
        );

    /**
     * Optional API parameter "permissions"
     *
     * @param permissions Set parameter "permissions" in API request.
     */
    void SetPermissions(Permissions permissions);

    /**
     * Optional API parameter "message"
     *
     * @param message Set parameter "message" in API request.
     */
    void SetMessage(std::string message);

    /**
     * Optional API parameter "fb_access_token"
     *
     * @param fb_access_token Set parameter "fb_access_token" in API request.
     */
    void SetFbAccessToken(std::string fb_access_token);

    /**
     * Optional API parameter "tw_oauth_token"
     *
     * @param tw_oauth_token Set parameter "tw_oauth_token" in API request.
     */
    void SetTwOauthToken(std::string tw_oauth_token);

    /**
     * Optional API parameter "tw_oauth_token_secret"
     *
     * @param tw_oauth_token_secret Set parameter "tw_oauth_token_secret" in API
     *                              request.
     */
    void SetTwOauthTokenSecret(std::string tw_oauth_token_secret);

    // Remaining functions are for use by API library only. --------------------

    /** Requester/SessionMaintainer expected type. */
    typedef Response ResponseType;

    /** Requester/SessionMaintainer expected type. */
    typedef std::function< void( const ResponseType & data)> CallbackType;

    /** Requester/SessionMaintainer expected type. */
    void SetCallback( CallbackType callback_function );

    /** Requester expected method. */
    void HandleContent(
            const std::string & url,
            const mf::http::Headers & headers,
            const std::string & content
        );

    /** Requester expected method. */
    void HandleError(
            const std::string & url,
            std::error_code ec,
            const std::string & error_string
        );

    /** Requester expected method. */
    std::string Url(const std::string & hostname) const;

    /** Requester optional method. */
    mf::http::SharedBuffer::Pointer GetPostData();

    /** SessionMaintainer expected method. */
    void SetSessionToken(
            std::string session_token,
            std::string time,
            int secret_key
        );
private:
    std::shared_ptr<Impl> impl_;
};
}  // namespace v0

// The latest version
using namespace v0;  // NOLINT

}  // namespace share_resources
}  // namespace device
}  // namespace api
}  // namespace mf
