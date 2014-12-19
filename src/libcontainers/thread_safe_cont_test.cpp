#define BOOST_TEST_MODULE stringtest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (stringtest) // name of the test suite is stringtest

BOOST_AUTO_TEST_CASE (test1)
{
  BOOST_CHECK(1 == 1);
}

BOOST_AUTO_TEST_SUITE_END( )
