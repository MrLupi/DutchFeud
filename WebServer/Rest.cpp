#include "Rest.h"

#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>
#include <unistd.h>

#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>

using namespace DutchFeud;
using namespace DutchFeud::Webserver;


Rest::Rest( int port )
    : Socket( port )
{

}


void
Rest::HandleNewConnection( int clientFileDescriptor )
{

    const char *body = "<html><body><h1>Hello World!</h1></body></html>";

    // Calculate Content-Length
    size_t contentLength = strlen( body );

    // Create the HTTP response header
    char header[1024];
    snprintf( header, sizeof( header ), "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %zu\r\n\r\n", contentLength );

    // Concatenate header and body to form the complete HTTP response
    char responseBuffer[10240];
    memset( responseBuffer, '\0', sizeof( responseBuffer ) );
    strcat( responseBuffer, header );
    strcat( responseBuffer, body );

    char clientBuffer[10240];

    int n = 0;

    while ( n > -1 )
    {
        memset( clientBuffer, '\0', sizeof( clientBuffer ) );

        int n = recv( clientFileDescriptor, clientBuffer, 10240, 0 );
        printf( "n = %d\n\n", n );

        if ( n < 1 )
        {
            break;
        }

        printf( "%s\n\n", clientBuffer );

        char *method = nullptr;
        char *route = nullptr;

        char *clientHttpHeader = strtok( clientBuffer, "\r\n" );

        printf( "%s\n\n", clientHttpHeader );

        char *headerToken = strtok( clientHttpHeader, " " );

        int headerParseCounter = 0;

        while ( headerToken != nullptr )
        {
            switch ( headerParseCounter )
            {
            case 0:
                method = headerToken;
                break;
            case 1:
                route = headerToken;
                break;
            }
            headerToken = strtok( NULL, " " );
            headerParseCounter++;
        }

        printf( "The method is: %s\n", method );
        printf( "The route is: %s\n", route );

        // Send the HTTP response to the client
        send( clientFileDescriptor, responseBuffer, strlen( responseBuffer ), 0 );
    }
}