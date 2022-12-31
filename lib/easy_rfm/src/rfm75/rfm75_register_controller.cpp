#include "spi/spi_config.h"

#include "rfm75_register_controller.h"

//-------------------------------------------------------------------------------------------------------------------
void RFM75RegisterController::setRegisterBit(RFM75Registers::RFM75Register &reg, uint8_t bit_num)
{
    readRegister(reg);
    reg.setBit(bit_num);
    writeRegister(reg);
}
//-------------------------------------------------------------------------------------------------------------------
void RFM75RegisterController::unSetRegisterBit(RFM75Registers::RFM75Register &reg, uint8_t bit_num)
{
    readRegister(reg);
    reg.unsetBit(bit_num);
    writeRegister(reg);
}
//-------------------------------------------------------------------------------------------------------------------
bool RFM75RegisterController::isRegisterBitSet(RFM75Registers::RFM75Register &reg, uint8_t bit_num)
{
    readRegister(reg);
    return reg.isBitSet(bit_num);
}
//-------------------------------------------------------------------------------------------------------------------
void RFM75RegisterController::setBankNumber(RFM75BankNumber number)
{
    if (getBankNumber() != number)
    {
        switchBankNumber();
    }
}
//-------------------------------------------------------------------------------------------------------------------
RFM75BankNumber RFM75RegisterController::getBankNumber()
{
    const uint8_t BANK_BIT_NUM = 7;
    RFM75Registers::RFM75RegisterInterface<RFM75Registers::STATUS> reg_interface;
    RFM75Registers::RFM75Register reg = reg_interface.getStruct();
    pSpi->exchange(&reg.addr, 1, reg.data, reg.size, true, true);
    return reg.isBitSet(BANK_BIT_NUM) ? RFM75BankNumber::BANK_1 : RFM75BankNumber::BANK_0;
}
//-------------------------------------------------------------------------------------------------------------------
RFM75BankNumber RFM75RegisterController::switchBankNumber()
{
    const uint8_t switch_command[] = {0x50, 0x53};
    pSpi->write(switch_command, 2, true, true);
    return getBankNumber();
}
//-------------------------------------------------------------------------------------------------------------------
void RFM75RegisterController::readRegister(RFM75Registers::RFM75Register &reg)
{
    if(getBankNumber() != reg.bank)
    {
        switchBankNumber();
    }
    pSpi->exchange(&reg.addr, 1, reg.data, reg.size, true, true);
}
//-------------------------------------------------------------------------------------------------------------------
void RFM75RegisterController::writeRegister(RFM75Registers::RFM75Register &reg)
{
    if(getBankNumber() != reg.bank)
    {
        switchBankNumber();
    }
    const uint8_t WRITE_CMD = reg.addr | 0x20;
    pSpi->write(&WRITE_CMD, 1, true, false);
    pSpi->write(reg.data, reg.size, false, true);
}
