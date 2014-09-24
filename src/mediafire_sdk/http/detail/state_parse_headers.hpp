/**
 * @file pstate_parse_headers.hpp
 * @author Herbert Jones
 * @brief Config state machine transitions
 * @copyright Copyright 2014 Mediafire
 */
#pragma once

#include <sstream>

#include "boost/msm/front/state_machine_def.hpp"

#include "mediafire_sdk/http/detail/http_request_events.hpp"
#include "mediafire_sdk/http/error.hpp"
#include "mediafire_sdk/http/headers.hpp"
#include "mediafire_sdk/http/url.hpp"

namespace mf {
namespace http {
namespace detail {

class ParseHeaders : public boost::msm::front::state<>
{
public:
    template <typename Event, typename FSM>
    void on_entry(Event const & evt, FSM & fsm)
    {
        using mf::http::http_error;

        if (evt.status_code == 301 || evt.status_code == 302)
        {
            auto it = evt.headers.find("location");
            if ( it == evt.headers.end() )
            {
                std::stringstream ss;
                ss << "Bad " << evt.status_code << " redirect.";
                ss << " Source URL: " << fsm.get_url();
                ss << " Missing \"Location\" header";
                fsm.ProcessEvent(ErrorEvent{
                        make_error_code(
                            http_error::InvalidRedirectUrl ),
                        ss.str()
                    });
            }
            else
            {
                try {
                    auto iface = fsm.get_callback();
                    auto & raw_headers = evt.raw_headers;
                    auto & header_map = evt.headers;
                    auto url = mf::http::Url(it->second);

                    if ( fsm.get_callback_io_service() ==
                        fsm.get_work_io_service())
                    {
                        iface->RedirectHeaderReceived( raw_headers, header_map,
                            url );
                    }
                    else
                    {
                        fsm.get_callback_io_service()->dispatch(
                            [iface, raw_headers, header_map, url]()
                            {
                                iface->RedirectHeaderReceived( raw_headers,
                                    header_map, url );
                            }
                        );
                    }

                    RedirectEvent redirect(evt);
                    redirect.redirect_url = it->second;
                    fsm.ProcessEvent(redirect);
                }
                catch(mf::http::InvalidUrl & err)
                {
                    std::stringstream ss;
                    ss << "Bad " << evt.status_code << " redirect.";
                    ss << " Source URL: " << fsm.get_url();
                    ss << " Invalid redirect url: " << it->second;
                    fsm.ProcessEvent(ErrorEvent{
                            make_error_code(
                                http_error::InvalidRedirectUrl ),
                            ss.str()
                        });
                }
            }
        }
        else
        {
            mf::http::Headers headers;

            headers.raw_headers = evt.raw_headers;
            headers.status_code = evt.status_code;
            headers.status_message = evt.status_message;
            headers.headers = evt.headers;

            auto iface = fsm.get_callback();
            if ( fsm.get_callback_io_service() == fsm.get_work_io_service())
            {
                iface->ResponseHeaderReceived( headers );
            }
            else
            {
                fsm.get_callback_io_service()->dispatch(
                    [iface, headers]()
                    {
                        iface->ResponseHeaderReceived( headers );
                    });
            }

            fsm.ProcessEvent(HeadersParsedEvent{
                evt.content_length,
                evt.headers,
                evt.read_buffer
                });
        }
    }

    template <typename Event, typename FSM>
    void on_exit(Event const&, FSM &)
    {
    }

private:
};


}  // namespace detail
}  // namespace http
}  // namespace mf
