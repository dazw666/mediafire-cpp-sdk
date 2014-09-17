/**
 * @file purchase_plan.cpp
 *
 * @copyright Copyright 2014 Mediafire
 *
 * This file was generated by gen_api_template.py. Do NOT edit by hand.
 */
// #define OUTPUT_DEBUG
#include "purchase_plan.hpp"

#include <string>

#include "mediafire_sdk/api/error.hpp"
#include "mediafire_sdk/api/ptree_helpers.hpp"
#include "mediafire_sdk/utils/string.hpp"
#include "mediafire_sdk/api/session_token_api_base.hpp"

#include "boost/property_tree/json_parser.hpp"

namespace v0 = mf::api::billing::purchase_plan::v0;


namespace {
std::string AsString(const v0::PaymentMethod & value)
{
    if (value == v0::PaymentMethod::NewCredit)
        return "newcredit";
    if (value == v0::PaymentMethod::PreviousCredit)
        return "prevcredit";
    return mf::utils::to_string(static_cast<uint32_t>(value));
}
std::string AsString(const v0::KeepCard & value)
{
    if (value == v0::KeepCard::DiscardCard)
        return "0";
    if (value == v0::KeepCard::KeepCard)
        return "1";
    return mf::utils::to_string(static_cast<uint32_t>(value));
}
}  // namespace

#include "mediafire_sdk/api/type_helpers.hpp"

namespace mf {
namespace api {
/** API action path "billing" */
namespace billing {
namespace purchase_plan {
namespace v0 {

const std::string api_path("/api/billing/purchase_plan");

// Impl ------------------------------------------------------------------------

class Impl : public SessionTokenApiBase<Response>
{
public:
    Impl();

    boost::optional<uint32_t> product_id_;
    boost::optional<PaymentMethod> payment_method_;
    boost::optional<std::string> first_name_info_;
    boost::optional<std::string> last_name_info_;
    boost::optional<std::string> address1_info_;
    boost::optional<std::string> city_info_;
    boost::optional<std::string> zip_info_;
    boost::optional<std::string> state_info_;
    boost::optional<std::string> country_info_;
    boost::optional<std::string> region_info_;
    boost::optional<std::string> postal_code_info_;
    boost::optional<std::string> card_number_;
    boost::optional<std::string> card_code_;
    boost::optional<std::string> exp_month_;
    boost::optional<std::string> exp_year_;
    boost::optional<KeepCard> keep_card_;
    boost::optional<std::string> prev_card_code_;
    boost::optional<std::string> subdomain_;
    boost::optional<std::string> company_;
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
    response->created_datetime = boost::posix_time::not_a_date_time;
    response->previous_invoice_datetime = boost::posix_time::not_a_date_time;

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.invoice",
            &response->invoice ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.invoice\"");

    // create_content_parse_single optional with default
    GetIfExists(
            response->pt,
            "created",
            &response->created_datetime);

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.total",
            &response->total ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.total\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.product",
            &response->product_id ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.product\"");

    // create_content_parse_single required
    if ( ! GetIfExists(
            response->pt,
            "response.premium",
            &response->premium ) )
        return_error(
            mf::api::errc::ContentInvalidData,
            "missing \"response.premium\"");

    // create_content_parse_single optional with default
    GetIfExists(
            response->pt,
            "lastpremium",
            &response->previous_invoice_datetime);

#   undef return_error
}

mf::http::SharedBuffer::Pointer Impl::GetPostData()
{
    std::map<std::string, std::string> parts;

    if (product_id_)
        parts["pid"] = AsString(*product_id_);
    if (payment_method_)
        parts["payment_method"] = AsString(*payment_method_);
    if (first_name_info_)
        parts["first_name_info"] = *first_name_info_;
    if (last_name_info_)
        parts["last_name_info"] = *last_name_info_;
    if (address1_info_)
        parts["address1_info"] = *address1_info_;
    if (city_info_)
        parts["city_info"] = *city_info_;
    if (zip_info_)
        parts["zip_info"] = *zip_info_;
    if (state_info_)
        parts["state_info"] = *state_info_;
    if (country_info_)
        parts["country_info"] = *country_info_;
    if (region_info_)
        parts["region_info"] = *region_info_;
    if (postal_code_info_)
        parts["postal_code_info"] = *postal_code_info_;
    if (card_number_)
        parts["card_number"] = *card_number_;
    if (card_code_)
        parts["card_code"] = *card_code_;
    if (exp_month_)
        parts["exp_month"] = *exp_month_;
    if (exp_year_)
        parts["exp_year"] = *exp_year_;
    if (keep_card_)
        parts["keep_card"] = AsString(*keep_card_);
    if (prev_card_code_)
        parts["prev_card_code"] = *prev_card_code_;
    if (subdomain_)
        parts["subdomain"] = *subdomain_;
    if (company_)
        parts["company"] = *company_;

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

void Request::SetProductId(uint32_t product_id)
{
    impl_->product_id_ = product_id;
}

void Request::SetPaymentMethod(PaymentMethod payment_method)
{
    impl_->payment_method_ = payment_method;
}

void Request::SetFirstNameInfo(std::string first_name_info)
{
    impl_->first_name_info_ = first_name_info;
}

void Request::SetLastNameInfo(std::string last_name_info)
{
    impl_->last_name_info_ = last_name_info;
}

void Request::SetAddress1Info(std::string address1_info)
{
    impl_->address1_info_ = address1_info;
}

void Request::SetCityInfo(std::string city_info)
{
    impl_->city_info_ = city_info;
}

void Request::SetZipInfo(std::string zip_info)
{
    impl_->zip_info_ = zip_info;
}

void Request::SetStateInfo(std::string state_info)
{
    impl_->state_info_ = state_info;
}

void Request::SetCountryInfo(std::string country_info)
{
    impl_->country_info_ = country_info;
}

void Request::SetRegionInfo(std::string region_info)
{
    impl_->region_info_ = region_info;
}

void Request::SetPostalCodeInfo(std::string postal_code_info)
{
    impl_->postal_code_info_ = postal_code_info;
}

void Request::SetCardNumber(std::string card_number)
{
    impl_->card_number_ = card_number;
}

void Request::SetCardCode(std::string card_code)
{
    impl_->card_code_ = card_code;
}

void Request::SetExpMonth(std::string exp_month)
{
    impl_->exp_month_ = exp_month;
}

void Request::SetExpYear(std::string exp_year)
{
    impl_->exp_year_ = exp_year;
}

void Request::SetKeepCard(KeepCard keep_card)
{
    impl_->keep_card_ = keep_card;
}

void Request::SetPrevCardCode(std::string prev_card_code)
{
    impl_->prev_card_code_ = prev_card_code;
}

void Request::SetSubdomain(std::string subdomain)
{
    impl_->subdomain_ = subdomain;
}

void Request::SetCompany(std::string company)
{
    impl_->company_ = company;
}

mf::http::SharedBuffer::Pointer Request::GetPostData()
{
    return impl_->GetPostData();
}

}  // namespace v0
}  // namespace purchase_plan
}  // namespace billing
}  // namespace api
}  // namespace mf
