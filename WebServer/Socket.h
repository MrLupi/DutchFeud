#pragma once

#include <string>

#include <openssl/ssl.h>
#include <openssl/err.h>

#include "General/Algo/Logger.h"

namespace DutchFeud::WebServer
{
    struct ConnectionData
    {
        int ClientFileDescriptor;
        std::string Host;
        SSL * Ssl;
    };

    class Socket
    {
        public:
        enum class SocketState
        {
            Uninitialized,
            Initializing,
            InError,
            Listening,
            Accepting,
            Connected,
            Receiving,
            Closing,
            Closed
        };

        std::string ToString( SocketState state );

        private:
        int _serverFileDescriptor;
        SocketState _socketState;
        int _port;
        std::string _errorMessage;

        protected:
        static General::Algo::Logger _log;
        SSL_CTX * _sslContext;
        
        public:
        Socket( int port );
        void Start();

        private:
        void SetState( SocketState state );
        void SetErrorState( std::string message );
        void HandleState();
        void Initialize();
        void Error();
        void Listen();
        void Accept();
        void Close();
        void CleanUp();

        virtual void HandleNewConnection( ConnectionData connectionData ) = 0;
    };
}