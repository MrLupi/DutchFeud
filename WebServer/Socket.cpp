#include "Socket.h"

#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>
#include <unistd.h>

#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>

#include "General/Algo/Logger.h"

using namespace DutchFeud;
using namespace DutchFeud::WebServer;

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
Socket::SetState( SocketState state )
{
    auto ss = std::stringstream();
    ss << "Changing state to " << ToString( state ) << "." << std::endl;

    auto log = General::Algo::LogManager::GetCurrentClassLogger();
    log.Trace( ss.str() );
    
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

    struct sockaddr_in* pV4Addr = (struct sockaddr_in*) & clientaddress;
    struct in_addr ipAddr = pV4Addr->sin_addr;
    
    char ipAddress[INET_ADDRSTRLEN];
    
    inet_ntop( AF_INET, &ipAddr, ipAddress, INET_ADDRSTRLEN );
    
    auto connectionData = ConnectionData();
    connectionData.ClientFileDescriptor = clientFileDescriptor;
    connectionData.Host = ipAddress;

    HandleNewConnection( connectionData );


    SetState( SocketState::Accepting );
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
