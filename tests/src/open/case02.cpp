#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <string>

namespace SecureStoreTest
{
    CppUnitTest::TestCase* testOpenDb_ThreeElementsAes256Cbc_case02()
    {
        CppUnitTest::TestCase* t = nullptr;
        t = new CppUnitTest::TestCase("open db file ciphered by aes 256 cbc with three records");
        t->printTitle();

        std::string fileName = "tests/fixtures/3_elements_aes_256_cbc_ver_0_0.xdb";
        std::string key = "vmbzyirhkfs342iyvsmm5@%";

        SecureStore::Storage::DB db;
        int result = db.open(&fileName, &key);
        CppUnitTest::assertEquals(t, 0, result);

        auto recs = db.getRecords();
        CppUnitTest::assertNotNull(t, recs);
        CppUnitTest::assertEquals(t, 3, recs->size());

        auto itRecs = recs->begin();

        // first record
        auto dbRecord = *itRecs;
        CppUnitTest::assertEquals(t, 0, dbRecord->getStatus());

        auto record = dbRecord->getRecord();
        CppUnitTest::assertNotNull(t, record);

        CppUnitTest::assertEquals(t, 1, record->getId());
        CppUnitTest::assertEquals(t, "testSaveDb_MultiRecordsData_case02_record1", record->getName());
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

        // second record
        itRecs++;
        dbRecord = *itRecs;
        CppUnitTest::assertEquals(t, 0, dbRecord->getStatus());

        record = dbRecord->getRecord();
        CppUnitTest::assertNotNull(t, record);

        CppUnitTest::assertEquals(t, 2, record->getId());
        CppUnitTest::assertEquals(t, "testSaveDb_MultiRecordsData_case02_record2", record->getName());
        CppUnitTest::assertEquals(t, "nagibator_3000", record->getUser());
        CppUnitTest::assertEquals(t, "zxcvb123$%^", record->getPassword());
        CppUnitTest::assertEquals(t, "This is secret for me", record->getComment());
        CppUnitTest::assertNull(t, record->getKeywords());
        CppUnitTest::assertEquals(t, 747828722, record->getCreateTime());

        t->finish();

        return t;
    }
}
