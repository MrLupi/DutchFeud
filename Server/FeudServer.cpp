#include "FeudServer.h"

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

Webserver::RestSession &
HandleNewConnection( Webserver::ConnectionData connectionData )
{
    auto session = std::make_shared< Common::Data::Session >( connectionData.Host, connectionData.ClientFileDescriptor );
    


    return * session;
}



void
FeudServer::Start()
{
    // _rest.RegisterHandler( "/", std::bind( &FeudServer::HandleIndexRequest, this ) );
    // _rest.RegisterHandler( "/feud", std::bind( &FeudServer::HandleFeudRequest, this ) );
    _rest.RegisterConnectHandler( HandleNewConnection );
    _rest.Start();
}