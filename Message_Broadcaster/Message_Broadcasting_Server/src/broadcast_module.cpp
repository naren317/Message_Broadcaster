#include "broadcast_module.hpp"
#include "data_struct.hpp"
#include <iostream>

namespace server
{
    broadcast_module::broadcast_module(asio::io_context& ioc, void *sh_mem, const std::string port) : _ioc(ioc),
                                                                                                      _sh_mem(sh_mem),
                                                                                                      _port(port),
                                                                                                      _endp(tcp::endpoint(ip::address_v4::any(), strtoul(port.c_str(), nullptr, 10) + 1)),
                                                                                                      _acceptor(_ioc),
                                                                                                      _broadcast_data()

    {
        set_acceptor_properties();
    }

    void
    broadcast_module::set_acceptor_properties()
    {
        _acceptor.open(_endp.protocol());
        _acceptor.set_option(asio::socket_base::reuse_address(true));
        _acceptor.bind(_endp);
        _acceptor.listen(asio::socket_base::max_listen_connections);
    }

    void
    broadcast_module::run_broadcast_module()
    {
        auto _baccept = _acceptor.accept();
        _baccept.send(asio::buffer("-- Broadcast server message module --\r\nEnter your message and end with 'endofmsg'(without quotes) : "));
        asio::streambuf stbuf;

        asio::read_until(_baccept, stbuf, "endofmsg");
        auto data = std::string(asio::buffer_cast<const char *>(stbuf.data()));
        _broadcast_data.clear();
        _broadcast_data.append(data.substr(0, data.find("endofmsg")));
        static_cast<data_struct *>(_sh_mem)->set_buffer_and_size(_broadcast_data.c_str(), _broadcast_data.size());
        _baccept.send(asio::buffer("Broadcast message successfully registered ...\r\n"));
        _baccept.shutdown(asio::socket_base::shutdown_both);
        if (!_ioc.stopped())
            run_broadcast_module();
    }

    broadcast_module::~broadcast_module()
    {
    }
} // namespace server
