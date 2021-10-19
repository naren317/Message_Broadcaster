#include "connection_client.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

namespace client
{    
    const std::string
    connection_client::module[(int)mod_index::ON_HANDSHAKE] = {"Host resolve",
                                                            "Connect",
                                                            "Handshake"};

    struct connection_client::impl : public std::enable_shared_from_this<connection_client::impl>
    {
        explicit impl(const std::string host, const std::string port, asio::io_context &ioc) : _host(host),
                                                                                               _ioc(ioc),
                                                                                               _port(port),
                                                                                               _wsock(ioc),
                                                                                               _resolver(ioc),
                                                                                               _endp(ip::address::from_string(host), strtoul(port.c_str(), nullptr, 10))
        {
        }

        ~impl()
        {
            if (!_ioc.stopped())
                _ioc.stop();
            if (_wsock.is_open())
                _wsock.close(websocket::normal);
        }

        void
        connect()
        {
            boost::system::error_code ec;
            auto result{_resolver.resolve(_endp, ec)};

            if (ec)
            {
                on_error(ec, mod_index::ON_HOST_RESOLVE);
                return;
            }
            _wsock.set_option(websocket::stream_base::decorator([](websocket::request_type &req) {
                req.set(beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
            }));
            
            asio::async_connect(_wsock.next_layer().socket(), result, boost::bind(&connection_client::impl::on_connect, shared_from_this(), boost::asio::placeholders::error));
            _ioc.run();
        }

        void
        on_read(const boost::system::error_code &ec)
        {
            if (ec)
            {
                on_error(ec, mod_index::ON_READ);
                return;
            }
            std::cout << boost::asio::buffer_cast<const char *>(_stbuff.data());
            _wsock.async_read(_stbuff, boost::bind(&connection_client::impl::on_read, shared_from_this(), asio::placeholders::error));
        }

        void
        on_connect(const boost::system::error_code &ec)
        {
            if (ec)
            {
                on_error(ec, mod_index::ON_CONNECT);
                return;
            }
            std::cout << _endp.address().to_string() << std::endl;
            _wsock.async_handshake(_endp.address().to_string(), "/",
                                   [&](const boost::system::error_code &ec) {
                                       if (ec)
                                       {
                                           on_error(ec, mod_index::ON_HANDSHAKE);
                                           return;
                                       }
                                       _wsock.async_read(_stbuff, boost::bind(&connection_client::impl::on_read, shared_from_this(), boost::asio::placeholders::error));
                                   });
        }

        void
        on_error(boost::system::error_code const ec, connection_client::mod_index const mi)
        {
            std::cout << connection_client::module[(int)mi] << " : " << ec.message() << std::endl
                      << "Error code : " << ec.value() << std::endl;
        }

    private:
        asio::io_context &_ioc;
        beast::websocket::stream<beast::tcp_stream> _wsock;
        asio::ip::tcp::resolver _resolver;
        asio::ip::tcp::endpoint _endp;
        asio::streambuf _stbuff;
        const std::string _host;
        const std::string _port;
    };

    connection_client::connection_client(const std::string &host, const std::string &port) : ioc(), pImpl(std::make_shared<impl>(host, port, ioc))
    {
    }

    void connection_client::connect_host()
    {
        pImpl->connect();
    }

    connection_client::~connection_client()
    {
        if (!ioc.stopped())
            ioc.stop();
    }

} // namespace client