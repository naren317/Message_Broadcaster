#include "routine_handler.hpp"
#include "data_struct.hpp"
#include <boost/bind.hpp>
#include <iostream>
#include <chrono>

namespace server
{
    routine_handler::routine_handler(tcp::socket &&socket, void *buff) : _wsock(std::move(socket)),
                                                                         _buff(buff)
    {
    }

    std::string
    routine_handler::get_timestamp() const
    {
        return const_cast<const char *>(std::ctime(std::make_shared<time_t>(time(0)).get()));
    }

    void
    routine_handler::set_websocket_options()
    {
        _wsock.set_option(websocket::stream_base::timeout::suggested(
            beast::role_type::server));
        _wsock.set_option(websocket::stream_base::decorator([](websocket::response_type &r) {
            r.set(beast::http::field::server, "Websocket server");
        }));
    }

    void
    routine_handler::run_routine_handlers()
    {
        set_websocket_options();
        _wsock.async_accept(boost::bind(&routine_handler::on_accept, this, asio::placeholders::error));
    }

    void
    routine_handler::on_accept(const system::error_code &ec)
    {
        if (ec)
            std::cout << " Error occurred : " << ec.message() << std::endl
                      << " Error code : " << ec.value() << std::endl;

        _wsock.async_write(asio::buffer(std::string("Connection accepted by server @ : ").append(get_timestamp())), boost::bind(&routine_handler::on_write, this, asio::placeholders::error, asio::placeholders::bytes_transferred));
    }

    void
    routine_handler::on_write(const system::error_code &ec, const size_t bytes)
    {
        if (ec)
        {
            std::cout << " Error occurred : " << ec.message() << std::endl
                      << " Error code : " << ec.value() << std::endl;
        }
        else
        {
            auto data = static_cast<const data_struct *>(_buff)->get_buffer_and_size();
            _wsock.async_write(asio::buffer(get_timestamp() + "\n" + std::string(data.first, data.second)), boost::bind(&routine_handler::on_write, this, asio::placeholders::error, asio::placeholders::bytes_transferred));
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }

    routine_handler::~routine_handler()
    {
        std::cout << " Closing client socket .." << std::endl;
    }

} // namespace server