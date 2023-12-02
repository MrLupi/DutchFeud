#include "MovePart.h"

using namespace DutchFeud;
using namespace DutchFeud::Common;
using namespace DutchFeud::Common::Data;


MovePart::MovePart( PlayFieldLocation location, unsigned int index )
    : _location( location )
    , _index( index )
{
}

const Tile & 
MovePart::GetTile( const TilesCollection & tilesCollection ) const
{
    return tilesCollection.GetTileConst( _index );
}