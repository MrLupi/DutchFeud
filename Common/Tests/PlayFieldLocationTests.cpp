#define BOOST_TEST_MODULE PlayFieldLocationTests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "Common/Data/PlayFieldLocation.h"

using namespace DutchFeud::Common::Data;

BOOST_AUTO_TEST_CASE( PlayFieldLocationEqualityTest )
{
    const PlayFieldLocation location1 = { 10, 20 };
    const PlayFieldLocation location2a = { 20, 20 };
    const PlayFieldLocation location2b = { 20, 20 };
    const PlayFieldLocation location3 = { 20, 10 };

    BOOST_CHECK( location1 != location3 );
    BOOST_CHECK( location2a != location3 );
    BOOST_CHECK( location3 != location1 );

    BOOST_CHECK( location2a == location2b );
}