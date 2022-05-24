#include <tests.h>
#include <cpp-unit-test.h>

int main() {
    CppUnitTest::TestSuite testSuite;

    testSuite.addTestCase(SecureStoreTest::testPackAndUnpack_FullQualifiedData_Case0());
    testSuite.addTestCase(SecureStoreTest::testPackAndUnpack_MinimumData());

    // cipher tests
    testSuite.addTestCase(SecureStoreTest::testEncryptDecrypt_Data_case02());

    // save tests
    testSuite.addTestCase(SecureStoreTest::testSaveDb_Data_case01());
    testSuite.addTestCase(SecureStoreTest::testSaveDb_MultiRecordsData_case02());
    testSuite.addTestCase(SecureStoreTest::testSaveDb_AppendData_case03());

    // open tests
    testSuite.addTestCase(SecureStoreTest::testOpenDb_OneElementAes256Cbc_case01());
    testSuite.addTestCase(SecureStoreTest::testOpenDb_ThreeElementsAes256Cbc_case02());
    testSuite.addTestCase(SecureStoreTest::testOpenDb_RepeatableOpenDb_case3());
    testSuite.addTestCase(SecureStoreTest::testOpenDb_OpenAfterRepeatableTriesWithWrongPassword_case4());
    testSuite.addTestCase(SecureStoreTest::testOpenDb_BruteForce1000Tries_case5());

    // hash tests
    testSuite.addTestCase(SecureStoreTest::testHash_Data_case01());

    // prepare credentials
    testSuite.addTestCase(SecureStoreTest::testPrepareCredentials_Data_case01());
    testSuite.addTestCase(SecureStoreTest::testPrepareCredentials_BruteForce_case02());

    testSuite.printTotal();

    return 0;
}
