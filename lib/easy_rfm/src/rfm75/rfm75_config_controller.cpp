#include "rfm75_config_controller.h"

Rfm75ConfigController::Rfm75ConfigController(RFM75RegisterController &registerController) : registerController(registerController){};

//-------------------------------------------------------------------------------------------------------------------
uint8_t Rfm75ConfigController::setRfChannel(uint8_t channel)
{
    RFM75Registers::RFM75RegisterInterface<RFM75Registers::RF_CH> reg_interface;
    RFM75Registers::RFM75Register reg = reg_interface.getStruct();
    reg.data[0] = channel;
    registerController.writeRegister(reg);
    return getRfChannel();
}
//-------------------------------------------------------------------------------------------------------------------
uint8_t Rfm75ConfigController::getRfChannel()
{
    RFM75Registers::RFM75RegisterInterface<RFM75Registers::RF_CH> reg_interface;
    RFM75Registers::RFM75Register reg = reg_interface.getStruct();
    registerController.readRegister(reg);
    return reg.data[0];
}
