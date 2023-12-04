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
    _rest.Start();
}