#ifndef H_SECURE_STORE_TESTS
#define H_SECURE_STORE_TESTS

#include <cpp-unit-test.h>

namespace SecureStoreTest
{
    // pack & unpack secrets
    CppUnitTest::TestCase* testPackAndUnpack_FullQualifiedData_Case0();
    CppUnitTest::TestCase* testPackAndUnpack_MinimumData();

    // cipher tests
    CppUnitTest::TestCase* testCipherData_case01();
    CppUnitTest::TestCase* testEncryptDecrypt_Data_case02();

    // save tests
    CppUnitTest::TestCase* testSaveDb_Data_case01();
}

#endif
