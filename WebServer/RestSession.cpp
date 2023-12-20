#include "RestSession.h"

using namespace DutchFeud;
using namespace DutchFeud::WebServer;

RestSession::RestSession( std::string ipAddress, int clientFileDescriptor )
    : _ipAddress( ipAddress )
    , _clientFileDescriptor( clientFileDescriptor )
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