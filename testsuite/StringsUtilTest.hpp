#ifndef __STRINGS_UTIL_TEST_HPP__
#define __STRINGS_UTIL_TEST_HPP__

#include <cppunit/extensions/HelperMacros.h>

class StringsUtilTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( StringsUtilTest );
    CPPUNIT_TEST( testSplit );
    CPPUNIT_TEST( testTrim );
    CPPUNIT_TEST_SUITE_END();

    public:
    void tearUp();
    void tearDown();
    void testSplit();
    void testTrim();
};

#endif