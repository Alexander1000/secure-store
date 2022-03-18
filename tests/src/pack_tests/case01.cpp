#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <list>
#include <string>

namespace SecureStoreTest
{
    CppUnitTest::TestCase* testPackAndUnpack_MinimumData()
    {
        CppUnitTest::TestCase* t = nullptr;
        t = new CppUnitTest::TestCase("pack & unpack with minimum data");
        t->printTitle();

        SecureStore::Storage::Record *record;
        record = new SecureStore::Storage::Record;

        record->setId(1);
        std::string name = "PackAndUnpack with minimum data";
        record->setName(&name);

        record->setCreateTime(187766224);

        SecureStore::Storage::DataPack *dataPack = SecureStore::Storage::pack(record);

        CppUnitTest::assertNotNull(t, dataPack);
        CppUnitTest::assertEquals(t, 44, dataPack->getLength());

        SecureStore::Storage::Record *unpackedRecord = SecureStore::Storage::unpack(dataPack);

        CppUnitTest::assertEquals(t, record->getId(), unpackedRecord->getId());
        CppUnitTest::assertEquals(t, *record->getName(), *unpackedRecord->getName());
        CppUnitTest::assertNull(t, unpackedRecord->getUser());
        CppUnitTest::assertNull(t, unpackedRecord->getPassword());
        CppUnitTest::assertNull(t, unpackedRecord->getComment());
        CppUnitTest::assertNull(t, unpackedRecord->getKeywords());
        CppUnitTest::assertEquals(t, (int) record->getCreateTime(), (int) unpackedRecord->getCreateTime());

        t->finish();

        return t;
    }
}
