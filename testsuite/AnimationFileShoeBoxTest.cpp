#include <cppunit/extensions/TestFactoryRegistry.h>

#include "AnimationFileShoeBoxTest.hpp"

#include "AnimationFileShoeBox.hpp"

void AnimationFileShoeBoxTest::tearUp()
{

}

void AnimationFileShoeBoxTest::tearDown()
{

}

void AnimationFileShoeBoxTest::testUnmarshal()
{
    EvelEngine::AnimationFileShoeBox f("assets/kenney_tooncharacters1/Female adventurer/Tilesheet/character_femaleAdventurer_sheet.xml");
    f.unmarshal();
}

CPPUNIT_TEST_SUITE_REGISTRATION( AnimationFileShoeBoxTest );