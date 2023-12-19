#include "FeudServer.h"

#include <typeinfo>

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



void
FeudServer::Start()
{
    _rest.RegisterConnectHandler( std::bind( & FeudServer::HandleNewConnection, this, std::placeholders::_1 ) );
    _rest.RegisterFeudHandler( "/test", std::bind( & FeudServer::HandleTestRequest, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 ) );

    _rest.Start();
}