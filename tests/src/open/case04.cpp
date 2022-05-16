#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <string>

namespace SecureStoreTest
{
    BEGIN_TEST_CASE(testOpenDb_OpenAfterRepeatableTriesWithWrongPassword_case4, "open db file after repetable retries with wrong password")
        std::string fileName = "tests/fixtures/one_element_aes_256_cbc.xdb";

        SecureStore::Storage::DB db;

        std::string user1 = "Nagibator_30001";
        std::string password1 = "Qwerty123!";

        int result = db.open(fileName.c_str(), user1.c_str(), password1.c_str());
        CppUnitTest::assertEquals(t, 6, result);

        std::string user2 = "Nagibator_3000";
        std::string password2 = "Qwerty123";

        result = db.open(fileName.c_str(), user2.c_str(), password2.c_str());
        CppUnitTest::assertEquals(t, 6, result);

        std::string user3 = "a";
        std::string password3 = "b";

        result = db.open(fileName.c_str(), user3.c_str(), password3.c_str());
        CppUnitTest::assertEquals(t, 6, result);

        std::string user4 = "qwertyuiopasdfghjklzxcvbnm";
        std::string password4 = "qwertyuiopasdfghjklzxcvbnm";

        result = db.open(fileName.c_str(), user4.c_str(), password4.c_str());
        CppUnitTest::assertEquals(t, 6, result);

        std::string user5 = "Nagibator_3000";
        std::string password5 = "Qwerty123!";

        result = db.open(fileName.c_str(), user5.c_str(), password5.c_str());
        CppUnitTest::assertEquals(t, 0, result);

        auto recs = db.getRecords();
        CppUnitTest::assertNotNull(t, recs);
        CppUnitTest::assertEquals(t, 1, recs->size());

        auto dbRecord = *recs->begin();
        CppUnitTest::assertEquals(t, 0, dbRecord->getStatus());

        auto record = dbRecord->getRecord();
        CppUnitTest::assertNotNull(t, record);

        CppUnitTest::assertEquals(t, "testSaveDb_Data_case01", record->getName());
        CppUnitTest::assertEquals(t, "some-login", record->getUser());
        CppUnitTest::assertEquals(t, "12345Qwerty!@#", record->getPassword());
        CppUnitTest::assertEquals(t, "It is example record in secure store", record->getComment());
        auto keywords = record->getKeywords();
        CppUnitTest::assertNotNull(t, keywords);
        CppUnitTest::assertEquals(t, 2, keywords->size());
        auto keyword = *keywords->begin();
        CppUnitTest::assertEquals(t, "system", keyword);
        keyword = *(++keywords->begin());
        CppUnitTest::assertEquals(t, "critical", keyword);
        CppUnitTest::assertEquals(t, 187766224, record->getCreateTime());
    END_TEST_CASE()
}
