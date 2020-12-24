#include <cppunit/extensions/TestFactoryRegistry.h>

#include "AnimationFileAsepriteTest.hpp"

#include "AnimationFileAseprite.hpp"

void AnimationFileAsepriteTest::tearUp()
{

}

void AnimationFileAsepriteTest::tearDown()
{

}

void AnimationFileAsepriteTest::testUnmarshal()
{
    EvelEngine::AnimationFileAseprite json("assets/sprites/adventurer_tilesheet.json");
    json.unmarshal();
}

CPPUNIT_TEST_SUITE_REGISTRATION( AnimationFileAsepriteTest );
