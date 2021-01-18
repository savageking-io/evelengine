#include <cppunit/extensions/TestFactoryRegistry.h>

#include "TilesetTiledTest.hpp"

#include "TilesetTiled.hpp"

void TilesetTiledTest::tearUp()
{

}

void TilesetTiledTest::tearDown()
{

}

void TilesetTiledTest::testLoad()
{
    auto tileset = EvelEngine::NewTilesetTiled("assets/tilesets/towerdefense.json");
}

CPPUNIT_TEST_SUITE_REGISTRATION( TilesetTiledTest );
