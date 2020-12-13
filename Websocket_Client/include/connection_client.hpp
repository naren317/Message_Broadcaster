#ifndef _CONNECTION_CLIENT_
#define _CONNECTION_CLIENT_

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <memory>

namespace client
{
    namespace asio = boost::asio;
    namespace beast = boost::beast;
    namespace websocket = beast::websocket;
    namespace system = boost::system;
    namespace ip = asio::ip;
    using tcp = ip::tcp;

    class connection_client
    {
    private:
        asio::io_context ioc;
        struct impl;
        std::shared_ptr<impl> pImpl;

    public:
        explicit connection_client(const std::string &host, const std::string &port);
        void connect_host();
        ~connection_client();

        enum class mod_index : unsigned int
        {
            ON_HOST_RESOLVE = 1,
            ON_CONNECT,
            ON_READ,
            ON_HANDSHAKE //Always needs to be the last one
        };
        static const std::string module[(int)mod_index::ON_HANDSHAKE];
    };
} // namespace client
#endif
