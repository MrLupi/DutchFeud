#include "GameStore.h"

using namespace DutchFeud::Common::Data;

GameStore::GameStore()
    : _gameIdGameMap()
{
}

void
GameStore::AddGame( std::shared_ptr< Game > gamePtr )
{
    _gameIdGameMap[ gamePtr->GetGuid() ] = gamePtr;
}
