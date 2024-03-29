/**
 * @file api/file/get_links.hpp
 * @brief API request: /api/file/get_links
 *
 * @copyright Copyright 2014 Mediafire
 *
 * This file was generated by gen_api_template.py. Do NOT edit by hand.
 */
#pragma once

#include <set>
#include <string>
#include <vector>

#include "mediafire_sdk/http/shared_buffer.hpp"
#include "mediafire_sdk/http/headers.hpp"
#include "mediafire_sdk/api/response_base.hpp"

#include "boost/date_time/posix_time/ptime.hpp"

namespace mf {
namespace api {
/** API action path "file" */
namespace file {
/** API action "file/get_links" */
namespace get_links {
/** API path "/api/file/get_links" */
namespace v0 {

enum class Recurring
{
    /** API value "0" */
    NonRecurring,
    /** API value "1" */
    Recurring
};

enum class LinkType
{
    /** API value "view" */
    View,
    /** API value "edit" */
    Edit,
    /** API value "listen" */
    Listen,
    /** API value "watch" */
    Watch,
    /** API value "normal_download" */
    NormalDownload,
    /** API value "direct_download" */
    DirectDownload,
    /** API value "one_time_download" */
    OneTimeDownload
};

/**
 * @class Response
 * @brief Response from API request "file/get_links"
 */
class Response : public ResponseBase
{
public:
    Response() :
        one_time_download_request_count(0),
        direct_download_free_bandwidth(0)
    {}
    struct Links
    {
        /** API response field "direct_download" */
        boost::optional<std::string> direct_download;

        /** API response field "direct_download_error_message" */
        boost::optional<std::string> direct_download_error_message;

        /** API response field "direct_download_error" */
        boost::optional<int32_t> direct_download_error;

        /** API response field "edit" */
        boost::optional<std::string> edit;

        /** API response field "edit_error_message" */
        boost::optional<std::string> edit_error_message;

        /** API response field "listen" */
        boost::optional<std::string> listen;

        /** API response field "normal_download" */
        boost::optional<std::string> normal_download;

        /** API response field "one_time_download" */
        boost::optional<std::string> one_time_download;

        /** API response field "one_time_download_error_message" */
        boost::optional<std::string> one_time_download_error_message;

        /** API response field "quickkey" */
        std::string quickkey;

        /** API response field "view" */
        boost::optional<std::string> view;

        /** API response field "watch" */
        boost::optional<std::string> watch;

        /** API response field "error" */
        boost::optional<std::string> error;
    };
    /** API response field "response.links" */
    std::vector<Links> links;

    /** API response field "response.one_time_download_request_count" */
    uint32_t one_time_download_request_count;

    /** API response field "response.direct_download_free_bandwidth" */
    uint32_t direct_download_free_bandwidth;
};

class Impl;

/**
 * @class Request
 * @brief Make API request "file/get_links"
 */
class Request
{
public:
    /**
     * API request "file/get_links"
     *
     * @param quickkeys API parameter "quick_key"
     */
    explicit Request(
            std::vector<std::string> quickkeys
        );

    /**
     * Optional API parameter "link_type"
     *
     * @param link_types Set parameter "link_type" in API request.
     */
    void SetLinkTypes(std::set<LinkType> link_types);

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

}  // namespace get_links
}  // namespace file
}  // namespace api
}  // namespace mf
