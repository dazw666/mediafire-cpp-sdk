/**
 * @file get_updates.cpp
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

namespace v0 = mf::api::device::get_updates::v0;


#include "mediafire_sdk/api/type_helpers.hpp"

namespace {
// get_data_type_struct_extractor begin
using namespace v0;  // NOLINT
bool UpdateFromPropertyBranch(
        Response * response,
        Response::Update * value,
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
    using mf::api::GetValueIfExists;

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "source_revision",
            &value->source_revision ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"source_revision\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "source_hash",
            &value->source_hash ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"source_hash\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "target_revision",
            &value->target_revision ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"target_revision\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "target_hash",
            &value->target_hash ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"target_hash\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "timestamp",
            &value->timestamp ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"timestamp\"");

    // get_data_type_struct_extractor conclusion
    return true;
#   undef return_error
}
}  // namespace

namespace mf {
namespace api {
/** API action path "device" */
namespace device {
namespace get_updates {
namespace v0 {

const std::string api_path("/api/device/get_updates");

// Impl ------------------------------------------------------------------------

class Impl : public SessionTokenApiBase<Response>
{
public:
    Impl(
            std::string quickkey,
            uint64_t revision
        );

    std::string quickkey_;
    uint64_t revision_;
    boost::optional<uint64_t> target_revision_;
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
        std::string quickkey,
        uint64_t revision
    ) :
    quickkey_(quickkey),
    revision_(revision)
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

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.current_revision",
            &response->current_revision ) )
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"response.current_revision\"");

    // create_content_struct_parse TArray
    try {
        const boost::property_tree::wptree & branch =
            response->pt.get_child(L"response.updates");
        response->updates.reserve( response->pt.size() );

        for ( auto & it : branch )
        {
            Response::Update optarg;
            if ( UpdateFromPropertyBranch(
                    response, &optarg, it.second) )
                response->updates.push_back(std::move(optarg));
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

    parts["quick_key"] = quickkey_;
    parts["revision"] = AsString(revision_);
    if (target_revision_)
        parts["target_revision"] = AsString(*target_revision_);

    std::string post_data = MakePost(api_path + ".php", parts);
    AddDebugText(" POST data: " + post_data + "\n");
    return mf::http::SharedBuffer::Create(post_data);
}

// Request ---------------------------------------------------------------------

Request::Request(
        std::string quickkey,
        uint64_t revision
    ) :
    impl_(new Impl(quickkey, revision))
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

void Request::SetTargetRevision(uint64_t target_revision)
{
    impl_->target_revision_ = target_revision;
}

mf::http::SharedBuffer::Pointer Request::GetPostData()
{
    return impl_->GetPostData();
}

}  // namespace v0
}  // namespace get_updates
}  // namespace device
}  // namespace api
}  // namespace mf
