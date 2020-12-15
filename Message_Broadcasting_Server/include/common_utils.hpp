#ifndef __COMMON_UTILS__
#define __COMMON_UTILS__

#include <boost/asio.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/beast.hpp>
#include <iostream>

namespace server
{
    namespace asio = boost::asio;
    namespace ip = asio::ip;
    namespace interprocess = boost::interprocess;
    namespace system = boost::system;
    namespace beast = boost::beast;
    namespace websocket = beast::websocket;
    using tcp = ip::tcp;
    using socket_base = asio::socket_base;
    using constus = const unsigned short;

    struct helper
    {
        enum class mod_index : unsigned int
        {
            ON_SETTING_ACCEPTOR_PROPERTIES = 1,
            ON_ACCEPT,
            ON_READ,
            ON_WRITE,
            ON_HANDSHAKE //Always needs to be the last one
        };

        static const std::string module[(int)mod_index::ON_HANDSHAKE];
       
        static void on_error(system::error_code const ec, mod_index const mi)
        {
            std::cout << module[(int)mi-1] << " Error : " << ec.message() << std::endl
                      << " Error code : " << ec.value() << std::endl;
        }
    };
} // namespace server

#endif