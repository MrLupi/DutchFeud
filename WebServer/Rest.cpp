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
    _log.Debug ( "Connection established with '" + session.GetIpAddress() + "'" );

    char clientBuffer[ BUFFER_SIZE ];
    const auto clientBufferSize = sizeof ( clientBuffer );

    int messageLength;

    do
    {   
        messageLength = 0; 
        memset( clientBuffer, '\0', clientBufferSize );

        messageLength = SSL_read( session.GetSSLDescriptor(), clientBuffer, clientBufferSize );

        ValidateMessageLength( messageLength, clientBufferSize );

        char * methodStr = nullptr;
        char * route = nullptr;
        char * clientHttpHeader = strtok( clientBuffer, "\r\n" );
        char * headerToken = strtok( clientHttpHeader, " " );

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

        int returnCode;
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

        SSL_write( session.GetSSLDescriptor(), response.c_str(), response.length() );

    }
    while ( messageLength > 0 );
    
    _log.Debug( "Connection ended for '" + session.GetIpAddress() + "'" );
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

bool
Rest::ValidateMessageLength( size_t messageLength, size_t messageAllocatedSize ) const
{
    if ( messageLength < 0 )
    {             
        _log.Error( "While receiving: '" + std::string ( std::strerror( errno ) ) + "'" );
        return false;            
    }

    if ( messageLength == 0 )
    {
        _log.Info( "Client has performed an orderly shutdown" );
        return false;
    }

    if ( messageLength > messageAllocatedSize )
    {
        _log.Error( "Client sent message beyond buffer size" );
        return false;
    }

    const int REST_MAXIMUM_MESSAGE_SIZE = 1024;
    if ( messageLength > REST_MAXIMUM_MESSAGE_SIZE )
    {
        auto message = std::stringstream();
        message << "Not expecting messages to exceed '" << REST_MAXIMUM_MESSAGE_SIZE << "' bytes. Current message size is '" << messageLength << "'bytes. Terminating connection";
        _log.Error( message.str() ); 
        return false;
    }

    return true;
}