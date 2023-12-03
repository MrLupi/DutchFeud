#include <iostream>

#include "FeudServer.h"

using namespace DutchFeud;

int
main( int , char ** ) 
{   
    auto server = DutchFeud::Server::FeudServer();

    server.Start();

    return 0;
}