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
        const char* salt = "qwertyuiopasdfghjklzxcvbnm12345";

        auto data = SecureStore::Crypto::prepare_credentials(user, password, salt);
        CppUnitTest::assertEquals(t, 64, data->getLength());

        t->finish();
        return t;
    }
}
