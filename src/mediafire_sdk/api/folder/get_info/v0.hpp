/**
 * @file api/folder/get_info.hpp
 * @brief API request: /api/folder/get_info
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
/** API action "folder/get_info" */
namespace get_info {
/** API path "/api/folder/get_info" */
namespace v0 {

enum class Details
{
    /** API value "no" */
    NoDetails,
    /** API value "yes" */
    FullDetails,
    /** API value "shallow" */
    ShallowDetails
};

enum class FileDrop
{
    /** API value "no" */
    Disabled,
    /** API value "yes" */
    Enabled
};

enum class SharedByUser
{
    /** API value "" */
    Unshared,
    /** API value "1" */
    Shared
};

/**
 * @class Response
 * @brief Response from API request "folder/get_info"
 */
class Response : public ResponseBase
{
public:
    Response() :
        created_datetime(boost::posix_time::not_a_date_time),
        deleted_datetime(boost::posix_time::not_a_date_time),
        shared_by_user(SharedByUser::Unshared)
    {}
    /** API response field "response.folder_info.folderkey" */
    std::string folderkey;

    /** API response field "response.folder_info.name" */
    std::string name;

    /** API response field "response.folder_info.description" */
    boost::optional<std::string> description;

    /** API response field "response.folder_info.created" */
    boost::posix_time::ptime created_datetime;

    /** API response field "response.folder_info.delete_date" */
    boost::posix_time::ptime deleted_datetime;

    /** API response field "response.folder_info.parent_folderkey" */
    boost::optional<std::string> parent_folderkey;

    /** API response field "response.folder_info.custom_url" */
    boost::optional<std::string> custom_url;

    /** API response field "response.folder_info.dropbox_enabled" */
    boost::optional<FileDrop> filedrop;

    /** API response field "response.folder_info.file_count" */
    uint32_t file_count;

    /** API response field "response.folder_info.folder_count" */
    uint32_t folder_count;

    /** API response field "response.folder_info.size" */
    boost::optional<uint64_t> size;

    /** API response field "response.folder_info.total_folders" */
    boost::optional<uint32_t> total_folders;

    /** API response field "response.folder_info.total_files" */
    boost::optional<uint32_t> total_files;

    /** API response field "response.folder_info.total_size" */
    boost::optional<uint64_t> total_size;

    /** API response field "response.folder_info.shared_by_user" */
    SharedByUser shared_by_user;

    /** API response field "response.folder_info.permissions" */
    boost::optional<uint32_t> permissions;

    /** API response field "response.folder_info.owner_name" */
    boost::optional<std::string> owner_name;

    /** API response field "response.folder_info.avatar" */
    boost::optional<std::string> avatar;

    /** API response field "response.folder_info.flag" */
    uint32_t flag;

    /** API response field "response.folder_info.revision" */
    uint32_t revision;
};

class Impl;

/**
 * @class Request
 * @brief Make API request "folder/get_info"
 */
class Request
{
public:
    /**
     * API request "folder/get_info"
     *
     * @param folderkey API parameter "folder_key"
     */
    explicit Request(
            std::string folderkey
        );

    /**
     * Optional API parameter "details"
     *
     * @param details Set parameter "details" in API request.
     */
    void SetDetails(Details details);

    /**
     * Optional API parameter "device_id"
     *
     * @param device_id Set parameter "device_id" in API request.
     */
    void SetDeviceId(uint32_t device_id);

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

}  // namespace get_info
}  // namespace folder
}  // namespace api
}  // namespace mf
