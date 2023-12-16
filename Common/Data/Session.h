#pragma once

#include <thread>
#include <functional>
#include <optional>

#include "Common/Data/Player.h"

namespace DutchFeud::Common::Data
{
    class Session
    {
    private:
        std::optional< std::reference_wrapper< Player > > _oPlayer;

    public:
        Session();
    };
    

}
