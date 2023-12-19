#pragma once

#include <functional>
#include <optional>

#include "RestSession.h"
#include "Socket.h"

namespace DutchFeud::WebServer
{
    enum class Method
    {
        GET,
        POST
    };

    typedef std::function < RestSession & ( ConnectionData ) > ConnectionHandler;
    typedef std::function < std::string ( RestSession &, std::string &, Method ) > RouteHandler;

    class Rest : public Socket
    {
    private:
        std::optional < ConnectionHandler > _connectHandler;
        std::optional < std::reference_wrapper< const ConnectionHandler > > _disconnectHandler;
        std::unordered_map< std::string, RouteHandler > _routes;

    public:
        Rest( int port );

        void Stop();
    
        void RegisterConnectHandler( ConnectionHandler handler );
        void RegisterDisconnectHandler( const ConnectionHandler & handler );

        void RegisterFeudHandler( const std::string & path, RouteHandler handler );


    private:
        void HandleNewConnection( ConnectionData connectionData ) override;     
        void HandleSession( RestSession & session );
    };
}