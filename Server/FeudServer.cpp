#include "FeudServer.h"

using namespace DutchFeud;
using namespace DutchFeud::Server;

FeudServer::FeudServer()
    : _socket( 8080 )
{
}

void
FeudServer::Start()
{
    _socket.Start();
}