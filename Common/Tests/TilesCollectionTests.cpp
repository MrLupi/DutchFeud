#define BOOST_TEST_MODULE TilesCollectionTests

#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <vector>

#include "Common/Data/TilesCollection.h"

using namespace DutchFeud::Common::Data;

Tile::Shape shapes[] = { Tile::Shape::Bicycle, Tile::Shape::Cheese, Tile::Shape::Clogs, Tile::Shape::Lion, Tile::Shape::Tulip, Tile::Shape::Windmill };
Tile::Color colors[] = { Tile::Color::Blue, Tile::Color::Green, Tile::Color::Orange, Tile::Color::Purple, Tile::Color::Red, Tile::Color::Yellow }; 

BOOST_AUTO_TEST_CASE( TestAmountOfTiles1 )
{
    const auto expectedNumberOfTiles = 36;
    
    const auto tilesCollection = TilesCollection( 1 );
    const auto actualNumberOfTiles = tilesCollection.GetNumberOfTiles();

    BOOST_CHECK_EQUAL( expectedNumberOfTiles, actualNumberOfTiles );
}

BOOST_AUTO_TEST_CASE( DefaultConstructorHasNoTiles )
{
    const auto expectedNumberOfTiles = 0;
    
    const auto tilesCollection = TilesCollection();
    const auto actualNumberOfTiles = tilesCollection.GetNumberOfTiles();

    BOOST_CHECK_EQUAL( expectedNumberOfTiles, actualNumberOfTiles );
}

BOOST_DATA_TEST_CASE( 
    TestAmountOfTiles2, 
    boost::unit_test::data::make( std::vector< std::tuple< int,int > >{ { 1, 36 }, { 2, 72 }, { 3, 108 }, { 4, 144 } } ),
    numberOfSets,
    expectedNumberOfTiles )
{
    const auto tilesCollection = TilesCollection( numberOfSets );
    const auto actualNumberOfTiles = tilesCollection.GetNumberOfTiles();

    BOOST_CHECK_EQUAL( expectedNumberOfTiles, actualNumberOfTiles );
}

BOOST_AUTO_TEST_CASE( NumberOfTilesAreCorrectAfterMove )
{   
    const auto numberOfTilesToMove = 7;

    auto gameTilesCollection = TilesCollection( 1 );
    auto playerTilesCollection = TilesCollection();

    const auto expectedNumberOfGameTilesBeforeMove = 36;
    const auto expectedNumberOfPlayerTilesBeforeMove = 0;

    const auto actualNumberOfGameTilesBeforeMove = gameTilesCollection.GetNumberOfTiles();
    const auto actualNumberOfPlayerTilesBeforeMove = playerTilesCollection.GetNumberOfTiles();

    const auto expectedNumberOfGameTilesAfterMove = actualNumberOfGameTilesBeforeMove - numberOfTilesToMove;
    const auto expectedNumberOfPlayerTilesAfterMove = actualNumberOfPlayerTilesBeforeMove + numberOfTilesToMove;

    gameTilesCollection.Deal( playerTilesCollection, numberOfTilesToMove );

    const auto actualNumberOfGameTilesAftereMove = gameTilesCollection.GetNumberOfTiles();
    const auto actualNumberOfPlayerTilesAfterMove = playerTilesCollection.GetNumberOfTiles();

    BOOST_CHECK_EQUAL( expectedNumberOfGameTilesBeforeMove, actualNumberOfGameTilesBeforeMove );
    BOOST_CHECK_EQUAL( expectedNumberOfPlayerTilesBeforeMove, actualNumberOfPlayerTilesBeforeMove );
    BOOST_CHECK_EQUAL( expectedNumberOfGameTilesAfterMove, actualNumberOfGameTilesAftereMove );
    BOOST_CHECK_EQUAL( expectedNumberOfPlayerTilesAfterMove, actualNumberOfPlayerTilesAfterMove );
}

BOOST_AUTO_TEST_CASE( CollectionHasCorrectTiles )
{
    const auto numberOfSets = 4;
    const auto tilesCollection = TilesCollection( numberOfSets );

    for ( const auto shape : shapes )
    {
        for ( const auto color : colors )
        {
            const auto expectedFinds = numberOfSets;
            auto actualFinds = 0;

            const auto tile = Tile( shape, color );

            for ( auto i = 0u; i < tilesCollection.GetNumberOfTiles(); i++ )
            {
                const auto & tileInCollection = tilesCollection.GetTileConst( i );
                if ( tileInCollection == tile )
                {
                    actualFinds++;
                }
            }

            BOOST_CHECK_EQUAL( expectedFinds, actualFinds );
        }
    }
}