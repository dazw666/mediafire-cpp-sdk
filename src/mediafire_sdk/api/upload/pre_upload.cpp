/**
 * @file pre_upload.cpp
 *
 * @copyright Copyright 2014 Mediafire
 *
 * This file was generated by gen_api_template.py. Do NOT edit by hand.
 */
// #define OUTPUT_DEBUG
#include "pre_upload.hpp"

#include <string>

#include "mediafire_sdk/api/error.hpp"
#include "mediafire_sdk/api/ptree_helpers.hpp"
#include "mediafire_sdk/utils/string.hpp"
#include "mediafire_sdk/api/session_token_api_base.hpp"

#include "boost/property_tree/json_parser.hpp"

namespace v0 = mf::api::upload::pre_upload::v0;


namespace {
std::string AsString(const v0::Resumability & value)
{
    if (value == v0::Resumability::NotResumable)
        return "no";
    if (value == v0::Resumability::Resumable)
        return "yes";
    return mf::utils::to_string(static_cast<uint32_t>(value));
}
std::string AsString(const v0::ActionOnDuplicate & value)
{
    if (value == v0::ActionOnDuplicate::Skip)
        return "skip";
    if (value == v0::ActionOnDuplicate::Keep)
        return "keep";
    if (value == v0::ActionOnDuplicate::Replace)
        return "replace";
    return mf::utils::to_string(static_cast<uint32_t>(value));
}
}  // namespace

#include "mediafire_sdk/api/type_helpers.hpp"

namespace mf {
namespace api {
/** API action path "upload" */
namespace upload {
namespace pre_upload {
namespace v0 {

const std::string api_path("/api/upload/pre_upload");

// Impl ------------------------------------------------------------------------

class Impl : public SessionTokenApiBase<Response>
{
public:
    Impl();

    boost::optional<Resumability> resumable_;
    boost::optional<std::string> filename_;
    boost::optional<std::string> quickkey_;
    boost::optional<std::string> hash_;
    boost::optional<uint64_t> filesize_;
    boost::optional<std::string> upload_folder_key_;
    boost::optional<std::string> relative_path_;
    boost::optional<ActionOnDuplicate> action_on_duplicate_;
    boost::optional<boost::posix_time::ptime> mtime_;
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

Impl::Impl()
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

    {
        std::string optval;
        // create_content_enum_parse TSingle
        if ( GetIfExists(
                response->pt,
                "response.storage_limit_exceeded",
                &optval) )
        {
            if ( optval == "no" )
                response->storage_limit_exceeded = StorageLimit::WithinBounds;
            else if ( optval == "yes" )
                response->storage_limit_exceeded = StorageLimit::Exceeded;
        }
    }

    // create_content_parse_single optional no default
    {
        uint64_t optarg;
        if ( GetIfExists(
                response->pt,
                "response.storage_limit",
                &optarg) )
        {
            response->storage_limit = optarg;
        }
    }

    // create_content_parse_single optional no default
    {
        uint64_t optarg;
        if ( GetIfExists(
                response->pt,
                "response.used_storage_size",
                &optarg) )
        {
            response->used_storage_size = optarg;
        }
    }

    {
        std::string optval;
        // create_content_enum_parse TSingle
        if ( GetIfExists(
                response->pt,
                "response.new_hash",
                &optval) )
        {
            if ( optval == "no" )
                response->known_by_cloud = KnownByCloud::Known;
            else if ( optval == "yes" )
                response->known_by_cloud = KnownByCloud::Unknown;
        }
    }

    // create_content_parse_single optional no default
    {
        std::string optarg;
        if ( GetIfExists(
                response->pt,
                "response.quickkey",
                &optarg) )
        {
            response->quickkey = optarg;
        }
    }

    // create_content_parse_single optional no default
    {
        std::string optarg;
        if ( GetIfExists(
                response->pt,
                "response.duplicate_quickkey",
                &optarg) )
        {
            response->duplicate_quickkey = optarg;
        }
    }

    {
        std::string optval;
        // create_content_enum_parse TSingle
        if ( GetIfExists(
                response->pt,
                "response.duplicate_name",
                &optval) )
        {
            if ( optval == "no" )
                response->duplicate_name = DuplicateName::NoPreexistingName;
            else if ( optval == "yes" )
                response->duplicate_name = DuplicateName::DuplicateNameExists;
        }
    }

