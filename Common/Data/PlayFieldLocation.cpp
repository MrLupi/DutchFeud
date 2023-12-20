#include "PlayFieldLocation.h"

using namespace DutchFeud::Common::Data;


PlayFieldLocation::PlayFieldLocation( unsigned int x, unsigned int y )
    : X( x )
    , Y( y )
{
}


bool 
PlayFieldLocation::operator==( const PlayFieldLocation & other ) const
{
    return X == other.X && Y == other.Y;
}

bool 
PlayFieldLocation::operator!=( const PlayFieldLocation & other ) const
{
    return !operator==( other );
}