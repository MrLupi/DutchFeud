#pragma once

#include "Common/Data/PlayerStore.h"
#include "Common/Data/GameStore.h"
#include "Common/Data/SessionStore.h"
#include "WebServer/Rest.h"

namespace DutchFeud::Server
{
    class FeudServer
    {
    private:
        Common::Data::PlayerStore _playerStore;
        Common::Data::GameStore _gameStore;
        Common::Data::SessionStore _sessionStore;

        Webserver::Rest _rest;


    public:
        FeudServer();
        void Start();
        Webserver::RestSession & HandleNewConnection( Webserver::ConnectionData connectionData );
    };
}