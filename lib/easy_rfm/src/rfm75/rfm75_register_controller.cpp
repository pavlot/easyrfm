#include <stdint.h>
#include "spi/spi_config.h"

#include "rfm75_register_controller.h"

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
    // RFM75Registers::RFM75RegisterInterface<RFM75Registers::STATUS> reg_interface;
    // RFM75Registers::RFM75Register reg = reg_interface.getStruct();
    RFM75Registers::STATUS reg;
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
void RFM75RegisterController::readRegister(const RFM75BankNumber bank, const uint8_t addr, const uint8_t size, uint8_t* data)
{
    if(getBankNumber() != bank)
    {
        switchBankNumber();
    }
    pSpi->exchange(&addr, 1, data, size, true, true);
}
//-------------------------------------------------------------------------------------------------------------------
//void RFM75RegisterController::writeRegister(RFM75Registers::RFM75Register &reg)
void RFM75RegisterController::writeRegister(const RFM75BankNumber bank, const uint8_t addr, const uint8_t size, const uint8_t *data)
{
    if(getBankNumber() != bank)
    {
        switchBankNumber();
    }
    const uint8_t WRITE_CMD = addr | 0x20;
    pSpi->write(&WRITE_CMD, 1, true, false);
    pSpi->write(data, size, false, true);
}
