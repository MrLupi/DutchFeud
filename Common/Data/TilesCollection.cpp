#include "TilesCollection.h"

#include <algorithm>
#include <cassert>
#include <random>
#include <ranges>
#include <type_traits>

using namespace DutchFeud;
using namespace DutchFeud::Common;
using namespace DutchFeud::Common::Data;


TilesCollection::TilesCollection()
    : _tiles()
{
}

TilesCollection::TilesCollection( unsigned int numberOfSets )
    : _tiles()
{
    assert ( numberOfSets <= 4 );
    for ( auto i = numberOfSets; i > 0; i-- )
    {
        AddSetToTiles();
    }

    Shuffle();
}

unsigned int
TilesCollection::GetNumberOfTiles() const
{
    return _tiles.size();
}

void
TilesCollection::Shuffle()
{
    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };
    std::shuffle( std::begin(_tiles ), std::end( _tiles ), rng );
}

void
TilesCollection::Deal( TilesCollection & otherTileCollection, unsigned int numberOfTiles )
{
    assert ( GetNumberOfTiles() >= numberOfTiles );

    for ( ; numberOfTiles > 0; numberOfTiles-- )
    {
        auto tile = _tiles.back();
        otherTileCollection._tiles.push_back( tile );
        _tiles.pop_back();
    }
}

const Tile &
TilesCollection::GetTileConst( unsigned int index ) const
{
    assert ( index < GetNumberOfTiles() );

    const auto & tile = _tiles[ index ];
    return tile;
}


void
TilesCollection::AddSetToTiles()
{
    for ( auto s = static_cast< Tile::TShapeUnderlying >( Tile::Shape::Undefined ) + 1
        ; s < static_cast< Tile::TShapeUnderlying >( Tile::Shape::ShapeCount )
        ; s++ )
    {
        for ( auto c = static_cast< Tile::TColorUnderlying >( Tile::Color::Undefined ) + 1
            ; c < static_cast< Tile::TColorUnderlying >( Tile::Color::ColorCount )
            ; c++ )
        {
            auto shape = static_cast< Tile::Shape >( s );
            auto color = static_cast< Tile::Color >( c );
            _tiles.emplace_back( shape, color );
        }
    }
}