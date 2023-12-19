#include "RestSession.h"

using namespace DutchFeud;
using namespace DutchFeud::WebServer;

RestSession::RestSession( std::string ipAddress, int clientFileDescriptor )
    : _oThread( std::nullopt )
    , _ipAddress( ipAddress )
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