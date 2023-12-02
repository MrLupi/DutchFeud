#pragma once

#include <functional>
#include <vector>

#include "Common/Data/MovePart.h"
#include "Common/Data/TilesCollection.h"

namespace DutchFeud::Common::Data
{
    class Move
    {
        private:
        std::vector< MovePart > _parts;
        const std::reference_wrapper< const TilesCollection > _tilesCollection;
        
        public:
        Move( const TilesCollection & tilesCollection );
    };
}