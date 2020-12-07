#ifndef _ROUTINE_HANDLER_
#define _ROUTINE_HANDLER_

#include "common_utils.hpp"
#include <memory>

namespace server
{
    class routine_handler
    {

    public:
        explicit routine_handler(tcp::socket &&socket, void *buff);
        ~routine_handler();

        void
        on_accept(const system::error_code &ec);

        void
        on_write(const system::error_code &ec, const size_t bytes);

        void
        run_routine_handlers();

        void
        set_websocket_options();

        std::string
        get_timestamp() const;

    private:
        websocket::stream<beast::tcp_stream> _wsock;
        beast::flat_buffer _data_buff;
        void *_buff;
    };
} // namespace server

#endif