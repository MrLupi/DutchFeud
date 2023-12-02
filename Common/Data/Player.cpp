#include "Player.h"

using namespace DutchFeud;
using namespace DutchFeud::Common;
using namespace DutchFeud::Common::Data;


Player::Player()
{

}

const std::string &
Player::GetGuid() const
{
    return _guid;
}

const std::wstring &
Player::GetName() const
{
    return _name;
}
