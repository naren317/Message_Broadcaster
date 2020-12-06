#ifndef _CONNECTION_SERVER_
#define _CONNECTION_SERVER_

#include "routine_handler.hpp"
#include "data_struct.hpp"
#include "common_utils.hpp"
#include <iostream>
#include <memory>

namespace server
{
    extern const unsigned short _PORT;

    class connection_server
    {

    public:
        explicit connection_server(const unsigned short& port = _PORT);

        void
        start_server();

        ~connection_server();

    private:
        class impl;
        std::unique_ptr<impl> pImpl;
        const unsigned short PORT;
    };

} // namespace server

#endif