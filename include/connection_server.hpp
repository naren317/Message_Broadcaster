#ifndef _CONNECTION_SERVER_
#define _CONNECTION_SERVER_

#include "routine_handler.hpp"
#include "data_struct.hpp"
#include "common_utils.hpp"
#include <memory>

namespace server
{
    extern constus _PORT;

    class connection_server
    {

    public:
        explicit connection_server(constus& port = _PORT);

        void
        start_server();

        ~connection_server();

    private:
        class impl;
        std::unique_ptr<impl> pImpl;
        constus PORT;
    };

} // namespace server

#endif