#include "PlayField.h"

#include <cassert>
#include <cstdlib>
#include <iostream>

#include "Common/Data/PlayFieldLocation.h"

using namespace DutchFeud;
using namespace DutchFeud::Common;
using namespace DutchFeud::Common::Data;

PlayField::PlayField( Layout layout )
{
    switch ( layout )
    {
        case PlayField::Layout::Default:
            InitializeDefaultPlayField();
            break;        
        case PlayField::Layout::Empty: 
            break;
        case PlayField::Layout::Random:
            InitializeRandomPlayField();
            break;
        default:
            assert( false );
        break;
    }
}

unsigned int
PlayField::GetMultiplier( const PlayFieldLocation & location ) const
{
    const auto & square = GetSquareConst( location );
    return square.GetMultiplier();
}

void 
PlayField::InitializeDefaultPlayField()
{
    const PlayFieldLocation VariantAMultiplierLocations[] =
    { 
        {0, 0}, {14, 0}, {14, 14}, {0, 14},
        {1, 1}, {13, 1}, {13, 13}, {1, 13},
        {2, 2}, {12, 2}, {12, 12}, {2, 12},
        {4, 4}, {10, 4}, {10, 10}, {4, 10},
        {5, 5}, {9, 5}, {9, 9}, {5, 9}
    };

    for ( const auto & location : VariantAMultiplierLocations )
    {
        auto & square = GetSquare( location );
        square.SetMultiplier( PlayFieldSquare::VariantAMultiplier );
    }

    const PlayFieldLocation VariantBMultiplierLocations[] = 
    { 
        {7, 0}, {14, 7}, {7, 14}, {0, 7},
        {3, 3}, {7, 3}, {11, 3}, {11, 7}, {11, 11}, {7, 11}, {3, 11}, {3, 7}
    };

    for ( const auto & location : VariantBMultiplierLocations )
    {
        auto & square = GetSquare( location );
        square.SetMultiplier( PlayFieldSquare::VariantBMultiplier );
    }
}


void 
PlayField::InitializeRandomPlayField()
{
    // ToDo: Move this to a general place to be called a single time. Or handle randomness different somehow.
    srand((unsigned) time(NULL));

    SetRandomMultipliers( RandomVariantACount, PlayFieldSquare::VariantAMultiplier );
    SetRandomMultipliers( RandomVariantBCount, PlayFieldSquare::VariantBMultiplier );
}


PlayFieldSquare & 
PlayField::GetSquare( const PlayFieldLocation & location )
{
    assert ( location.X < PlayFieldSize && location.Y < PlayFieldSize );

    return _squares[location.X][location.Y];
}

const PlayFieldSquare &
PlayField::GetSquareConst( const PlayFieldLocation & location ) const
{
    assert ( location.X < PlayFieldSize && location.Y < PlayFieldSize );

    return _squares[location.X][location.Y];
}


void
PlayField::SetRandomMultipliers(  unsigned int count, unsigned int value )
{
    assert ( value > 1 );

    while ( count > 0 )
    {
        const auto location = PlayFieldLocation( rand() % PlayFieldSize, rand() % PlayFieldSize );
        auto & square = GetSquare( location );
        if ( square.GetMultiplier() == 1 )
        {
            square.SetMultiplier( value );
            count--;
        }
    }
}
