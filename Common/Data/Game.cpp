#include "Game.h"

#include "Common/Algo/GenerateRandomGuid.h"

using namespace DutchFeud;
using namespace DutchFeud::Common;
using namespace DutchFeud::Common::Data;

Game::Game( Player & player1, Player & player2, PlayField::Layout layout, unsigned int setCount )
    : _player1( player1 )
    , _player2( player2 )
    , _playfield( layout )
    , _gameTiles( setCount )
    , _player1Tiles()
    , _player2Tiles()
    , _lock()
{
    _state = GameState::UnInitialized;
    SetRandomTurn();
}

std::string
Game::GetGuid() const
{
    return _guid;
}

void
Game::SetRandomTurn()
{
    const auto isEven = ( rand() % 100 + 1 ) % 2;
    _turn = isEven ? Turn::Player1 : Turn::Player2;
}

void
Game::SetRandomGuid()
{
    _guid = Algo::GenerateRandomGuid()();
}

void 
Game::SwitchTurn()
{
    _turn = _turn == Turn::Player1 ? Turn::Player2 : Turn::Player1;
}
