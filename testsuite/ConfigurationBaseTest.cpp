#include <cppunit/extensions/TestFactoryRegistry.h>

#include "ConfigurationBaseTest.hpp"
#include "ConfigurationBase.hpp"
#include "Log.hpp"

void ConfigurationBaseTest::tearUp()
{

}

void ConfigurationBaseTest::tearDown()
{

}

void ConfigurationBaseTest::testDefineInt()
{
    EvelEngine::ConfigurationBase b("");
    b.defineOption("testInt0", 0);
    b.defineOption("testInt1", 1);
    b.defineOption("testInt2", 2);

    int i0 = b.get("testInt0")->value;
    CPPUNIT_ASSERT(i0 == 0);
}

void ConfigurationBaseTest::testDefineFloat()
{
    EvelEngine::ConfigurationBase b("");
    b.defineOption("testFloat0", 0.0f);
    b.defineOption("testFloat1", 0.1f);
    b.defineOption("testFloat2", 0.2f);
}

void ConfigurationBaseTest::testDefineString()
{
    EvelEngine::ConfigurationBase b("");
    b.defineOption("testString0", "0");
    b.defineOption("testString1", "1");
    b.defineOption("testString2", "2");
}

CPPUNIT_TEST_SUITE_REGISTRATION( ConfigurationBaseTest );
