#include "connection_server.hpp"
#include <boost/asio.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        if (argc == 1)
        {
            server::connection_server(server::_PORT).start_server();
        }
        else
        {
            std::cout << "Invalid parameters" << std::endl;
            std::cout << "Usage : Message_Broadcasting_Server <PORT>" << std::endl;
            std::cout << "Example : Message_Broadcasting_Server 9000" << std::endl;
        }
    }
    else
    {
        server::connection_server(argv[1]).start_server();
    }

    return 0;
}