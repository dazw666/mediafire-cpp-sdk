/**
 * @file get_supported_media.cpp
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
#include "mediafire_sdk/api/tokenless_api_base.hpp"

#include "boost/property_tree/json_parser.hpp"

namespace v0 = mf::api::system::get_supported_media::v0;


#include "mediafire_sdk/api/type_helpers.hpp"

namespace mf {
namespace api {
/** API action path "system" */
namespace system {
namespace get_supported_media {
namespace v0 {

const std::string api_path("/api/system/get_supported_media");

// Impl ------------------------------------------------------------------------

class Impl : public TokenlessApiBase<Response>
{
public:
    Impl();

    virtual void BuildUrl(
        std::string * path,
        std::map<std::string, std::string> * query_parts
    ) const override;

    virtual void ParseResponse( Response * response ) override;

    mf::api::RequestMethod GetRequestMethod() const
    {
        return mf::api::RequestMethod::Get;
    }
};

Impl::Impl()
{
}

void Impl::BuildUrl(
            std::string * path,
            std::map<std::string, std::string> * /* query_parts */
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

    // create_content_parse_array TArray
    try {
        const boost::property_tree::wptree & branch =
            response->pt.get_child(L"response.viewable.extensions");
        response->viewable_extensions.reserve( branch.size() );
        if (branch.empty())
        {
            return_error(
                mf::api::api_code::ContentInvalidData,
                "missing value in response.viewable.extensions");
        }
        for ( auto & it : branch )
        {
            std::string result;
            if ( GetValueIfExists(
                    response->pt,
                    &result ) )
            {
                response->viewable_extensions.push_back(result);
            }
            else
            {
                return_error(
                    mf::api::api_code::ContentInvalidData,
                    "invalid value in response.viewable.extensions");
            }
        }
    }
    catch(boost::property_tree::ptree_bad_path & err)
    {
        // JSON response still has element if expected.
        // This is really an error.
        return_error(
            mf::api::api_code::ContentInvalidData,
            "missing \"response.viewable.extensions\"");
    }

#   undef return_error
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

}  // namespace v0
}  // namespace get_supported_media
}  // namespace system
}  // namespace api
}  // namespace mf
