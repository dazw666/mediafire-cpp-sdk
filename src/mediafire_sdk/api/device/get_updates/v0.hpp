/**
 * @file api/device/get_updates.hpp
 * @brief API request: /api/device/get_updates
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
/** API action "device/get_updates" */
namespace get_updates {
/** API path "/api/device/get_updates" */
namespace v0 {

/**
 * @class Response
 * @brief Response from API request "device/get_updates"
 */
class Response : public ResponseBase
{
public:
    struct Update
    {
        /** API response field "source_revision" */
        uint32_t source_revision;

        /** API response field "source_hash" */
        std::string source_hash;

        /** API response field "target_revision" */
        uint32_t target_revision;

        /** API response field "target_hash" */
        std::string target_hash;

        /** API response field "timestamp" */
        boost::posix_time::ptime timestamp;
    };
    /** API response field "response.current_revision" */
    uint32_t current_revision;

    /** API response field "response.updates" */
    std::vector<Update> updates;
};

class Impl;

/**
 * @class Request
 * @brief Make API request "device/get_updates"
 */
class Request
{
public:
    /**
     * API request "device/get_updates"
     *
     * @param quickkey API parameter "quick_key"
     * @param revision API parameter "revision"
     */
    Request(
            std::string quickkey,
            uint64_t revision
        );

    /**
     * Optional API parameter "target_revision"
     *
     * @param target_revision Set parameter "target_revision" in API request.
     */
    void SetTargetRevision(uint64_t target_revision);

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

}  // namespace get_updates
}  // namespace device
}  // namespace api
}  // namespace mf
