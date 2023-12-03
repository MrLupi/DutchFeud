#pragma once

#include "Common/Data/PlayerStore.h"
#include "Common/Data/GameStore.h"
#include "Common/Data/SessionStore.h"
#include "WebServer/Socket.h"

namespace DutchFeud::Server
{
    class FeudServer
    {
    private:
        Common::Data::PlayerStore _playerStore;
        Common::Data::GameStore _gameStore;
        Common::Data::SessionStore _sessionStore;

        Webserver::Socket _socket;


    public:
        FeudServer();

        void Start();
    };
}