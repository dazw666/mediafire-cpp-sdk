/**
 * @file get_invoice.cpp
 *
 * @copyright Copyright 2014 Mediafire
 *
 * This file was generated by gen_api_template.py. Do NOT edit by hand.
 */
// #define OUTPUT_DEBUG
#include "get_invoice.hpp"

#include <string>

#include "mediafire_sdk/api/error.hpp"
#include "mediafire_sdk/api/ptree_helpers.hpp"
#include "mediafire_sdk/utils/string.hpp"
#include "mediafire_sdk/api/session_token_api_base.hpp"

#include "boost/property_tree/json_parser.hpp"

namespace v0 = mf::api::billing::get_invoice::v0;


#include "mediafire_sdk/api/type_helpers.hpp"

namespace {
// get_data_type_struct_extractor begin
using namespace v0;  // NOLINT
bool ProductFromPropertyBranch(
        Response * response,
        Response::Product * value,
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
    value->is_recurring = Recurring::NonRecurring;
    value->recurring_units = 0;
    value->free_months = 0;
    value->trial = Trial::NonTrial;
    value->active = Activity::Inactive;
    value->frequency_text = "";
    value->uses_credits = UsesCredits::No;
    value->reseller_entitlement = ResellerEntitled::No;
    value->interval = 0;
    value->legacy = Legacy::No;
    value->base_storage = 0;

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "product_id",
            &value->product_id ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"product_id\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "description",
            &value->description ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"description\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "short_description",
            &value->short_description ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"short_description\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "initial_amount",
            &value->initial_amount ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"initial_amount\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "initial_units",
            &value->initial_units ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"initial_units\"");

    {
        std::string optval;
        // create_content_enum_parse TSingle
        if ( GetIfExists(
                pt,
                "is_recurring",
                &optval) )
        {
            if ( optval == "0" )
                value->is_recurring = Recurring::NonRecurring;
            else if ( optval == "1" )
                value->is_recurring = Recurring::Recurring;
        }
    }

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "recurring_amount",
            &value->recurring_amount ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"recurring_amount\"");

    // create_content_parse_single optional with default
    GetIfExists(
            pt,
            "recurring_units",
            &value->recurring_units);

    // create_content_parse_single optional with default
    GetIfExists(
            pt,
            "free_months",
            &value->free_months);

    {
        std::string optval;
        // create_content_enum_parse TSingle
        if ( GetIfExists(
                pt,
                "trial",
                &optval) )
        {
            if ( optval == "0" )
                value->trial = Trial::NonTrial;
            else if ( optval == "1" )
                value->trial = Trial::Trial;
        }
    }

    {
        std::string optval;
        // create_content_enum_parse TSingle
        if ( GetIfExists(
                pt,
                "active",
                &optval) )
        {
            if ( optval == "0" )
                value->active = Activity::Inactive;
            else if ( optval == "1" )
                value->active = Activity::Active;
        }
    }

    // create_content_parse_single optional with default
    GetIfExists(
            pt,
            "frequency_text",
            &value->frequency_text);

    {
        std::string optval;
        // create_content_enum_parse TSingle
        if ( GetIfExists(
                pt,
                "uses_credits",
                &optval) )
        {
            if ( optval == "0" )
                value->uses_credits = UsesCredits::No;
            else if ( optval == "1" )
                value->uses_credits = UsesCredits::Yes;
        }
    }

    {
        std::string optval;
        // create_content_enum_parse TSingle
        if ( GetIfExists(
                pt,
                "reseller_entitlement",
                &optval) )
        {
            if ( optval == "0" )
                value->reseller_entitlement = ResellerEntitled::No;
            else if ( optval == "1" )
                value->reseller_entitlement = ResellerEntitled::Yes;
        }
    }

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "payment_methods",
            &value->payment_methods ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"payment_methods\"");

    // create_content_parse_single optional with default
    GetIfExists(
            pt,
            "interval",
            &value->interval);

    {
        std::string optval;
        // create_content_enum_parse TSingle
        if ( GetIfExists(
                pt,
                "legacy",
                &optval) )
        {
            if ( optval == "0" )
                value->legacy = Legacy::No;
            else if ( optval == "1" )
                value->legacy = Legacy::Yes;
        }
    }

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "product_class",
            &value->product_class ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"product_class\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            pt,
            "product_family",
            &value->product_family ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"product_family\"");

    // create_content_parse_single optional with default
    GetIfExists(
            pt,
            "base_storage",
            &value->base_storage);

    // get_data_type_struct_extractor conclusion
    return true;
