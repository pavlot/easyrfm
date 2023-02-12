#include "rfm75_crc_config_controller.h"

Rfm75CrcConfigController::Rfm75CrcConfigController(RFM75RegisterController &registerController) : registerController(registerController){};

//-------------------------------------------------------------------------------------------------------------------
void Rfm75CrcConfigController::setCrcLen(const RFM75CrcLen crc_len)
{
    RFM75Registers::CONFIG reg;
    if (crc_len == RFM75CrcLen::CRC_2)
    {
        registerController.setRegisterBit(reg, 2);
    }
    else
    {
        registerController.unSetRegisterBit(reg, 2);
    }
}
//-------------------------------------------------------------------------------------------------------------------

RFM75CrcLen Rfm75CrcConfigController::getCrcLen()
{
    RFM75Registers::CONFIG reg;
    return registerController.isRegisterBitSet(reg, 2) ? RFM75CrcLen::CRC_2 : RFM75CrcLen::CRC_1;
}
//-------------------------------------------------------------------------------------------------------------------

void Rfm75CrcConfigController::enableCrc()
{
    RFM75Registers::CONFIG reg;
    registerController.setRegisterBit(reg, 3);
}
//-------------------------------------------------------------------------------------------------------------------

void Rfm75CrcConfigController::disableCrc()
{
    RFM75Registers::CONFIG reg;
    registerController.unSetRegisterBit(reg, 3);
}
//-------------------------------------------------------------------------------------------------------------------

bool Rfm75CrcConfigController::isCrcEnabled()
{
    RFM75Registers::CONFIG reg;
    return registerController.isRegisterBitSet(reg, 3);
}
//-------------------------------------------------------------------------------------------------------------------
