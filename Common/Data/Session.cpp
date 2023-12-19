#include "Session.h"

#include "Common/Algo/GenerateRandomGuid.h"

using namespace DutchFeud;
using namespace DutchFeud::Common;
using namespace DutchFeud::Common::Data;


Session::Session( std::string ipAddress, int clientFileDescriptor )
    : RestSession( ipAddress, clientFileDescriptor )
    , _oPlayer( std::nullopt )
{
    _guid = Algo::GenerateRandomGuid()();
}

const std::string &
Session::getGuid() const
{
    return _guid;
}