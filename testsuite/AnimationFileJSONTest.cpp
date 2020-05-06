#include <cppunit/extensions/TestFactoryRegistry.h>

#include "AnimationFileJSONTest.hpp"

#include "AnimationFileJSON.hpp"

void AnimationFileJSONTest::tearUp()
{

}

void AnimationFileJSONTest::tearDown()
{

}

void AnimationFileJSONTest::testUnmarshal()
{
    EvelEngine::AnimationFileJSON json("assets/sprites/adventurer_tilesheet.json");
    json.unmarshal();
}

CPPUNIT_TEST_SUITE_REGISTRATION( AnimationFileJSONTest );
