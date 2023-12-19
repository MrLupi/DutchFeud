#pragma once

#include <string>

namespace DutchFeud::Common::Algo
{
    class GenerateRandomGuid
    {
        public:
        std::string operator()();
    };
}