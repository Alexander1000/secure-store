#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <string>

namespace SecureStoreTest
{
    BEGIN_TEST_CASE(testOpenDb_BruteForce1000Tries_case5, "Brute force 1000 tries attempts open secured file")
        const char* fileName = "tests/fixtures/one_element_aes_256_cbc.xdb";

        SecureStore::Storage::DB db;

        const char* patternUser = "Nagibator_%d";
        const char* patternPassword = "SuperPassword_%d";

        for (int i = 0; i < 1000; i++) {
            INIT_CHAR_STRING(sUser, 32);
            sprintf(sUser, patternUser, i);

            INIT_CHAR_STRING(sPassword, 32);
            sprintf(sPassword, patternPassword, i);

            int result = db.open(fileName, sUser, sPassword);
            CppUnitTest::assertTrue(t, result == 6 || result == 7);

            MEMORY_FREE(sUser);
            MEMORY_FREE(sPassword);
        }
    END_TEST_CASE()
}
