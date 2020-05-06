#include <cppunit/extensions/TestFactoryRegistry.h>

#include "StringsUtilTest.hpp"

#include "StringsUtil.hpp"

void StringsUtilTest::tearUp()
{

}

void StringsUtilTest::tearDown()
{

}

void StringsUtilTest::testSplit()
{
    auto t0 = EvelEngine::StringsUtil::Split("string1,string2 ,string3,", ",", EvelEngine::StringsUtil::SPLIT_IGNORE_EMPTY);
    auto s0 = t0.size();
    CPPUNIT_ASSERT(s0 == 3);
    CPPUNIT_ASSERT(t0[0] == "string1");
    CPPUNIT_ASSERT(t0[1] == "string2 ");
    CPPUNIT_ASSERT(t0[2] == "string3");
    auto t1 = EvelEngine::StringsUtil::Split("str1, str2,str3 , str4 ", ",", EvelEngine::StringsUtil::SPLIT_TRIM);
    auto s1 = t1.size();
    CPPUNIT_ASSERT(s1 == 4);
    CPPUNIT_ASSERT(t1[0] == "str1");
    CPPUNIT_ASSERT(t1[1] == "str2");
    CPPUNIT_ASSERT(t1[2] == "str3");
    CPPUNIT_ASSERT(t1[3] == "str4");
}

void StringsUtilTest::testTrim()
{
    std::string t1(" leftspace");
    std::string t2("rightspace ");
    std::string t3(" bothspace ");
    EvelEngine::StringsUtil::Trim(t1);
    CPPUNIT_ASSERT(t1 == "leftspace");
    EvelEngine::StringsUtil::Trim(t2);
    CPPUNIT_ASSERT(t2 == "rightspace");
    EvelEngine::StringsUtil::Trim(t3);
    CPPUNIT_ASSERT(t3 == "bothspace");
}

CPPUNIT_TEST_SUITE_REGISTRATION( StringsUtilTest );
