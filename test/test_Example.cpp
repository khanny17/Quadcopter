//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "BaseClassModule"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

//#include "some_project/some_base_class.h"
// ------------- Tests Follow --------------
BOOST_AUTO_TEST_CASE( constructors )
{
    //SomeBaseClass obj;
    //SomeBaseClass obj2;

    //Check default constructor
    //Use BOOST_CHECK for small equal checks  true or false
    BOOST_CHECK(true == true);
    //......
}

//Name your test cases for what they test
BOOST_AUTO_TEST_CASE( assignment )
{
    //Use BOOST_CHECK_EQUAL if you want the values to be 
    //printed out if they mismatch
    BOOST_CHECK_EQUAL("SomeValue", "SomeValue");
}

