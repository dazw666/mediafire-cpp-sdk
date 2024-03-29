/**
 * @file api/billing/get_invoice.hpp
 * @brief API request: /api/1.1/billing/get_invoice
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
/** API action path "billing" */
namespace billing {
/** API action "billing/get_invoice" */
namespace get_invoice {
/** API path "/api/1.1/billing/get_invoice" */
namespace v1_1 {

enum class Activity
{
    /** API value "0" */
    Inactive,
    /** API value "1" */
    Active
};

enum class Legacy
{
    /** API value "0" */
    No,
    /** API value "1" */
    Yes
};

enum class Recurring
{
    /** API value "0" */
    NonRecurring,
    /** API value "1" */
    Recurring
};

enum class ResellerEntitled
{
    /** API value "0" */
    No,
    /** API value "1" */
    Yes
};

enum class Trial
{
    /** API value "0" */
    NonTrial,
    /** API value "1" */
    Trial
};

enum class UsesCredits
{
    /** API value "0" */
    No,
    /** API value "1" */
    Yes
};

enum class Yearly
{
    /** API value "0" */
    NotYearly,
    /** API value "1" */
    Yearly
};

/**
 * @class Response
 * @brief Response from API request "billing/get_invoice"
 */
class Response : public ResponseBase
{
public:
    Response() :
        recurring_startdate(boost::posix_time::not_a_date_time),
        recurring_enddate(boost::posix_time::not_a_date_time),
        next_bandwidth(boost::posix_time::not_a_date_time)
    {}
    struct Product
    {
        /** API response field "product_id" */
        uint32_t product_id;

        /** API response field "description" */
        std::string description;

        /** API response field "short_description" */
        std::string short_description;

        /** API response field "initial_amount" */
        std::string initial_amount;

        /** API response field "initial_units" */
        uint64_t initial_units;

        /** API response field "is_recurring" */
        Recurring is_recurring;

        /** API response field "recurring_amount" */
        std::string recurring_amount;

        /** API response field "recurring_units" */
        uint32_t recurring_units;

        /** API response field "free_months" */
        uint32_t free_months;

        /** API response field "trial" */
        Trial trial;

        /** API response field "active" */
        Activity active;

        /** API response field "frequency_text" */
        std::string frequency_text;

        /** API response field "uses_credits" */
        UsesCredits uses_credits;

        /** API response field "reseller_entitlement" */
        ResellerEntitled reseller_entitlement;

        /** API response field "payment_methods" */
        std::string payment_methods;

        /** API response field "interval" */
        uint32_t interval;

        /** API response field "legacy" */
        Legacy legacy;

        /** API response field "product_class" */
        uint32_t product_class;

        /** API response field "product_family" */
        uint32_t product_family;

        /** API response field "base_storage" */
        uint64_t base_storage;
    };
    /** API response field "response.invoice.invoice_id" */
    uint32_t invoice_id;

    /** API response field "response.invoice.invoice_num" */
    std::string invoice_num;

    /** API response field "response.invoice.payment_method" */
    std::string payment_method;

    /** API response field "response.invoice.recurring_status" */
    std::string recurring_status;

    /** API response field "response.invoice.recurring_profile_id" */
    uint32_t recurring_profile_id;

    /** API response field "response.invoice.date_created" */
    boost::posix_time::ptime created_datetime;

    /** API response field "response.invoice.company_id" */
    boost::optional<uint32_t> company_id;

    /** API response field "response.invoice.product_id" */
    uint32_t product_id;

    /** API response field "response.invoice.product_description" */
    std::string product_description;

    /** API response field "response.invoice.country" */
    std::string country;

    /** API response field "response.invoice.initial_amount" */
    std::string initial_amount;

    /** API response field "response.invoice.initial_tax" */
    std::string initial_tax;

    /** API response field "response.invoice.initial_total" */
    std::string initial_total;

    /** API response field "response.invoice.recurring_amount" */
    std::string recurring_amount;

    /** API response field "response.invoice.recurring_tax" */
    std::string recurring_tax;

    /** API response field "response.invoice.recurring_total" */
    std::string recurring_total;

    /** API response field "response.invoice.recurring_startdate" */
    boost::posix_time::ptime recurring_startdate;

    /** API response field "response.invoice.recurring_enddate" */
    boost::posix_time::ptime recurring_enddate;

    /** API response field "response.invoice.next_bandwidth" */
    boost::posix_time::ptime next_bandwidth;

    /** API response field "response.invoice.previous_invoice" */
    boost::optional<uint32_t> previous_invoice_id;

    /** API response field "response.invoice.promo_code" */
    std::string promo_code;

    /** API response field "response.invoice.product" */
    Product product;
};

class Impl;

/**
 * @class Request
 * @brief Make API request "billing/get_invoice"
 */
class Request
{
public:
    /**
     * API request "billing/get_invoice"
     */
    Request();

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
}  // namespace v1_1

}  // namespace get_invoice
}  // namespace billing
}  // namespace api
}  // namespace mf
