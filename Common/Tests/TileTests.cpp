#define BOOST_TEST_MODULE TileTests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "Common/Data/Tile.h"

using namespace DutchFeud::Common::Data;

Tile::Shape shapes[] = { Tile::Shape::Bicycle, Tile::Shape::Cheese, Tile::Shape::Clogs, Tile::Shape::Lion, Tile::Shape::Tulip, Tile::Shape::Windmill };
Tile::Color colors[] = { Tile::Color::Blue, Tile::Color::Green, Tile::Color::Orange, Tile::Color::Purple, Tile::Color::Red, Tile::Color::Yellow }; 

BOOST_AUTO_TEST_CASE( DefaultTileIsUndefined )
{
    const auto expectedTileShape = Tile::Shape::Undefined;
    const auto expectedTileColor = Tile::Color::Undefined;
    
    const auto defaultTile = Tile();
    const auto & actualTileShape = defaultTile.GetShape();
    const auto & actualTileColor = defaultTile.GetColor();

    BOOST_CHECK( actualTileShape == expectedTileShape );
    BOOST_CHECK( actualTileColor == expectedTileColor );
}

BOOST_AUTO_TEST_CASE( DefaultTileDoesNotMatchValidTilesEquals )
{
    const auto expectedEquals = false;

    const auto defaultTile = Tile();

    for ( const auto shape : shapes )
    {
        for ( const auto color : colors )
        {
            const auto validTile = Tile( shape, color );
            const auto actualEquals = defaultTile == validTile;

            BOOST_CHECK( actualEquals == expectedEquals );
        }
    }
}

BOOST_AUTO_TEST_CASE( DefaultTileDoesNotMatchValidTilesNotEquals )
{
    const auto expectedEquals = true;

    const auto defaultTile = Tile();

    for ( const auto shape : shapes )
    {
        for ( const auto color : colors )
        {
            const auto validTile = Tile( shape, color );
            const auto actualEquals = defaultTile != validTile;

            BOOST_CHECK( actualEquals == expectedEquals );
        }
    }
}

BOOST_AUTO_TEST_CASE( TilesEqualNotEqualTest )
{
    const auto tile1 = Tile( Tile::Shape::Windmill, Tile::Color::Blue );
    const auto tile2a = Tile( Tile::Shape::Windmill, Tile::Color::Orange );
    const auto tile2b = Tile( Tile::Shape::Windmill, Tile::Color::Orange );
    const auto tile3 = Tile( Tile::Shape::Cheese, Tile::Color::Orange );

    BOOST_CHECK( tile1 != tile2a );
    BOOST_CHECK( tile2a != tile3 );
    BOOST_CHECK( tile3 != tile1 );

    BOOST_CHECK( tile2a == tile2b );
}

BOOST_AUTO_TEST_CASE( TileHasCorrectShapeAndColor )
{
    const auto expectedShape = Tile::Shape::Clogs;
    const auto expectedColor = Tile::Color::Green;

    const auto tile = Tile( expectedShape, expectedColor );

    const auto actualShape = tile.GetShape();
    const auto actualColor = tile.GetColor();

    BOOST_CHECK( actualShape == expectedShape );
    BOOST_CHECK( actualColor == expectedColor );
}

//BOOST_DATA_TEST_CASE( NotEqualOperatorTests, boost::unit_test::data::make( shapes ), shape_value )
//{
//    const auto lhs = new Tile();
//    for( auto color : colors )
//    {
//        const auto rhs = new Tile( shape_value, color );
//
//        BOOST_CHECK( lhs != rhs );
//    }
//}