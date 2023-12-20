#pragma once

#include <optional>
#include <thread>

namespace DutchFeud::WebServer
{
    class RestSession
    {
        protected:
        std::string _ipAddress;
        int _clientFileDescriptor;

        public:
        std::thread Thread;


        public:
        RestSession( std::string ipAddress, int clientFileDescriptor );
        virtual ~RestSession();
        const std::string & GetIpAddress() const;
        int GetClientFileDescriptor() const;
    };
}