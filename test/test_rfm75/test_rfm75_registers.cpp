#include "unity.h"
#include <rfm75/rfm75_registers.h>

typedef RFM75Registers::RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x00, 1> REGISTER_1B;
typedef RFM75Registers::RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x00, 2> REGISTER_2B;
typedef RFM75Registers::RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x00, 3> REGISTER_3B;

//-------------------------------------------------------------------------------------------------------------------
void test_RFM75RegisterInterface_isBitSet_1B_register(void)
{
  REGISTER_1B reg;
  TEST_ASSERT_FALSE(reg.isBitSet(1));
  reg.data[0] = 0b00000001;
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(0), "Assertion for bit 0 failed");
  reg.data[0] = 0b10000001;
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(0), "Assertion for bit 0 failed");
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(7), "Assertion for bit 7 failed");
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(1), "Assertion for bit 1 unset failed");

  reg.data[0] = 0b10000000;
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(0), "Assertion for bit 0 unset failed");
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(7), "Assertion for bit 7 failed");
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(1), "Assertion for bit 1 unset failed");
}

//-------------------------------------------------------------------------------------------------------------------
void test_RFM75RegisterInterface_isBitSet_2B_register(void)
{
  REGISTER_2B reg;
  TEST_ASSERT_FALSE(reg.isBitSet(1));
  reg.data[0] = 0b00000001;
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(0), "Assertion for bit 0 failed");
  reg.data[0] = 0b10000001;
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(0), "Assertion for bit 0 failed");
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(7), "Assertion for bit 7 failed");
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(1), "Assertion for bit 1 unset failed");

  reg.data[0] = 0b10000000;
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(0), "Assertion for bit 0 unset failed");
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(7), "Assertion for bit 7 failed");
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(1), "Assertion for bit 1 unset failed");

  reg.data[0] = 0b10000000;
  reg.data[1] = 0b10000000;
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(0), "Assertion for bit 0 unset failed");
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(7), "Assertion for bit 7 failed");
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(15), "Assertion for bit 15 failed");

  reg.data[0] = 0b0;
  reg.data[1] = 0b10000000;
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(0), "Assertion for bit 0 unset failed");
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(7), "Assertion for bit 7 unset failed");
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(15), "Assertion for bit 15 failed");
}
//-------------------------------------------------------------------------------------------------------------------
void test_RFM75RegisterInterface_isBitSet_3B_register(void)
{
  REGISTER_3B reg;
  TEST_ASSERT_FALSE(reg.isBitSet(1));
  reg.data[0] = 0b00000001;
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(0), "Assertion for bit 0 failed");
  reg.data[0] = 0b10000001;
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(0), "Assertion for bit 0 failed");
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(7), "Assertion for bit 7 failed");
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(1), "Assertion for bit 1 unset failed");

  reg.data[0] = 0b10000000;
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(0), "Assertion for bit 0 unset failed");
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(7), "Assertion for bit 7 failed");
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(1), "Assertion for bit 1 unset failed");

  reg.data[0] = 0b10000000;
  reg.data[2] = 0b10000000;
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(0), "Assertion for bit 0 unset failed");
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(7), "Assertion for bit 7 failed");
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(23), "Assertion for bit 23 failed");

  reg.data[0] = 0b0;
  reg.data[2] = 0b10000000;
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(0), "Assertion for bit 0 unset failed");
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(7), "Assertion for bit 7 unset failed");
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(23), "Assertion for bit 15 failed");
}

//-------------------------------------------------------------------------------------------------------------------
void test_RFM75RegisterInterface_setBit_1B_register(void)
{
  REGISTER_1B reg;
  reg.setBit(0);
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(0), "Assertion for bit 0 set failed");
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(1), "Assertion for bit 1 unset failed");
}
//-------------------------------------------------------------------------------------------------------------------
void test_RFM75RegisterInterface_setBit_2B_register(void)
{
  REGISTER_2B reg;
  reg.setBit(0);
  reg.setBit(8);
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(0), "Assertion for bit 0 set failed");
  TEST_ASSERT_TRUE_MESSAGE(reg.isBitSet(8), "Assertion for bit 1 set failed");
}
//-------------------------------------------------------------------------------------------------------------------
void test_RFM75RegisterInterface_unsetBit_1B_register(void)
{
  REGISTER_1B reg;
  reg.data[0] = 0b11111111;
  reg.unsetBit(0);
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(0), "Assertion for bit 0 unset failed");
}
//-------------------------------------------------------------------------------------------------------------------
void test_RFM75RegisterInterface_unsetBit_2B_register(void)
{

  REGISTER_2B reg;
  reg.data[0] = 0b11111111;
  reg.data[1] = 0b11111111;
  reg.unsetBit(0);
  reg.unsetBit(8);
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(0), "Assertion for bit 0 unset failed");
  TEST_ASSERT_FALSE_MESSAGE(reg.isBitSet(8), "Assertion for bit 1 unset failed");
}
