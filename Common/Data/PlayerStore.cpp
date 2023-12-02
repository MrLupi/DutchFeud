#include "PlayerStore.h"

using namespace DutchFeud;
using namespace DutchFeud::Common;
using namespace DutchFeud::Common::Data;

PlayerStore::PlayerStore()
    : _playerIdPlayerMap()
    , _playerNamePlayerMap()
{
}

void
PlayerStore::AddPlayer( std::shared_ptr< Player > playerPtr )
{
    _playerIdPlayerMap[ playerPtr->GetGuid() ] = playerPtr;
    _playerNamePlayerMap[ playerPtr->GetName() ] = playerPtr;
}