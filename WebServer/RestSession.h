#pragma once

#include <optional>
#include <thread>

namespace DutchFeud::WebServer
{
    class RestSession
    {
        protected:
        std::optional< std::thread > _oThread;
        std::string _ipAddress;
        int _clientFileDescriptor;

        public:
        RestSession( std::string ipAddress, int clientFileDescriptor );

    };
}