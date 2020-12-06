#include "connection_server.hpp"
#include <boost/asio.hpp>

int main(int argc, char* argv[])
{
    server::connection_server(std::stoul(argv[1], nullptr, 10)).start_server();
    return 0;
}