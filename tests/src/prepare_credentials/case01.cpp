#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <string>
#include <memory>
#include <openssl/rand.h>

namespace SecureStoreTest
{
    CppUnitTest::TestCase* testPrepareCredentials_Data_case01()
    {
        CppUnitTest::TestCase* t = nullptr;
        t = new CppUnitTest::TestCase("testPrepareCredentials_Data_case01");
        t->printTitle();

        const char* user = "alexander";
        const char* password = "123Qwerty!";
        char* salt = (char*) malloc(32);
        RAND_bytes((unsigned char*) salt, 32);

        SecureStore::Crypto::prepare_credentials(user, password, salt);

        t->finish();
        return t;
    }
}
