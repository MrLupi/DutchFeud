#define BOOST_TEST_MODULE PlayFieldSquareTests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "Common/Data/PlayFieldSquare.h"

using namespace DutchFeud::Common::Data;

BOOST_DATA_TEST_CASE( CorrectMultiplierIsSet, boost::unit_test::data::make( { 0, 1, 2, 3, 5, 100, 1000 } ), multiplier_value )
{
    const unsigned int expectedMultiplier = multiplier_value;

    const auto square = PlayFieldSquare( expectedMultiplier );

    const auto actualMultiplier = square.GetMultiplier();

    BOOST_CHECK( actualMultiplier == expectedMultiplier );
}

BOOST_DATA_TEST_CASE( PlayFieldSquareSetMultiplierWorks, boost::unit_test::data::make( { 0, 1, 2, 3, 5, 100, 1000 } ), multiplier_value )
{
    const unsigned int expectedMultiplier = multiplier_value;

    auto square = PlayFieldSquare();

    square.SetMultiplier( multiplier_value );

    const auto actualMultiplier = square.GetMultiplier();

    BOOST_CHECK( actualMultiplier == expectedMultiplier );
}

BOOST_AUTO_TEST_CASE( NewPlayFieldSquareHasNoTile )
{
    const auto expectedHasTile = false;

    const auto square = PlayFieldSquare( 1u );

    const auto actualHasTile  = square.HasTile();

    BOOST_CHECK( actualHasTile == expectedHasTile );
}

BOOST_AUTO_TEST_CASE( PlayFieldSquareReturnsCorrectTile )
{
    const auto expectedHasTile = true;
    auto expectedTile = Tile( Tile::Shape::Tulip, Tile::Color::Purple );

    auto square = PlayFieldSquare( 1u );
    square.SetTile( expectedTile );

    const auto actualHasTile = square.HasTile();
    const auto actualTile = square.GetTile();

    BOOST_CHECK( actualHasTile == expectedHasTile );
    BOOST_CHECK( actualTile == expectedTile );
}


