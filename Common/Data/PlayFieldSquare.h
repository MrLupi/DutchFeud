#pragma once

#include <optional>


#include "Common/Data/Tile.h"

namespace DutchFeud::Common::Data
{
    class PlayFieldSquare
    {        
        public:
        static const unsigned int DefaultMultiplier = 1;
        static const unsigned int VariantAMultiplier = 2;
        static const unsigned int VariantBMultiplier = 3;

        private:
        unsigned int _multiplier;
        std::optional< Tile > _oTile;

        public:
        PlayFieldSquare();
        PlayFieldSquare( unsigned int multiplier );

        unsigned int GetMultiplier() const;

        void SetMultiplier( unsigned int multiplier );

        bool HasTile() const;

        const Tile & GetTile() const;

        void SetTile( Tile & tile );    
    };
}