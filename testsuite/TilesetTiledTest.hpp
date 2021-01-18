#include <cppunit/extensions/HelperMacros.h>

class TilesetTiledTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( TilesetTiledTest );
    CPPUNIT_TEST( testLoad );
    CPPUNIT_TEST_SUITE_END();

    public:
    void tearUp();
    void tearDown();
    void testLoad();
};
