/**
 * @file get_foreign_resources.cpp
 *
 * @copyright Copyright 2014 Mediafire
 *
 * This file was generated by gen_api_template.py. Do NOT edit by hand.
 */
// #define OUTPUT_DEBUG
#include "v0.hpp"

#include <string>

#include "mediafire_sdk/api/error.hpp"
#include "mediafire_sdk/api/ptree_helpers.hpp"
#include "mediafire_sdk/utils/string.hpp"
#include "mediafire_sdk/api/session_token_api_base.hpp"

#include "boost/property_tree/json_parser.hpp"

namespace v0 = mf::api::device::get_foreign_resources::v0;


namespace {
std::string AsString(const v0::ContentType & value)
{
    if (value == v0::ContentType::Folders)
        return "folders";
    if (value == v0::ContentType::Files)
        return "files";
    return mf::utils::to_string(static_cast<uint32_t>(value));
}
std::string AsString(const v0::SyncToDesktopFilter & value)
{
    if (value == v0::SyncToDesktopFilter::All)
        return "0";
    if (value == v0::SyncToDesktopFilter::DesktopSyncedOnly)
        return "1";
    return mf::utils::to_string(static_cast<uint32_t>(value));
}
}  // namespace

#include "mediafire_sdk/api/type_helpers.hpp"

namespace {
// get_data_type_struct_extractor begin
using namespace v0;  // NOLINT
bool FileFromPropertyBranch(
        Response * response,
        Response::File * value,
        const boost::property_tree::wptree & pt
    )
{
#   define return_error(error_type, error_message)                             \
    {                                                                          \
        response->error_code = make_error_code( error_type );                  \
        response->error_string = error_message;                                \
        return false;                                                          \
    }
    using mf::api::GetIfExists;
    value->share_link_enabled = ShareLinkEnabled::LinkDisabled;

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "attributes",
            &value->attributes ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"attributes\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "created",
            &value->created_datetime ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"created\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "date_shared",
            &value->shared_datetime ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"date_shared\"");

    // create_content_parse_single optional no default
    {
        std::string optarg;
        if ( GetIfExists(
                pt,
                "desc",
                &optarg) )
        {
            value->description = optarg;
        }
    }

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "filename",
            &value->filename ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"filename\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "filetype",
            &value->filetype ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"filetype\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "md5",
            &value->hash ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"md5\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "mimetype",
            &value->mimetype ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"mimetype\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "options",
            &value->options ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"options\"");

    // create_content_parse_single optional no default
    {
        uint32_t optarg;
        if ( GetIfExists(
                pt,
                "permissions",
                &optarg) )
        {
            value->permissions = optarg;
        }
    }

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "quickkey",
            &value->quickkey ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"quickkey\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "revision",
            &value->revision ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"revision\"");

    {
        std::string optval;
        // create_content_enum_parse TSingle
        if ( GetIfExists(
                pt,
                "share_link_enabled",
                &optval) )
        {
            if ( optval == "0" )
                value->share_link_enabled = ShareLinkEnabled::LinkDisabled;
            else if ( optval == "1" )
                value->share_link_enabled = ShareLinkEnabled::LinkEnabled;
        }
    }

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "sharer",
            &value->sharer ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"sharer\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "size",
            &value->filesize ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"size\"");

    // get_data_type_struct_extractor conclusion
    return true;
#   undef return_error
}
// get_data_type_struct_extractor begin
using namespace v0;  // NOLINT
bool FolderFromPropertyBranch(
        Response * response,
        Response::Folder * value,
        const boost::property_tree::wptree & pt
    )
{
#   define return_error(error_type, error_message)                             \
    {                                                                          \
        response->error_code = make_error_code( error_type );                  \
        response->error_string = error_message;                                \
        return false;                                                          \
    }
    using mf::api::GetIfExists;
    value->share_link_enabled = ShareLinkEnabled::LinkDisabled;

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "attributes",
            &value->attributes ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"attributes\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "created",
            &value->created_datetime ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"created\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "date_shared",
            &value->shared_datetime ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"date_shared\"");

    // create_content_parse_single optional no default
    {
        std::string optarg;
        if ( GetIfExists(
                pt,
                "desc",
                &optarg) )
        {
            value->description = optarg;
        }
    }

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "folderkey",
            &value->folderkey ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"folderkey\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "name",
            &value->name ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"name\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "options",
            &value->options ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"options\"");

    // create_content_parse_single optional no default
    {
        uint32_t optarg;
        if ( GetIfExists(
                pt,
                "permissions",
                &optarg) )
        {
            value->permissions = optarg;
        }
    }

    // create_content_parse_single optional no default
    {
        std::string optarg;
        if ( GetIfExists(
                pt,
                "resource_key",
                &optarg) )
        {
            value->resource_key = optarg;
        }
    }

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "revision",
            &value->revision ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"revision\"");

    {
        std::string optval;
        // create_content_enum_parse TSingle
        if ( GetIfExists(
                pt,
                "share_link_enabled",
                &optval) )
        {
            if ( optval == "0" )
                value->share_link_enabled = ShareLinkEnabled::LinkDisabled;
            else if ( optval == "1" )
                value->share_link_enabled = ShareLinkEnabled::LinkEnabled;
        }
    }

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "sharer",
            &value->sharer ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"sharer\"");

    // get_data_type_struct_extractor conclusion
    return true;
