#ifndef __COMMON_UTILS__
#define __COMMON_UTILS__

#include <boost/asio.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <boost/beast.hpp>

namespace server
{
    namespace asio = boost::asio;
    namespace ip = asio::ip;
    namespace interprocess = boost::interprocess;
    namespace system = boost::system;
    using tcp = ip::tcp;
    using socket_base = asio::socket_base;

    namespace beast = boost::beast;
    namespace websocket = beast::websocket;

} // namespace server

#endif