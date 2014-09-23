/**
 * @file api/folder/folder_delete.hpp
 * @brief API request: /api/folder/delete
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
/** API action path "folder" */
namespace folder {
/** API action "folder/folder_delete" */
namespace folder_delete {
/** API path "/api/folder/delete" */
namespace v0 {

enum class Asynchronous
{
    /** API value "no" */
    Synchronous,
    /** API value "yes" */
    Asynchronous
};

/**
 * @class Response
 * @brief Response from API request "folder/delete"
 */
class Response : public ResponseBase
{
public:
    Response() :
        asynchronous(Asynchronous::Synchronous)
    {}
    /** API response field "response.asynchronous" */
    Asynchronous asynchronous;

    /** API response field "response.device_revision" */
    uint32_t device_revision;
};

class Impl;

/**
 * @class Request
 * @brief Make API request "folder/delete"
 */
class Request
{
public:
    /**
     * API request "folder/delete"
     *
     * @param folderkeys API parameter "folder_key"
     */
    explicit Request(
            std::string folderkeys
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

}  // namespace folder_delete
}  // namespace folder
}  // namespace api
}  // namespace mf
