#pragma once

#include <functional>
#include <optional>

#include "Socket.h"

namespace DutchFeud::Webserver
{
    struct ConnectionData
    {
        int ClientFileDescriptor;
        std::string Host;
    };

    enum class Method
    {
        GET,
        POST
    };

    typedef std::function < void ( ConnectionData ) > ConnectionHandler;
    typedef std::function < void ( std::string &, Method ) > RouteHandler;

    class Rest : public Socket
    {
    private:
        std::optional < std::reference_wrapper< const ConnectionHandler > > _connectHandler;
        std::optional < std::reference_wrapper< const ConnectionHandler > > _disconnectHandler;
        std::unordered_map< std::string, RouteHandler > _routes;

    public:
        Rest( int port );

        void Stop();
    
        void RegisterConnectHandler( const ConnectionHandler & handler );
        void RegisterDisconnectHandler( const ConnectionHandler & handler );

        void RegisterFeudHandler( const std::string & path, RouteHandler & handler );


    private:
        void HandleNewConnection( int clientFileDescriptor ) override;        
    };
}