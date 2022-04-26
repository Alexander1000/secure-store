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

        uint8_t expectedData[64] = {
            0xef, 0xa1, 0x08, 0x6e, 0x9b, 0xac, 0x49, 0x1f,
            0xac, 0x5c, 0x1d, 0x10, 0x46, 0xca, 0x11, 0xd7,
            0x37, 0xb9, 0x2a, 0x2b, 0x2e, 0xbd, 0x93, 0xf0,
            0x05, 0xd7, 0xb7, 0x10, 0x11, 0x0c, 0x0a, 0x67,
            0x82, 0x88, 0x16, 0x6e, 0x7f, 0xbe, 0x79, 0x68,
            0x83, 0xa4, 0xf2, 0xe9, 0xb3, 0xca, 0x9f, 0x48,
            0x4f, 0x52, 0x1d, 0x0c, 0xe4, 0x64, 0x34, 0x5c,
            0xc1, 0xae, 0xc9, 0x67, 0x79, 0x14, 0x9c, 0x14,
        };

        for (int i = 0; i < data->getLength(); i++) {
            auto curChar = *((uint8_t*) data->getData() + i);
            CppUnitTest::assertEquals(t, expectedData[i], curChar);
        }

        t->finish();
        return t;
    }
}
