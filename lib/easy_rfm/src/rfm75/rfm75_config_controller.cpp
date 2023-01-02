#include "rfm75_config_controller.h"

Rfm75ConfigController::Rfm75ConfigController(RFM75RegisterController &registerController) : registerController(registerController){};

//-------------------------------------------------------------------------------------------------------------------
uint8_t Rfm75ConfigController::setRfChannel(uint8_t channel)
{
    // RFM75Registers::RFM75RegisterInterface<RFM75Registers::RF_CH> reg_interface;
    // RFM75Registers::RFM75Register reg = reg_interface.getStruct();
RFM75Registers::RF_CH reg;
    reg.data[0] = channel;
    registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
    return getRfChannel();
}
//-------------------------------------------------------------------------------------------------------------------
uint8_t Rfm75ConfigController::getRfChannel()
{
    // RFM75Registers::RFM75RegisterInterface<RFM75Registers::RF_CH> reg_interface;
    // RFM75Registers::RFM75Register reg = reg_interface.getStruct();
RFM75Registers::RF_CH reg;
    registerController.readRegister(reg.bank, reg.addr, reg.size, reg.data);
    return reg.data[0];
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::setLnaGainHigh(void)
{
    // RFM75Registers::RFM75RegisterInterface<RFM75Registers::RF_SETUP> reg_interface;
    // RFM75Registers::RFM75Register reg = reg_interface.getStruct();
    RFM75Registers::RF_SETUP reg;
    registerController.setRegisterBit(reg, 0);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::setLnaGainLow(void)
{
    // RFM75Registers::RFM75RegisterInterface<RFM75Registers::RF_SETUP> reg_interface;
    // RFM75Registers::RFM75Register reg = reg_interface.getStruct();
    RFM75Registers::RF_SETUP reg;
    registerController.unSetRegisterBit(reg, 0);
}
//-------------------------------------------------------------------------------------------------------------------
bool Rfm75ConfigController::isLnaGainLow(void)
{
    // RFM75Registers::RFM75RegisterInterface<RFM75Registers::RF_SETUP> reg_interface;
    // RFM75Registers::RFM75Register reg = reg_interface.getStruct();
    RFM75Registers::RF_SETUP reg;
    return registerController.isRegisterBitSet(reg, 0) == false;
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::setTxPower(const RFM75TxPower power)
{
    // RFM75Registers::RFM75RegisterInterface<RFM75Registers::RF_SETUP> reg_interface;
    // RFM75Registers::RFM75Register reg = reg_interface.getStruct();
    RFM75Registers::RF_SETUP reg;
    registerController.readRegister(reg.bank, reg.addr, reg.size, reg.data);
    reg.data[0] = reg.data[0] | static_cast<uint8_t>(power);
    registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
}
//-------------------------------------------------------------------------------------------------------------------
RFM75TxPower Rfm75ConfigController::getTxPower()
{
    // RFM75Registers::RFM75RegisterInterface<RFM75Registers::RF_SETUP> reg_interface;
    // RFM75Registers::RFM75Register reg = reg_interface.getStruct();
    RFM75Registers::RF_SETUP reg;
    registerController.readRegister(reg.bank, reg.addr, reg.size, reg.data);
    return RFM75TxPower(reg.data[0] & RFM75_TX_POWER_MASK);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::resetConfig()
{
    // RFM75Registers::RFM75RegisterInterface<RFM75Registers::CONFIG> reg_interface;
    // RFM75Registers::RFM75Register reg = reg_interface.getStruct();
    RFM75Registers::CONFIG reg;
    reg.data[0] = 0;
    registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::setAddressWidth(const RFM75AddressWidth address_width)
{
    // RFM75Registers::RFM75RegisterInterface<RFM75Registers::SETUP_AW> reg_interface;
    // RFM75Registers::RFM75Register reg = reg_interface.getStruct();
    RFM75Registers::SETUP_AW reg;
    reg.data[0] = static_cast<uint8_t>(address_width);
    registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
}
//-------------------------------------------------------------------------------------------------------------------
RFM75AddressWidth Rfm75ConfigController::getAddressWidth()
{
    // RFM75Registers::RFM75RegisterInterface<RFM75Registers::SETUP_AW> reg_interface;
    // RFM75Registers::RFM75Register reg = reg_interface.getStruct();
    RFM75Registers::SETUP_AW reg;
    registerController.readRegister(reg.bank, reg.addr, reg.size, reg.data);
    return RFM75AddressWidth(reg.data[0]);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::chipInit(const RFM75DataRate data_rate)
{
    chipInitRfSetup(data_rate);
}

//-------------------------------------------------------------------------------------------------------------------
// Private members
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::chipInitRfSetup(const RFM75DataRate data_rate)
{
    // RFM75Registers::RFM75RegisterInterface<RFM75Registers::RF_SETUP> ri_rf_setup;
    // RFM75Registers::RFM75Register reg = ri_rf_setup.getStruct();
    RFM75Registers::RF_SETUP reg;
    registerController.readRegister(reg.bank, reg.addr, reg.size, reg.data);
    switch (data_rate)
    {
    case RFM75DataRate::DR_250KSPS:
        reg.unsetBit(3);
        reg.setBit(5);
        break;
    case RFM75DataRate::DR_1MSPS:
        reg.unsetBit(3);
        reg.unsetBit(5);
        break;
    case RFM75DataRate::DR_2MSPS:
        reg.setBit(3);
        reg.unsetBit(5);
        break;
    default:
        reg.unsetBit(3);
        reg.setBit(5);
        break;
    }
    registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
}
