#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <string>

namespace SecureStoreTest
{
    BEGIN_TEST_CASE(testOpenDb_BruteForce1000Tries_case5, "Brute force 1000 tries attempts open secured file")
        std::string fileName = "tests/fixtures/one_element_aes_256_cbc.xdb";

        SecureStore::Storage::DB db;

        for (int i = 0; i < 1000; i++) {
            INIT_CHAR_STRING(sUser, 32);
            sprintf(sUser, "Nagibator_%d", i);

            INIT_CHAR_STRING(sPassword, 32);
            sprintf(sPassword, "SuperPassword_%d", i);

            int result = db.open(fileName.c_str(), sUser, sPassword);
            CppUnitTest::assertEquals(t, 6, result);

            free(sUser);
            free(sPassword);
        }
    END_TEST_CASE()
}
