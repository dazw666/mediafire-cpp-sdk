/**
 * @file api/upload/poll_upload.hpp
 * @brief API request: /api/upload/poll_upload
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
/** API action path "upload" */
namespace upload {
/** API action "upload/poll_upload" */
namespace poll_upload {
/** API path "/api/upload/poll_upload" */
namespace v0 {

/**
 * @class Response
 * @brief Response from API request "upload/poll_upload"
 */
class Response : public ResponseBase
{
public:
    Response() :
        fileerror(0)
    {}
    /** API response field "response.doupload.result" */
    int32_t result;

    /** API response field "response.doupload.status" */
    int32_t status;

    /** API response field "response.doupload.fileerror" */
    int32_t fileerror;

    /** API response field "response.doupload.description" */
    boost::optional<std::string> description;

    /** API response field "response.doupload.quickkey" */
    boost::optional<std::string> quickkey;

    /** API response field "response.doupload.size" */
    boost::optional<uint64_t> filesize;

    /** API response field "response.doupload.revision" */
    boost::optional<std::string> revision;
};

class Impl;

/**
 * @class Request
 * @brief Make API request "upload/poll_upload"
 */
class Request
{
public:
    /**
     * API request "upload/poll_upload"
     *
     * @param key API parameter "key"
     */
    explicit Request(
            std::string key
        );

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

}  // namespace poll_upload
}  // namespace upload
}  // namespace api
}  // namespace mf
