#ifndef __ANIMATION_FILE_SHOE_BOX_TEST_HPP__
#define __ANIMATION_FILE_SHOE_BOX_TEST_HPP__

#include <cppunit/extensions/HelperMacros.h>

class AnimationFileShoeBoxTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( AnimationFileShoeBoxTest );
    CPPUNIT_TEST( testUnmarshal );
    CPPUNIT_TEST_SUITE_END();

    public:
    void tearUp();
    void tearDown();
    void testUnmarshal();
};

#endif