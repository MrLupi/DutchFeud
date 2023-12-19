#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Common/Data/Session.h"

namespace DutchFeud::Common::Data
{
    class SessionStore
    {
    private:
        std::unordered_map< std::string, std::shared_ptr< Session > > _sessionIdSessionMap;
    public:
        SessionStore();

        void AddSession( std::shared_ptr< Session > sessionPtr );
    };
}
