#pragma once

#include <optional>
#include <thread>

#include <openssl/ssl.h>

namespace DutchFeud::WebServer
{
    class RestSession
    {
        private:
        std::string _ipAddress;
        int _clientFileDescriptor;
        SSL * _sslDescriptor;

        public:
        std::thread Thread;

        public:
        RestSession( std::string ipAddress, int clientFileDescriptor, SSL * sslDescriptor );
        virtual ~RestSession();
        const std::string & GetIpAddress() const;
        int GetClientFileDescriptor() const;
        SSL * GetSSLDescriptor() const;
    };
}