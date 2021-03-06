#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <string>
#include <memory>

namespace SecureStoreTest
{
    BEGIN_TEST_CASE(testHash_Data_case01, "testHash_Data_case01")
        std::string message = "test";
        auto input = new SecureStore::DataPack((int) message.size(), (void*) message.c_str());

        uint8_t cipheredData[64] = {
            0x9e, 0xce, 0x08, 0x6e, 0x9b, 0xac, 0x49, 0x1f,
            0xac, 0x5c, 0x1d, 0x10, 0x46, 0xca, 0x11, 0xd7,
            0x37, 0xb9, 0x2a, 0x2b, 0x2e, 0xbd, 0x93, 0xf0,
            0x05, 0xd7, 0xb7, 0x10, 0x11, 0x0c, 0x0a, 0x67,
            0x82, 0x88, 0x16, 0x6e, 0x7f, 0xbe, 0x79, 0x68,
            0x83, 0xa4, 0xf2, 0xe9, 0xb3, 0xca, 0x9f, 0x48,
            0x4f, 0x52, 0x1d, 0x0c, 0xe4, 0x64, 0x34, 0x5c,
            0xc1, 0xae, 0xc9, 0x67, 0x79, 0x14, 0x9c, 0x14,
        };

        auto data = SecureStore::Crypto::hash_sha3_512(input);

        for (int i = 0; i < 64; i++) {
            CppUnitTest::assertEquals(t, cipheredData[i], data[i]);
        }
    END_TEST_CASE()
}
