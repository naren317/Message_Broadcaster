#include "connection_server.hpp"
#include "connection_server_impl.hpp"
#include "routine_handler.hpp"
#include <iostream>

namespace server
{
    const std::string _PORT = R"(9000)";

    const std::string helper::module[(int)helper::mod_index::ON_HANDSHAKE] = {"Setting acceptor properties",
                                                                              "Accept",
                                                                              "Read",
                                                                              "Write",
                                                                              "Handshake"};

    connection_server::connection_server(const std::string port) : pImpl(std::make_unique<impl>(port)),
                                                                   PORT(std::strtoul(port.c_str(), nullptr, 10))
    {
    }

    connection_server::~connection_server()
    {
    }

    void connection_server::start_server()
    {
        std::cout << " To view the broadcasted message connect PORT @ " << PORT << std::endl
                  << " To modify the broadcasted message register @ PORT : " << PORT + 1 << std::endl;
        try
        {
            pImpl->setup_shared_memory();

            pImpl->setup_broadcasting_msg();

            auto ec = pImpl->set_acceptor_properties_impl();
            if (ec)
            {
                helper::on_error(ec, helper::mod_index::ON_SETTING_ACCEPTOR_PROPERTIES);
                pImpl->exception_handler_impl();
            }
            std::cout << " Listening ... Press ctrl + c to abort ..." << std::endl;

            pImpl->start_listening_impl();
        }

        catch (const interprocess::interprocess_exception &ec)
        {
            pImpl->exception_handler_impl();
            std::cout << "Shared Memory Exception occurred : " << ec.what() << std::endl
                      << "Exception Error Code : " << ec.get_error_code();
        }

        catch (const system::system_error &ec)
        {
            pImpl->exception_handler_impl();
            if (ec.code() != system::errc::interrupted)
                std::cout << "System Exception occurred : " << ec.what() << std::endl
                          << "Error Code : " << ec.code();
        }

        catch (const std::exception &ec)
        {
            pImpl->exception_handler_impl();
            std::cout << " Exception occurred : " << ec.what() << std::endl;
        }
    }
} // namespace server