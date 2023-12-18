#include "Session.h"

using namespace DutchFeud;
using namespace DutchFeud::Common;
using namespace DutchFeud::Common::Data;


Session::Session( std::string ipAddress, int clientFileDescriptor )
    : RestSession( ipAddress, clientFileDescriptor )
    , _oPlayer( std::nullopt )
{

}