#   undef return_error
}
}  // namespace

namespace mf {
namespace api {
/** API action path "device" */
namespace device {
namespace get_foreign_resources {
namespace v0 {

const std::string api_path("/api/device/get_foreign_resources");

// Impl ------------------------------------------------------------------------

class Impl : public SessionTokenApiBase<Response>
{
public:
    Impl(
            uint32_t chunk_number,
            ContentType content_type
        );

    uint32_t chunk_number_;
    ContentType content_type_;
    boost::optional<std::string> filter_;
    boost::optional<SyncToDesktopFilter> sync_to_desktop_filter_;
    virtual void BuildUrl(
        std::string * path,
        std::map<std::string, std::string> * query_parts
    ) const override;

    virtual void ParseResponse( Response * response ) override;

    mf::http::SharedBuffer::Pointer GetPostData();

    mf::api::RequestMethod GetRequestMethod() const
    {
        return mf::api::RequestMethod::Post;
    }
};

Impl::Impl(
        uint32_t chunk_number,
        ContentType content_type
    ) :
    chunk_number_(chunk_number),
    content_type_(content_type)
{
}

void Impl::BuildUrl(
            std::string * path,
            std::map<std::string, std::string> * query_parts
    ) const
{
    *path = api_path + ".php";
}

void Impl::ParseResponse( Response * response )
{
    // This function uses return defines for readability and maintainability.
#   define return_error(error_type, error_message)                             \
    {                                                                          \
        SetError(response, error_type, error_message);                         \
        return;                                                                \
    }

    // create_content_struct_parse TArray
    try {
        const boost::property_tree::wptree & branch =
            response->pt.get_child(L"response.files");
        response->files.reserve( response->pt.size() );

        for ( auto & it : branch )
        {
            Response::File optarg;
            if ( FileFromPropertyBranch(
                    response, &optarg, it.second) )
                response->files.push_back(std::move(optarg));
        }
    }
    catch(boost::property_tree::ptree_bad_path & err)
    {
        // Is optional
    }

    // create_content_struct_parse TArray
    try {
        const boost::property_tree::wptree & branch =
            response->pt.get_child(L"response.folders");
        response->folders.reserve( response->pt.size() );

        for ( auto & it : branch )
        {
            Response::Folder optarg;
            if ( FolderFromPropertyBranch(
                    response, &optarg, it.second) )
                response->folders.push_back(std::move(optarg));
        }
    }
    catch(boost::property_tree::ptree_bad_path & err)
    {
        // Is optional
    }

#   undef return_error
}

mf::http::SharedBuffer::Pointer Impl::GetPostData()
{
    std::map<std::string, std::string> parts;

    parts["chunk"] = AsString(chunk_number_);
    parts["type"] = AsString(content_type_);
    if (filter_)
        parts["filter"] = *filter_;
    if (sync_to_desktop_filter_)
        parts["sync"] = AsString(*sync_to_desktop_filter_);

    std::string post_data = MakePost(api_path + ".php", parts);
    AddDebugText(" POST data: " + post_data + "\n");
    return mf::http::SharedBuffer::Create(post_data);
}

// Request ---------------------------------------------------------------------

Request::Request(
        uint32_t chunk_number,
        ContentType content_type
    ) :
    impl_(new Impl(chunk_number, content_type))
{
}

void Request::SetCallback( CallbackType callback_function )
{
    impl_->SetCallback(callback_function);
}

void Request::HandleContent(
        const std::string & url,
        const mf::http::Headers & headers,
        const std::string & content
    )
{
    impl_->HandleContent(url, headers, content);
}

void Request::HandleError(
        const std::string & url,
        std::error_code ec,
        const std::string & error_string
    )
{
    impl_->HandleError(url, ec, error_string);
}

std::string Request::Url(const std::string & hostname) const
{
    return impl_->Url(hostname);
}

void Request::SetSessionToken(
        std::string session_token,
        std::string time,
        int secret_key
    )
{
    impl_->SetSessionToken(session_token, time, secret_key);
}

void Request::SetFilter(std::string filter)
{
    impl_->filter_ = filter;
}

void Request::SetSyncToDesktopFilter(SyncToDesktopFilter sync_to_desktop_filter)
{
    impl_->sync_to_desktop_filter_ = sync_to_desktop_filter;
}

mf::http::SharedBuffer::Pointer Request::GetPostData()
{
    return impl_->GetPostData();
}

}  // namespace v0
}  // namespace get_foreign_resources
}  // namespace device
}  // namespace api
}  // namespace mf