#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <string>

namespace SecureStoreTest
{
    CppUnitTest::TestCase* testOpenDb_OneElementAes256Cbc_case01()
    {
        CppUnitTest::TestCase* t = nullptr;
        t = new CppUnitTest::TestCase("open db file ciphered by aes 256 cbc");
        t->printTitle();

        std::string fileName = "tests/fixtures/one_element_aes_256_cbc.xdb";
        std::string key = "Qwerty123!";

        SecureStore::Storage::DB db;
        db.open(&fileName, &key);

        auto recs = db.getRecords();
        CppUnitTest::assertNotNull(t, recs);

        t->finish();

        return t;
    }
}
