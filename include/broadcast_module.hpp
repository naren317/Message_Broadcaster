#ifndef __BROADCAST_HPP__
#define __BROADCAST_HPP__

#include "common_utils.hpp"

namespace server
{
    extern const unsigned short _PORT;

    class broadcast_module
    {
        using constus = const unsigned short;

    private:
        asio::io_context& _ioc;
        void *_sh_mem;
        tcp::acceptor _acceptor;
        tcp::endpoint _endp;
        std::string _broadcast_data;
        constus& _port;

        void
        set_acceptor_properties();

    public:
        explicit broadcast_module(asio::io_context& ioc, void *sh_mem = nullptr, constus& port = _PORT);

        void
        run_broadcast_module();

        ~broadcast_module();
    };

} // namespace server

#endif
