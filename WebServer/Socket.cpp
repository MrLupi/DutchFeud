#include "Socket.h"

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

std::string
Socket::ToString( SocketState state )
{
    switch ( state )
    {
        case SocketState::Uninitialized:
            return "Uninitialized";
        case SocketState::Initializing:
            return "Initializing";
        case SocketState::InError:
            return "InError";
        case SocketState::Listening:
            return "Listening";
        case SocketState::Accepting:
            return "Accepting";
        case SocketState::Connected:
            return "Connected";
        case SocketState::Receiving:
            return "Receiving";
        case SocketState::Closing:
            return "Closing";
        case SocketState::Closed:
            return "Closed";
        default:
            throw;
        break;
    }
}

Socket::Socket( int port )
    : _serverFileDescriptor( 0 )
    , _socketState( SocketState::Uninitialized )
    , _port( port )
    , _statusMessage()
{
}

void
Socket::Start()
{
    SetState( SocketState::Initializing );
    while ( _socketState != SocketState::Closed )
    {
        HandleState();
    }
}

void
Socket::PrintInfo()
{
    std::cout << "Hello, World" << std::endl;
}

void
Socket::SetState( SocketState state )
{
    std::cout << "Changing state to " << ToString( state ) << "." << std::endl;
    _socketState = state;
}

void
Socket::SetErrorState( std::string message )
{
    auto stream = std::stringstream();
    stream << message;
    
    if ( errno != 0 )
    {
        stream << " ( " << std::string ( std::strerror( errno ) ) << " )";
    }

    _statusMessage = stream.str();
    SetState( SocketState::InError );
}

void 
Socket::HandleState()
{
    switch ( _socketState )
    {
    case SocketState::Uninitialized:        
        break;
    
    case SocketState::Initializing:
        Initialize();
        break;
    case SocketState::Listening:
        Listen();
        break;
    case SocketState::Closing:
        Close();        
        break;
    case SocketState::InError:
        Error();
        break;
    case SocketState::Accepting:
        Accept();
        break;
    default:
        break;
    }
}

void
Socket::Initialize()
{
    int fd = socket( AF_INET, SOCK_STREAM, 0 ); // ToDo: Check out SOCK_NONBLOCK ??
    if ( fd < 0 )
    {
        SetErrorState( "Could not create socket" );
        return;
    }

    _serverFileDescriptor = fd;

    sockaddr_in serverAddress;
    std::memset( & serverAddress, 0, sizeof ( serverAddress ) );

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons( _port );

    auto address = reinterpret_cast< sockaddr* >( & serverAddress );
    auto addressSize = sizeof ( serverAddress );

    if ( bind( _serverFileDescriptor, address, addressSize ) < 0 )
    {
        SetErrorState( "Could not bind." );
        return;
    }
    SetState( SocketState::Listening );
}

void
Socket::Error()
{
    std::cerr << _statusMessage << std::endl;
    SetState( SocketState::Closing );
}

void
Socket::Listen()
{
    const int maximumNumberOfConnections = 5;

    if ( listen( _serverFileDescriptor, maximumNumberOfConnections ) < 0  )
    {
        SetErrorState( "Could not listen" );
        return;
    }
    SetState( SocketState::Accepting );
}

void Socket::Accept()
{
    int clientFileDescriptor;
    struct sockaddr_in clientaddress;
    socklen_t clientAddresSize = sizeof( clientaddress );

    clientFileDescriptor = accept( _serverFileDescriptor, ( struct sockaddr * ) & clientaddress, & clientAddresSize );
    if ( clientFileDescriptor < 0 )
    {
        SetErrorState( "Could not accept connection" );
        return;
    }

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

    SetState( SocketState::Closing );
}

void
Socket::Close()
{
    CleanUp();
    SetState( SocketState::Closed );
}

void
Socket::CleanUp()
{
    if ( _serverFileDescriptor != 0 )
    {
        close( _serverFileDescriptor );
        _serverFileDescriptor = 0;
    }
}
