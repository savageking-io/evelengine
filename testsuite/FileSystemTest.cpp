#include <cppunit/extensions/TestFactoryRegistry.h>

#include "FileSystemTest.hpp"
#include "FileSystem.hpp"
#include "Log.hpp"

void FileSystemTest::tearUp()
{

}

void FileSystemTest::tearDown()
{

}

void FileSystemTest::testPath()
{

}

void FileSystemTest::testAddTexturesPath()
{
    EvelEngine::FileSystem fs("/", nullptr);

    CPPUNIT_ASSERT(fs.root() == "/");

    bool rc0 = fs.addTexturesPath("tmp1");
    bool rc1 = fs.addTexturesPath("tmp");
    bool rc2 = fs.addTexturesPath("tmp1");

    CPPUNIT_ASSERT(!rc0);
    CPPUNIT_ASSERT(rc1);
    CPPUNIT_ASSERT(!rc2);
}

void FileSystemTest::testAddAnimationFilesPath()
{

}

void FileSystemTest::testExists()
{
    EvelEngine::FileSystem fs("/", nullptr);
    CPPUNIT_ASSERT(fs.exists("tmp"));
}

CPPUNIT_TEST_SUITE_REGISTRATION( FileSystemTest );
