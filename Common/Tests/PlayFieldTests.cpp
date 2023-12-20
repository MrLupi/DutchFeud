#define BOOST_TEST_MODULE PlayFieldTests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "Common/Data/PlayField.h"

using namespace DutchFeud::Common::Data;

BOOST_AUTO_TEST_CASE( PlayFieldDefaultHasExpectedValue )
{
    const unsigned int expectedMultiplierTotal = 269;
    const auto playfield = PlayField( PlayField::Layout::Default );

    unsigned int actualMultiplierTotal = 0;
    for ( auto x = 0u; x < PlayField::PlayFieldSize; x++ )
    {
        for ( auto y = 0u; y < PlayField::PlayFieldSize; y++ )
        {
            const auto location = PlayFieldLocation( x, y );
            actualMultiplierTotal += playfield.GetMultiplier( location );
        }
    }

    BOOST_CHECK( expectedMultiplierTotal == actualMultiplierTotal );
}

BOOST_AUTO_TEST_CASE( PlayFieldDefaultHasExpectedMultiplier )
{
    const unsigned int expectedMultiplier1 = 1;
    const unsigned int expectedMultiplier2 = 2;
    const unsigned int expectedMultiplier3 = 3;

    const auto playfield = PlayField( PlayField::Layout::Default );

    const auto location1 = PlayFieldLocation( 7, 7 );
    const auto actualMultiplier1 = playfield.GetMultiplier( location1 );

    const auto location2 = PlayFieldLocation( 2, 2 );
    const auto actualMultiplier2 = playfield.GetMultiplier( location2 );

    const auto location3 = PlayFieldLocation( 3, 3 );
    const auto actualMultiplier3 = playfield.GetMultiplier( location3 );

    BOOST_CHECK( expectedMultiplier1 == actualMultiplier1 );
    BOOST_CHECK( expectedMultiplier2 == actualMultiplier2 );
    BOOST_CHECK( expectedMultiplier3 == actualMultiplier3 );
}

BOOST_AUTO_TEST_CASE( PlayFieldEmptyHasExpectedValue )
{
    const unsigned int expectedMultiplierTotal = 225;
    const auto playfield = PlayField( PlayField::Layout::Empty );

    unsigned int actualMultiplierTotal = 0;
    for ( auto x = 0u; x < PlayField::PlayFieldSize; x++ )
    {
        for ( auto y = 0u; y < PlayField::PlayFieldSize; y++ )
        {
            const auto location = PlayFieldLocation( x, y );
            actualMultiplierTotal += playfield.GetMultiplier( location );
        }
    }

    BOOST_CHECK( expectedMultiplierTotal == actualMultiplierTotal );
}

BOOST_AUTO_TEST_CASE( PlayFieldRandomHasExpectedValue )
{
    const unsigned int expectedMultiplierTotal = 269;
    const auto playfield = PlayField( PlayField::Layout::Random );

    unsigned int actualMultiplierTotal = 0;
    for ( auto x = 0u; x < PlayField::PlayFieldSize; x++ )
    {
        for ( auto y = 0u; y < PlayField::PlayFieldSize; y++ )
        {
            const auto location = PlayFieldLocation( x, y );
            actualMultiplierTotal += playfield.GetMultiplier( location );
        }
    }

    BOOST_CHECK_EQUAL( expectedMultiplierTotal, actualMultiplierTotal );
}