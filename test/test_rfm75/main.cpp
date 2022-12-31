#include "unity.h"
#include "test_rfm75_registers.h"

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_RFM75RegisterInterface_isBitSet_1B_register);
    RUN_TEST(test_RFM75RegisterInterface_isBitSet_2B_register);
    RUN_TEST(test_RFM75RegisterInterface_isBitSet_3B_register);
    RUN_TEST(test_RFM75RegisterInterface_setBit_1B_register);
    RUN_TEST(test_RFM75RegisterInterface_setBit_2B_register);
    RUN_TEST(test_RFM75RegisterInterface_unsetBit_1B_register);
    RUN_TEST(test_RFM75RegisterInterface_unsetBit_2B_register);

    return UNITY_END();
}

/**
 * For native dev-platform or for some embedded frameworks
 */
int main(void)
{
    return runUnityTests();
}
