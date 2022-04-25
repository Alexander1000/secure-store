#ifndef H_SECURE_STORE_TESTS
#define H_SECURE_STORE_TESTS

#include <cpp-unit-test.h>

#define BEGIN_TEST_CASE(method, description) \
    CppUnitTest::TestCase *method() \
    { \
        CppUnitTest::TestCase* t = nullptr; \
        t = new CppUnitTest::TestCase(description); \
        t->printTitle();

#define END_TEST_CASE() \
        t->finish(); \
        return t; \
    }

namespace SecureStoreTest
{
    // pack & unpack secrets
    CppUnitTest::TestCase* testPackAndUnpack_FullQualifiedData_Case0();
    CppUnitTest::TestCase* testPackAndUnpack_MinimumData();

    // cipher tests
    CppUnitTest::TestCase* testEncryptDecrypt_Data_case02();

    // save tests
    CppUnitTest::TestCase* testSaveDb_Data_case01();
    CppUnitTest::TestCase* testSaveDb_MultiRecordsData_case02();
    CppUnitTest::TestCase* testSaveDb_AppendData_case03();

    // open tests
    CppUnitTest::TestCase* testOpenDb_OneElementAes256Cbc_case01();
    CppUnitTest::TestCase* testOpenDb_ThreeElementsAes256Cbc_case02();
    CppUnitTest::TestCase* testOpenDb_RepeatableOpenDb_case3();

    // hash tests
    CppUnitTest::TestCase* testHash_Data_case01();

    // prepare credentials
    CppUnitTest::TestCase* testPrepareCredentials_Data_case01();
}

#endif
