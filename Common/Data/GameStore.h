#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

#include "Common/Data/Game.h"

namespace DutchFeud::Common::Data
{
    class GameStore
    {
        private:
        std::unordered_map< std::string, std::shared_ptr< Game > > _gameIdGameMap;

        public:
        GameStore();
        void AddGame( std::shared_ptr< Game > gamePtr );
    };
}