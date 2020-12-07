#ifndef __CONNECTION_SERVER_IMPL__
#define __CONNECTION_SERVER_IMPL__

#include "broadcast_module.hpp"
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

class server::connection_server::impl
{

private:
    asio::io_context _ioc;
    tcp::endpoint _endp;
    tcp::acceptor _acceptor;
    boost::thread_group _thread_group;
    interprocess::interprocess_mutex _mtx;
    std::string _broadcast_data;
    const unsigned short _port;
    interprocess::managed_shared_memory _msm;
    void *_sh_mem;

    struct _delete_shared_mem
    {
        _delete_shared_mem() { interprocess::shared_memory_object::remove("Shared_Mem"); }
        ~_delete_shared_mem() { interprocess::shared_memory_object::remove("Shared_Mem"); }
    } _delete_shared_mem;

public:
    explicit impl(const unsigned short &port = _PORT) : _port(port),
                                                        _ioc(boost::thread::hardware_concurrency()),
                                                        _endp(tcp::endpoint(ip::address_v4::any(), port)),
                                                        _acceptor(_ioc),
                                                        _thread_group(),
                                                        _mtx(),
                                                        _broadcast_data("Default broadcast message\r\n"),
                                                        _sh_mem(nullptr),
                                                        _delete_shared_mem(),
                                                        _msm(interprocess::open_or_create, "Shared_Mem", 10 * 1024)
    {
        _thread_group.create_thread(
            [&] 
            {
                boost::asio::signal_set ss(_ioc, SIGTERM, SIGINT);

                ss.async_wait(
                    [&](const system::error_code &ec, int signal)
                    {

                    _ioc.stop();

                    });

                    _ioc.run();
            });
    }

    void
    start_listening_impl() noexcept(false)
    {
        auto _socket{_acceptor.accept()};

        _thread_group.create_thread(
            [&]
            {
                _mtx.lock();
                server::routine_handler _rh(std::forward<tcp::socket>(_socket), _sh_mem);
                _mtx.unlock();
                _rh.run_routine_handlers();
                _ioc.run();
            });
        
        start_listening_impl();
    }

    system::error_code
    set_acceptor_properties_impl() noexcept(false)
    {
        system::error_code ec;
        _acceptor.open(_endp.protocol(), ec);
        if (ec)
            return ec;
        _acceptor.set_option(socket_base::reuse_address(true), ec);
        if (ec)
            return ec;
        _acceptor.bind(_endp, ec);
        if (ec)
            return ec;
        _acceptor.listen(socket_base::max_listen_connections, ec);
        return ec;
    }

    void
    setup_shared_memory()
    {
        _sh_mem = _msm.construct<data_struct>("Shared_Data")();
        static_cast<data_struct *>(_sh_mem)->set_buffer_and_size(_broadcast_data.c_str(), _broadcast_data.size());
    }

    void
    setup_broadcasting_msg()
    {
        _thread_group.create_thread(
            [&]
            {
                _mtx.lock();
                server::broadcast_module _bm(_ioc, _sh_mem, _port);
                _mtx.unlock();
                _bm.run_broadcast_module();
            });
    }

    void
    exception_handler_impl()
    {
        std::cout << " Shutting down server .." << std::endl;
        if (!_ioc.stopped())
            _ioc.stop();
            
        std::unique_lock<interprocess::interprocess_mutex> _ulock(_mtx);
        _thread_group.join_all();
        _acceptor.close();
        _broadcast_data.clear();
        _msm.destroy<data_struct>("Shared_Data");
        interprocess::shared_memory_object::remove("Shared_Mem");
    }

    ~impl()
    {
        if (!_ioc.stopped())
            _ioc.stop();
    }
};

#endif