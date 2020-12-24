#include <cppunit/extensions/HelperMacros.h>

class AnimationFileAsepriteTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( AnimationFileAsepriteTest );
    CPPUNIT_TEST( testUnmarshal);
    CPPUNIT_TEST_SUITE_END();

    public:
    void tearUp();
    void tearDown();
    void testUnmarshal();
};
