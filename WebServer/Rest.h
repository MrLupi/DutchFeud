#pragma once

#include "Socket.h"

namespace DutchFeud::Webserver
{
    class Rest : public Socket
    {
    public:
        Rest( int port );

        void Stop();
    
    private:
        void HandleNewConnection( int clientFileDescriptor ) override;
    };
}