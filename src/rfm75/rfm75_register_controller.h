#pragma once
#include <stdint.h>
#include "rfm75_registers.h"
#include "spi/spi_config.h"

//---------- Forward declarations --------------------
//---------- End of Forward declarations -------------

class RFM75RegisterController
{
public:
    explicit RFM75RegisterController(SPIInterface *iSpi) : pSpi(iSpi){};
    //-------------------------------------------------------------------------------------------------------------------
    template <typename RegisterType> void setRegisterBit(RegisterType &reg, uint8_t bit_num)
    {
        readRegister(reg.bank, reg.addr, reg.size, reg.data);
        reg.setBit(bit_num);
        writeRegister(reg.bank, reg.addr, reg.size, reg.data);
    }
    //-------------------------------------------------------------------------------------------------------------------
    template <typename RegisterType> void unSetRegisterBit(RegisterType &reg, uint8_t bit_num)
    {
        readRegister(reg.bank, reg.addr, reg.size, reg.data);
        reg.unsetBit(bit_num);
        writeRegister(reg.bank, reg.addr, reg.size, reg.data);
    }
    //-------------------------------------------------------------------------------------------------------------------
    template <typename RegisterType> bool isRegisterBitSet(RegisterType &reg, uint8_t bit_num)
    {
        readRegister(reg.bank, reg.addr, reg.size, reg.data);
        return reg.isBitSet(bit_num);
    }

    void setBankNumber(RFM75BankNumber number);
    RFM75BankNumber getBankNumber();
    RFM75BankNumber switchBankNumber();
    void readRegister(const RFM75BankNumber bank, const uint8_t addr, const uint8_t size, uint8_t *data);
    void writeRegister(const RFM75BankNumber bank, const uint8_t addr, const uint8_t size, const uint8_t *data);

private:
    SPIInterface *pSpi;
};