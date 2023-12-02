#include <iostream>

#include "WebServer/Socket.h"

using namespace DutchFeud::Webserver;

int
main( int , char ** ) 
{   
    auto sock = Socket( 8080 );

    sock.Start();

    return 0;
}