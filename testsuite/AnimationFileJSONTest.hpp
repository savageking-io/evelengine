#include <cppunit/extensions/HelperMacros.h>

class AnimationFileJSONTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( AnimationFileJSONTest );
    CPPUNIT_TEST( testUnmarshal);
    CPPUNIT_TEST_SUITE_END();

    public:
    void tearUp();
    void tearDown();
    void testUnmarshal();
};
