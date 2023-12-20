#include "RestSession.h"

using namespace DutchFeud;
using namespace DutchFeud::WebServer;

RestSession::RestSession( std::string ipAddress, int clientFileDescriptor, SSL * sslDescriptor )
    : _ipAddress( ipAddress )
    , _clientFileDescriptor( clientFileDescriptor )
    , _sslDescriptor( sslDescriptor )
{
}

RestSession::~RestSession()
{
}

const std::string &
RestSession::GetIpAddress() const
{
    return _ipAddress;
}


int
RestSession::GetClientFileDescriptor() const
{
    return _clientFileDescriptor;
}

SSL * 
RestSession::GetSSLDescriptor() const
{
    return _sslDescriptor;
}