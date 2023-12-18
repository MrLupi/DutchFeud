#include "PlayFieldSquare.h"

#include <cassert>

using namespace DutchFeud;
using namespace DutchFeud::Common;
using namespace DutchFeud::Common::Data;


PlayFieldSquare::PlayFieldSquare()
: PlayFieldSquare( DefaultMultiplier )
{    
}

PlayFieldSquare::PlayFieldSquare( unsigned int multiplier )
    : _multiplier( multiplier )
    , _oTile( std::nullopt )
{
}

unsigned int
PlayFieldSquare::GetMultiplier() const
{
    return _multiplier;
}

void
PlayFieldSquare::SetMultiplier( unsigned int multiplier )
{
    _multiplier = multiplier;
}

bool 
PlayFieldSquare::HasTile() const
{
    return _oTile.has_value();
}

const Tile &
PlayFieldSquare::GetTile() const
{
    assert( _oTile.has_value() );

    const auto & tile = _oTile.value();

    return tile;
}

void
PlayFieldSquare::SetTile( Tile & tile )   
{
    assert( !_oTile.has_value() );

    _oTile.emplace( tile );
}
