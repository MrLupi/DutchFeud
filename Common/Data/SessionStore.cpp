#include "SessionStore.h"

using namespace DutchFeud;
using namespace DutchFeud::Common;
using namespace DutchFeud::Common::Data;


SessionStore::SessionStore()
{

}

void
SessionStore::AddSession( std::shared_ptr< Session > sessionPtr )
{
    _sessionIdSessionMap[ sessionPtr->getGuid() ] = sessionPtr;
}