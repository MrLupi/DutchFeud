#pragma once

#include <vector>

#include "Common/Data/Tile.h"

namespace DutchFeud::Common::Data
{
    class TilesCollection
    {
        public:
        static const unsigned int MaximumNumberOfSets = 4;

        private:
        std::vector< Tile > _tiles;

        public:
        TilesCollection();
        TilesCollection( unsigned int numberOfSets );
        
        unsigned int GetNumberOfTiles() const;

        void Shuffle();
        void Deal( TilesCollection & otherTileCollection, unsigned int numberOfTiles );
        const Tile & GetTileConst( unsigned int index ) const;


        private:
        void AddSetToTiles();
    };
}