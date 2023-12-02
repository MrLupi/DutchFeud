#include "Tile.h"

using namespace DutchFeud;
using namespace DutchFeud::Common;
using namespace DutchFeud::Common::Data;

Tile::Tile()
    : _shape( Shape::Undefined )
    , _color( Color::Undefined )
{    
}

Tile::Tile( Shape shape, Color color )
    : _shape( shape )
    , _color( color )
{
}

bool 
Tile::operator==( const Tile & otherTile ) const
{
    return otherTile._color == _color
        && otherTile._shape == _shape; 
}

bool 
Tile::operator!=( const Tile & otherTile ) const
{
    return !operator==( otherTile );
}

const Tile::Shape &
Tile::GetShape() const
{
    return _shape;
}

const Tile::Color &
Tile::GetColor() const
{
    return _color;
}
