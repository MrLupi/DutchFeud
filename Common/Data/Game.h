#pragma once

#include <cinttypes>
#include <functional>
#include <mutex>
#include <uuid/uuid.h>

#include "Common/Data/PlayField.h"
#include "Common/Data/Player.h"
#include "Common/Data/TilesCollection.h"


namespace DutchFeud::Common::Data
{
    enum class GameState
    {
        UnInitialized,
        NotStarted,
        InProgress,
        Completed,
        Cancelled,
        NoLongerReferenced
    };

    enum class Turn
    {
        Player1,
        Player2
    };

    enum class Winner
    {
        Undefnined,
        Player1,
        Player2,
        Tie
    };

    class Game
    {
        private:
        std::string _guid;
        std::reference_wrapper< Player > _player1;
        std::reference_wrapper< Player > _player2;        
        PlayField _playfield;
        TilesCollection _gameTiles;
        TilesCollection _player1Tiles;
        TilesCollection _player2Tiles;
        GameState _state;
        Turn _turn;
        Winner _winner;
        std::mutex _lock;

        public:
        Game( Player & player1, Player & player2, PlayField::Layout layout, unsigned int setCount );
        std::string GetGuid() const;


        private:
        void SetRandomTurn();
        void SetRandomGuid();
        void SwitchTurn();
    };
}