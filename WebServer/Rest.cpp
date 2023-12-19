#include "Rest.h"

#include <cerrno>
#include <cstring>
#include <functional>
#include <iostream>
#include <sstream>
#include <unistd.h>

#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>

#include "WebServer/Algo/HeaderBuilder.h"

using namespace DutchFeud;
using namespace DutchFeud::WebServer;


Rest::Rest( int port )
    : Socket( port )
    , _connectHandler( std::nullopt )
    , _disconnectHandler( std::nullopt )
    , _routes()
{
}

void
Rest::RegisterConnectHandler( ConnectionHandler handler )
{
    _connectHandler = handler;
}


void
Rest::RegisterDisconnectHandler( const ConnectionHandler & handler )
{
    _connectHandler = handler;
}

void
Rest::RegisterFeudHandler( const std::string & path, RouteHandler handler )
{
    _routes[ path ] = handler;
}

void 
Rest::HandleSession( RestSession & session )
{
    int n = 0;
    char clientBuffer[10240];

    do
    {
        int returnCode = 999;
        memset( clientBuffer, '\0', sizeof( clientBuffer ) );
        int n = recv( session.GetClientFileDescriptor(), clientBuffer, 10240, 0 );

        if ( n < 1 )
        {
            // todo: log state
            break;            
        }

        char *  methodStr = nullptr;
        char *  route = nullptr;
        char *  clientHttpHeader = strtok( clientBuffer, "\r\n" );
        char *  headerToken = strtok( clientHttpHeader, " " );

        int headerParseCounter = 0;

        while ( headerToken != nullptr )
        {
            switch ( headerParseCounter )
            {
            case 0:
                methodStr = headerToken;
                break;
            case 1:
                route = headerToken;
                break;
            }
            headerToken = strtok( NULL, " " );
            headerParseCounter++;
        }

        WebServer::Method method;

        if ( methodStr != nullptr && strncmp( "GET", methodStr, 4 ) == 0 )
        {
            method = WebServer::Method::GET;
        }
        else if ( methodStr != nullptr && strncmp( "POST", methodStr, 4 ) == 0 )
        {
            method = WebServer::Method::POST;
        }
        else
        {
            // todo Log
            break;
        }

        auto responseData = std::string();

        if ( route != nullptr && strnlen( route, 256 ) && _routes.find( route ) != _routes.end() )
        {
            auto routeHandler = _routes[ route ];

            auto routeString = std::string( route );
            responseData = routeHandler( session, routeString, method );
            returnCode = 200;
        }
        else
        {            
            returnCode = 404;
        }

        auto headerBuilder = Algo::HeaderBuilder( returnCode );
        headerBuilder.SetContentType( "application/json; charset=utf-8" );
        headerBuilder.SetContentLength( responseData.length() );

        auto response = headerBuilder.BuildHeader() + responseData;

        send( session.GetClientFileDescriptor(), response.c_str(), response.length(), 0 );

    } while ( n > -1 );
}

void
Rest::HandleNewConnection( ConnectionData connectionData )
{
    if ( !_connectHandler.has_value() )
    {
        // ToDo: Log
        return;
    }
    
    auto & connectHandler = _connectHandler.value();
    auto & restSession = connectHandler( connectionData );

    restSession.Thread = std::thread( [&]() -> void { HandleSession( restSession ); } );
}