    // create_content_parse_single optional no default
    {
        std::string optarg;
        if ( GetIfExists(
                response->pt,
                "response.resumable_upload.upload_key",
                &optarg) )
        {
            response->upload_key = optarg;
        }
    }

    {
        std::string optval;
        // create_content_enum_parse TSingle
        if ( GetIfExists(
                response->pt,
                "response.resumable_upload.all_units_ready",
                &optval) )
        {
            if ( optval == "no" )
                response->all_units_ready = UnitsReady::NotReady;
            else if ( optval == "yes" )
                response->all_units_ready = UnitsReady::AllUnitsReady;
        }
    }

    // create_content_parse_single optional no default
    {
        uint32_t optarg;
        if ( GetIfExists(
                response->pt,
                "response.resumable_upload.number_of_units",
                &optarg) )
        {
            response->number_of_units = optarg;
        }
    }

    // create_content_parse_single optional no default
    {
        uint64_t optarg;
        if ( GetIfExists(
                response->pt,
                "response.resumable_upload.unit_size",
                &optarg) )
        {
            response->unit_size = optarg;
        }
    }

    // create_content_parse_single optional no default
    {
        uint32_t optarg;
        if ( GetIfExists(
                response->pt,
                "response.resumable_upload.bitmap.count",
                &optarg) )
        {
            response->bitmap_count = optarg;
        }
    }

    // create_content_parse_array TArray
    try {
        const boost::property_tree::wptree & branch =
            response->pt.get_child(L"response.resumable_upload.bitmap.words");
        response->bitmap_words.reserve( branch.size() );
        for ( auto & it : branch )
        {
            boost::optional<uint16_t> result =
                it.second.get_value_optional<uint16_t>();
            if ( result )
            {
                response->bitmap_words.push_back(*result);
            }
            else
            {
                break;
            }
        }
    }
    catch(boost::property_tree::ptree_bad_path & err)
    {
        // The value is optional.
    }

#   undef return_error
}

mf::http::SharedBuffer::Pointer Impl::GetPostData()
{
    std::map<std::string, std::string> parts;

    if (resumable_)
        parts["resumable"] = AsString(*resumable_);
    if (filename_)
        parts["filename"] = *filename_;
    if (quickkey_)
        parts["quick_key"] = *quickkey_;
    if (hash_)
        parts["hash"] = *hash_;
    if (filesize_)
        parts["size"] = AsString(*filesize_);
    if (upload_folder_key_)
        parts["upload_folder_key"] = *upload_folder_key_;
    if (relative_path_)
        parts["path"] = *relative_path_;
    if (action_on_duplicate_)
        parts["action_on_duplicate"] = AsString(*action_on_duplicate_);
    if (mtime_)
        parts["mtime"] = AsString(*mtime_);

    std::string post_data = MakePost(api_path + ".php", parts);
    api_data_type_debug_ += " POST data: " + post_data + "\n";
    return mf::http::SharedBuffer::Create(post_data);
}

// Request ---------------------------------------------------------------------

Request::Request() :
    impl_(new Impl())
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

void Request::SetResumable(Resumability resumable)
{
    impl_->resumable_ = resumable;
}

void Request::SetFilename(std::string filename)
{
    impl_->filename_ = filename;
}

void Request::SetQuickkey(std::string quickkey)
{
    impl_->quickkey_ = quickkey;
}

void Request::SetHash(std::string hash)
{
    impl_->hash_ = hash;
}

void Request::SetFilesize(uint64_t filesize)
{
    impl_->filesize_ = filesize;
}

void Request::SetUploadFolderKey(std::string upload_folder_key)
{
    impl_->upload_folder_key_ = upload_folder_key;
}

void Request::SetRelativePath(std::string relative_path)
{
    impl_->relative_path_ = relative_path;
}

void Request::SetActionOnDuplicate(ActionOnDuplicate action_on_duplicate)
{
    impl_->action_on_duplicate_ = action_on_duplicate;
}

void Request::SetMtime(boost::posix_time::ptime mtime)
{
    impl_->mtime_ = mtime;
}

mf::http::SharedBuffer::Pointer Request::GetPostData()
{
    return impl_->GetPostData();
}

}  // namespace v0
}  // namespace pre_upload
}  // namespace upload
}  // namespace api
}  // namespace mf
