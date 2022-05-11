#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <list>
#include <string>

namespace SecureStoreTest
{
    BEGIN_TEST_CASE(testPackAndUnpack_MinimumData, "pack & unpack with minimum data")
        SecureStore::Storage::Record *record;
        record = new SecureStore::Storage::Record;

        record->setId(1);
        std::string name = "PackAndUnpack with minimum data";
        record->setName(&name);

        record->setCreateTime(187766224);

        SecureStore::DataPack *dataPack = SecureStore::Storage::pack(record);

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
    END_TEST_CASE()
}
