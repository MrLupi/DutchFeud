#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

#include "Common/Data/Player.h"

namespace DutchFeud::Common::Data
{
    class PlayerStore
    {
        private:
        std::unordered_map< std::string, std::shared_ptr< Player > > _playerIdPlayerMap;
        std::unordered_map< std::wstring, std::shared_ptr< Player > > _playerNamePlayerMap;

        public:
        PlayerStore();
        
        void AddPlayer( std::shared_ptr< Player > playerPtr );
    };
}