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
    void setRegisterBit(RFM75Registers::RFM75Register &reg, uint8_t bit_num);
    void unSetRegisterBit(RFM75Registers::RFM75Register &reg, uint8_t bit_num);
    bool isRegisterBitSet(RFM75Registers::RFM75Register &reg, uint8_t bit_num);
    void setBankNumber(RFM75BankNumber number);
    RFM75BankNumber getBankNumber();
    RFM75BankNumber switchBankNumber();
    void readRegister(RFM75Registers::RFM75Register &reg);
    void writeRegister(RFM75Registers::RFM75Register &reg);
private:
    SPIInterface *pSpi;
};