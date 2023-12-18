#pragma once

#include "Common/Data/PlayFieldLocation.h"
#include "Common/Data/TilesCollection.h"

namespace DutchFeud::Common::Data
{
    class MovePart
    {
        private:
        PlayFieldLocation _location;
        unsigned int _index;

        public:
        MovePart( PlayFieldLocation location, unsigned int index );

        const Tile & GetTile( const TilesCollection & tilesCollection ) const;
    };
}