#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <string>
#include <memory>
#include <openssl/rand.h>

namespace SecureStoreTest
{
    BEGIN_TEST_CASE(testPrepareCredentials_BruteForce_case02, "Brute force for prepare_credentials")
        const char* patternUser = "Nagibator_%d";
        const char* patternPassword = "SuperPassword_%d";

        MEMORY_ALLOC(salt, SecureStore::Storage::DB_HEADER_SALT_BYTE_SIZE);
        RAND_bytes((unsigned char*) salt, sizeof(unsigned char) * SecureStore::Storage::DB_HEADER_SALT_BYTE_SIZE);

        for (int i = 0; i < 1000; i++) {
            INIT_CHAR_STRING(sUser, 32);
            sprintf(sUser, patternUser, i);

            INIT_CHAR_STRING(sPassword, 32);
            sprintf(sPassword, patternPassword, i);

            auto data = SecureStore::Crypto::prepare_credentials(sUser, sPassword, (const char*) salt);
            CppUnitTest::assertEquals(t, 64, data->getLength());

            MEMORY_FREE(sUser);
            MEMORY_FREE(sPassword);
        }

        MEMORY_FREE(salt);
    END_TEST_CASE()
}
