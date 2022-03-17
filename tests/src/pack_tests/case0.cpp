#include <tests.h>
#include <cpp-unit-test.h>

namespace SecureStoreTest
{
    CppUnitTest::TestCase* testPack_case0()
    {
        CppUnitTest::TestCase* t = nullptr;
        t = new CppUnitTest::TestCase("test case0");
        t->printTitle();

        // do tests with asserts

        t->finish();

        return t;
    }
}
