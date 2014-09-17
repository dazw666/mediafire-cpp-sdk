/**
 * @file get_user_shares.cpp
 *
 * @copyright Copyright 2014 Mediafire
 *
 * This file was generated by gen_api_template.py. Do NOT edit by hand.
 */
// #define OUTPUT_DEBUG
#include "get_user_shares.hpp"

#include <string>

#include "mediafire_sdk/api/error.hpp"
#include "mediafire_sdk/api/ptree_helpers.hpp"
#include "mediafire_sdk/utils/string.hpp"
#include "mediafire_sdk/api/session_token_api_base.hpp"

#include "boost/property_tree/json_parser.hpp"

namespace v0 = mf::api::device::get_user_shares::v0;


#include "mediafire_sdk/api/type_helpers.hpp"

namespace {
// get_data_type_struct_extractor begin
using namespace v0;  // NOLINT
bool ShareFromPropertyBranch(
        Response * response,
        Response::Share * value,
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

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "contact_key",
            &value->contact_key ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"contact_key\"");

    {
        std::string optval;
        // create_content_enum_parse TSingle
        if ( GetIfExists(
                pt,
                "contact_indirect",
                &optval) )
        {
            if ( optval == "0" )
                value->contact_indirect = ContactIndirect::Direct;
            else if ( optval == "1" )
                value->contact_indirect = ContactIndirect::Indirect;
            else
                return_error(
                    mf::api::errc::ContentInvalidData,
                    "invalid value in contact_indirect");
        }
        else
            return_error(
                mf::api::errc::ContentInvalidData,
                "no value in contact_indirect");
    }

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "contact_type",
            &value->contact_type ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"contact_type\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "display_name",
            &value->display_name ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"display_name\"");

    // create_content_parse_single optional no default
    {
        std::string optarg;
        if ( GetIfExists(
                pt,
                "avatar",
                &optarg) )
        {
            value->avatar = optarg;
        }
    }

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "resource_key",
            &value->resource_key ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"resource_key\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "attributes",
            &value->attributes ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"attributes\"");

    {
        std::string optval;
        // create_content_enum_parse TSingle
        if ( GetIfExists(
                pt,
                "permissions",
                &optval) )
        {
            if ( optval == "1" )
                value->share_permissions = Permissions::Read;
            else if ( optval == "2" )
                value->share_permissions = Permissions::ReadWrite;
            else if ( optval == "4" )
                value->share_permissions = Permissions::Manage;
            else
                return_error(
                    mf::api::errc::ContentInvalidData,
                    "invalid value in permissions");
        }
        else
            return_error(
                mf::api::errc::ContentInvalidData,
                "no value in permissions");
    }

    // get_data_type_struct_extractor conclusion
    return true;
#   undef return_error
}
}  // namespace

namespace mf {
namespace api {
/** API action path "device" */
namespace device {
namespace get_user_shares {
namespace v0 {

const std::string api_path("/api/device/get_user_shares");

// Impl ------------------------------------------------------------------------

class Impl : public SessionTokenApiBase<Response>
{
public:
    Impl();

    boost::optional<std::string> contacts_;
    boost::optional<uint32_t> limit_;
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

    // create_content_struct_parse TArray
    try {
        const boost::property_tree::wptree & branch =
            response->pt.get_child(L"response.shares");
        response->shares.reserve( response->pt.size() );

        for ( auto & it : branch )
        {
            Response::Share optarg;
            if ( ShareFromPropertyBranch(
                    response, &optarg, it.second) )
                response->shares.push_back(std::move(optarg));
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

    if (contacts_)
        parts["contacts"] = *contacts_;
    if (limit_)
        parts["limit"] = AsString(*limit_);

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

void Request::SetContacts(std::string contacts)
{
    impl_->contacts_ = contacts;
}

void Request::SetLimit(uint32_t limit)
{
    impl_->limit_ = limit;
}

mf::http::SharedBuffer::Pointer Request::GetPostData()
{
    return impl_->GetPostData();
}

}  // namespace v0
}  // namespace get_user_shares
}  // namespace device
}  // namespace api
}  // namespace mf
