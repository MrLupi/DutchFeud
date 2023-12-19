#pragma once

#include <thread>
#include <functional>
#include <optional>

#include "Common/Data/Player.h"
#include "WebServer/RestSession.h"

namespace DutchFeud::Common::Data
{
    class Session : public Webserver::RestSession
    {
    private:
        std::string _guid;
        std::optional< std::reference_wrapper< Player > > _oPlayer;

    public:
        Session( std::string ipAddress, int clientFileDescriptor );

        const std::string & getGuid() const;
    };
    

}
