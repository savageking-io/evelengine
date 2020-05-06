#ifndef __STRINGS_UTIL_TEST_HPP__
#define __STRINGS_UTIL_TEST_HPP__

#include <cppunit/extensions/HelperMacros.h>

class FileSystemTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( FileSystemTest );
    CPPUNIT_TEST( testPath );
    CPPUNIT_TEST( testAddTexturesPath );
    CPPUNIT_TEST( testAddAnimationFilesPath );
    CPPUNIT_TEST( testExists );
    CPPUNIT_TEST_SUITE_END();

    public:
    void tearUp();
    void tearDown();
    void testPath();
    void testAddTexturesPath();
    void testAddAnimationFilesPath();
    void testExists();
};

#endif
