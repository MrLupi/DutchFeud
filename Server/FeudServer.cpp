#include "FeudServer.h"

using namespace DutchFeud;
using namespace DutchFeud::Server;

FeudServer::FeudServer()
    : _rest( 8080 )
{
}



void
FeudServer::Start()
{
    // _rest.RegisterHandler( "/", std::bind( &FeudServer::HandleIndexRequest, this ) );
    // _rest.RegisterHandler( "/feud", std::bind( &FeudServer::HandleFeudRequest, this ) );
    _rest.Start();
}