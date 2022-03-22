#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <string>

namespace SecureStoreTest
{
    CppUnitTest::TestCase* testSaveDb_Data_case01()
    {
        CppUnitTest::TestCase* t = nullptr;
        t = new CppUnitTest::TestCase("save db in file");
        t->printTitle();

        t->finish();

        return t;
    }
}