#   undef return_error
}
}  // namespace

namespace mf {
namespace api {
/** API action path "billing" */
namespace billing {
namespace get_invoice {
namespace v0 {

const std::string api_path("/api/billing/get_invoice");

// Impl ------------------------------------------------------------------------

class Impl : public SessionTokenApiBase<Response>
{
public:
    Impl();

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
    response->recurring_startdate = boost::posix_time::not_a_date_time;
    response->recurring_enddate = boost::posix_time::not_a_date_time;
    response->next_bandwidth = boost::posix_time::not_a_date_time;

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.invoice.invoice_id",
            &response->invoice_id ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice.invoice_id\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.invoice.invoice_num",
            &response->invoice_num ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice.invoice_num\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.invoice.payment_method",
            &response->payment_method ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice.payment_method\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.invoice.recurring_status",
            &response->recurring_status ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice.recurring_status\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.invoice.recurring_profile_id",
            &response->recurring_profile_id ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice.recurring_profile_id\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.invoice.date_created",
            &response->created_datetime ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice.date_created\"");

    // create_content_parse_single optional no default
    {
        uint32_t optarg;
        if ( GetIfExists(
                response->pt,
                "response.invoice.company_id",
                &optarg) )
        {
            response->company_id = optarg;
        }
    }

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.invoice.product_id",
            &response->product_id ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice.product_id\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.invoice.product_description",
            &response->product_description ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice.product_description\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.invoice.country",
            &response->country ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice.country\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.invoice.initial_amount",
            &response->initial_amount ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice.initial_amount\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.invoice.initial_tax",
            &response->initial_tax ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice.initial_tax\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.invoice.initial_total",
            &response->initial_total ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice.initial_total\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.invoice.recurring_amount",
            &response->recurring_amount ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice.recurring_amount\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.invoice.recurring_tax",
            &response->recurring_tax ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice.recurring_tax\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.invoice.recurring_total",
            &response->recurring_total ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice.recurring_total\"");

    // create_content_parse_single optional with default
    GetIfExists(
            response->pt,
            "response.invoice.recurring_startdate",
            &response->recurring_startdate);

    // create_content_parse_single optional with default
    GetIfExists(
            response->pt,
            "response.invoice.recurring_enddate",
            &response->recurring_enddate);

    // create_content_parse_single optional with default
    GetIfExists(
            response->pt,
            "response.invoice.next_bandwidth",
            &response->next_bandwidth);

    // create_content_parse_single optional no default
    {
        uint32_t optarg;
        if ( GetIfExists(
                response->pt,
                "response.invoice.previous_invoice",
                &optarg) )
        {
            response->previous_invoice_id = optarg;
        }
    }

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.invoice.promo_code",
            &response->promo_code ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice.promo_code\"");

    // create_content_struct_parse TSingle
    try {
        const boost::property_tree::wptree & branch =
            response->pt.get_child(L"response.invoice.product");

        Response::Product optarg;
        if ( ProductFromPropertyBranch(
                response, &optarg, branch) )
        {
            response->product = std::move(optarg);
        }
        else
        {
            // JSON response still has element if expected.
            // This is really an error.
            return_error(
                mf::api::errc::ContentInvalidData,
                "missing \"response.invoice.product\"");
        }
    }
    catch(boost::property_tree::ptree_bad_path & err)
    {
        // JSON response still has element if no files were returned.
        // This is really an error.
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice.product\"");
    }

#   undef return_error
}

mf::http::SharedBuffer::Pointer Impl::GetPostData()
{
    std::map<std::string, std::string> parts;


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

mf::http::SharedBuffer::Pointer Request::GetPostData()
{
    return impl_->GetPostData();
}

}  // namespace v0
}  // namespace get_invoice
}  // namespace billing
}  // namespace api
}  // namespace mf
