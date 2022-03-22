#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <list>
#include <string>

namespace SecureStoreTest
{
    CppUnitTest::TestCase* testEncyptDecrypt_Data_case02()
    {
        CppUnitTest::TestCase* t = nullptr;
        t = new CppUnitTest::TestCase("cipher data test-case 01");
        t->printTitle();

        t->finish();

        return t;
    }
}
