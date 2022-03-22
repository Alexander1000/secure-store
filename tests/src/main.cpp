#include <tests.h>
#include <cpp-unit-test.h>

int main() {
    CppUnitTest::TestSuite testSuite;

    testSuite.addTestCase(SecureStoreTest::testPackAndUnpack_FullQualifiedData_Case0());
    testSuite.addTestCase(SecureStoreTest::testPackAndUnpack_MinimumData());

    // cipher tests
    testSuite.addTestCase(SecureStoreTest::testCipherData_case01());
    testSuite.addTestCase(SecureStoreTest::testEncyptDecrypt_Data_case02());

    testSuite.printTotal();

    return 0;
}
