#include "connection_server.hpp"
#include "connection_server_impl.hpp"

namespace server
{
    const unsigned short _PORT = 9000;

    connection_server::connection_server(const unsigned short &port) : pImpl(std::make_unique<impl>(port)),
                                                                       PORT(port)
    {
    }

    connection_server::~connection_server()
    {
    }

    void connection_server::start_server()
    {
        std::cout << " Register broadcast message @ PORT : " << PORT + 1 << std::endl
                  << " To view broadcast message connect PORT @ " << PORT << std::endl;
        try
        {
            pImpl->setup_shared_memory();
            pImpl->setup_broadcasting_msg();

            auto ec = pImpl->set_acceptor_properties_impl();
            if (ec)
            {
                std::cout << "Error occurred while setting acceptor properties..!!" << std::endl
                          << ec.message() << std::endl;
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