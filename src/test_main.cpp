#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE( Test1 )
{
	BOOST_CHECK((2+2) == 4);
	BOOST_CHECK((2+2) == 5);
}
