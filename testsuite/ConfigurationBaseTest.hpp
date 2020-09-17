#ifndef __STRINGS_UTIL_TEST_HPP__
#define __STRINGS_UTIL_TEST_HPP__

#include <cppunit/extensions/HelperMacros.h>

class ConfigurationBaseTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( ConfigurationBaseTest );
    CPPUNIT_TEST( testDefineInt );
    CPPUNIT_TEST( testDefineFloat );
    CPPUNIT_TEST( testDefineString );
    CPPUNIT_TEST_SUITE_END();

    public:
    void tearUp();
    void tearDown();
    void testDefineInt();
    void testDefineFloat();
    void testDefineString();
};

#endif
