#include <iostream>
#include "connection_client.hpp"
#include <memory>
#include <exception>
#include <boost/asio.hpp>

int main(int argc, char* argv[])
{
    try
    {
        std::make_shared<client::connection_client>(argv[1], argv[2])->connect_host();
    }
    catch(const std::exception& e)
    {
        std::cout << "Exception " << e.what();

    }
    return 0;
}