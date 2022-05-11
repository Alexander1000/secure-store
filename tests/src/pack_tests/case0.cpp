#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <list>
#include <string>

namespace SecureStoreTest
{
    BEGIN_TEST_CASE(testPackAndUnpack_FullQualifiedData_Case0, "test case0")
        SecureStore::Storage::Record *record;
        record = new SecureStore::Storage::Record;

        record->setId(1);
        std::string name = "TestCase01";
        record->setName(&name);

        std::string user = "some-login";
        record->setUser(&user);

        std::string password = "12345Qwerty!@#";
        record->setPassword(&password);

        std::string comment = "It is example record in secure store";
        record->setComment(&comment);

        std::list<std::string> keywords;
        keywords.emplace_back("system");
        keywords.emplace_back("critical");
        record->setKeywords(&keywords);

        record->setCreateTime(187766224);

        SecureStore::DataPack *dataPack = SecureStore::Storage::pack(record);

        CppUnitTest::assertNotNull(t, dataPack);
        CppUnitTest::assertEquals(t, 116, dataPack->getLength());

        SecureStore::Storage::Record *unpackedRecord = SecureStore::Storage::unpack(dataPack);

        CppUnitTest::assertEquals(t, record->getId(), unpackedRecord->getId());
        CppUnitTest::assertEquals(t, *record->getName(), *unpackedRecord->getName());
        CppUnitTest::assertEquals(t, *record->getUser(), *unpackedRecord->getUser());
        CppUnitTest::assertEquals(t, *record->getPassword(), *unpackedRecord->getPassword());
        CppUnitTest::assertEquals(t, *record->getComment(), *unpackedRecord->getComment());

        CppUnitTest::assertEquals(t, (int) record->getKeywords()->size(), (int) unpackedRecord->getKeywords()->size());

        for (auto & keyword : *record->getKeywords()) {
            bool found = false;

            for (auto & unpackedKeyword : *unpackedRecord->getKeywords()) {
                if (keyword == unpackedKeyword) {
                    found = true;
                    break;
                }
            }

            CppUnitTest::assertTrue(t, found);
        }

        CppUnitTest::assertEquals(t, (int) record->getCreateTime(), (int) unpackedRecord->getCreateTime());
    END_TEST_CASE()
}
