#include "FeudServer.h"

#include <typeinfo>

#include "Server/Algo/GetServerVersion.h"

#include "Common/Data/Session.h"
#include "WebServer/Socket.h"

using namespace DutchFeud;
using namespace DutchFeud::Server;

FeudServer::FeudServer()
    : _playerStore()
    , _gameStore()
    , _sessionStore()
    , _rest( 8080 )
{
}

WebServer::RestSession &
FeudServer::HandleNewConnection( WebServer::ConnectionData connectionData )
{
    auto session = std::make_shared< Common::Data::Session >( connectionData.Host, connectionData.ClientFileDescriptor );
    _sessionStore.AddSession( session );

    return * session;
}

std::string
FeudServer::HandleTestRequest( WebServer::RestSession & restSession, std::string & response, WebServer::Method method )
{
    if ( auto feudSession = dynamic_cast< Common::Data::Session * >( & restSession ) )
    {
        if ( method != WebServer::Method::GET )
        {
            return std::string();
        }

        if ( response.length() == 0 )
        {
            return std::string();
        }

        return "[{\"ip\":\"" + feudSession->GetIpAddress() + "\", \"sessionId\":\"" + feudSession->getGuid() + "\"}]";
    }
    return std::string();
}

std::string
FeudServer::HandleVersionRequest( WebServer::RestSession & restSession, std::string & response, WebServer::Method method )
{
    if ( dynamic_cast< Common::Data::Session * >( & restSession ) )
    {
        if ( method != WebServer::Method::GET )
        {
            return std::string();
        }

        if ( response.length() == 0 )
        {
            return std::string();
        }

        return "[{\"serverVersion\":\"" + Algo::GetServerVersion().Execute() + "\"}]";
    }
    return std::string();
}


void
FeudServer::Start()
{
    _rest.RegisterConnectHandler( std::bind( & FeudServer::HandleNewConnection, this, std::placeholders::_1 ) );
    _rest.RegisterFeudHandler( "/test", std::bind( & FeudServer::HandleTestRequest, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 ) );
    _rest.RegisterFeudHandler( "/version", std::bind( & FeudServer::HandleVersionRequest, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 ) );

    _rest.Start();
}

WebServer::RouteHandler 
FeudServer::BindForRouteHandler( FeudServer::TESTTYPE & testType )
{
    return std::bind( testType, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 );
}

