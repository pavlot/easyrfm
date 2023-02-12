#include "rfm75_config_controller.h"
#include "std/initializer_list.h"

Rfm75ConfigController::Rfm75ConfigController(RFM75RegisterController &registerController) : registerController(registerController),
                                                                                            crcConfigController(registerController),
                                                                                            pipeConfigController(registerController){};

//-------------------------------------------------------------------------------------------------------------------
uint8_t Rfm75ConfigController::setRfChannel(uint8_t channel)
{
    RFM75Registers::RF_CH reg;
    reg.data[0] = channel;
    registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
    return getRfChannel();
}
//-------------------------------------------------------------------------------------------------------------------
uint8_t Rfm75ConfigController::getRfChannel()
{
    RFM75Registers::RF_CH reg;
    registerController.readRegister(reg.bank, reg.addr, reg.size, reg.data);
    return reg.data[0];
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::setLnaGainHigh(void)
{
    RFM75Registers::RF_SETUP reg;
    registerController.setRegisterBit(reg, 0);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::setLnaGainLow(void)
{
    RFM75Registers::RF_SETUP reg;
    registerController.unSetRegisterBit(reg, 0);
}
//-------------------------------------------------------------------------------------------------------------------
bool Rfm75ConfigController::isLnaGainLow(void)
{
    RFM75Registers::RF_SETUP reg;
    return registerController.isRegisterBitSet(reg, 0) == false;
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::setTxPower(const RFM75TxPower power)
{
    RFM75Registers::RF_SETUP reg;
    registerController.readRegister(reg.bank, reg.addr, reg.size, reg.data);
    reg.data[0] = reg.data[0] | static_cast<uint8_t>(power);
    registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
}
//-------------------------------------------------------------------------------------------------------------------
RFM75TxPower Rfm75ConfigController::getTxPower()
{
    RFM75Registers::RF_SETUP reg;
    registerController.readRegister(reg.bank, reg.addr, reg.size, reg.data);
    return RFM75TxPower(reg.data[0] & RFM75_TX_POWER_MASK);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::resetConfig()
{
    RFM75Registers::CONFIG reg;
    registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::setAddressWidth(const RFM75AddressWidth address_width)
{
    RFM75Registers::SETUP_AW reg;
    reg.data[0] = static_cast<uint8_t>(address_width);
    registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
}
//-------------------------------------------------------------------------------------------------------------------
RFM75AddressWidth Rfm75ConfigController::getAddressWidth()
{
    RFM75Registers::SETUP_AW reg;
    registerController.readRegister(reg.bank, reg.addr, reg.size, reg.data);
    return RFM75AddressWidth(reg.data[0]);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::chipInit(const RFM75DataRate data_rate)
{
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    {
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
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    {
        RFM75Registers::B1_REG_00 reg;
        reg.setData({0x40, 0x4B, 0x01, 0xE2});
        registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    {
        RFM75Registers::B1_REG_01 reg;
        reg.setData({0xC0, 0x4B, 0x00, 0x00});
        registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    {
        RFM75Registers::B1_REG_02 reg;
        reg.setData({0xD0, 0xFC, 0x8C, 0x02});
        registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    {
        RFM75Registers::B1_REG_03 reg;
        reg.setData({0x99, 0x00, 0x39, 0x41});
        registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    {
        RFM75Registers::B1_REG_04 reg;
        switch (data_rate)
        {
        case RFM75DataRate::DR_250KSPS:
            reg.setData({0xF9, 0x96, 0x8A, 0xDB});
            break;
        case RFM75DataRate::DR_1MSPS:
            reg.setData({0xF9, 0x96, 0x82, 0x1B});
            break;
        case RFM75DataRate::DR_2MSPS:
            reg.setData({0xF9, 0x96, 0x82, 0xDB});
            break;
        default:
            reg.setData({0xF9, 0x96, 0x8A, 0xDB});
            break;
        }

        registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    {
        RFM75Registers::B1_REG_05 reg;
        switch (data_rate)
        {
        case RFM75DataRate::DR_250KSPS:
            reg.setData({0x24, 0x06, 0x0F, 0xB6});
            break;
        case RFM75DataRate::DR_1MSPS:
            reg.setData({0x24, 0x06, 0x0F, 0xA6});
            break;
        case RFM75DataRate::DR_2MSPS:
            reg.setData({0x24, 0x06, 0x0F, 0xB6});
            break;
        default:
            reg.setData({0x24, 0x06, 0x0F, 0xB6});
            break;
        }

        registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    {
        RFM75Registers::B1_REG_0C reg;
        reg.setData({0x00, 0x12, 0x73, 0x00});
        registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    {
        RFM75Registers::B1_REG_0D reg;
        reg.setData({0x36, 0xB4, 0x80, 0x00});
        registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    {
        RFM75Registers::B1_REG_0E reg;
        reg.setData({0x41, 0x20, 0x08, 0x04, 0x81, 0x20, 0xCF, 0xF7, 0xFE, 0xFF, 0xFF});
        registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::enableDynamicAcknowledge()
{
    RFM75Registers::FEATURE reg;
    registerController.setRegisterBit(reg, 0);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::disableDynamicAcknowledge()
{
    RFM75Registers::FEATURE reg;
    registerController.unSetRegisterBit(reg, 0);
}
//-------------------------------------------------------------------------------------------------------------------
bool Rfm75ConfigController::isEnabledDynamicAcknowledge()
{
    RFM75Registers::FEATURE reg;
    return registerController.isRegisterBitSet(reg, 0);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::enablePayloadAck()
{
    RFM75Registers::FEATURE reg;
    registerController.setRegisterBit(reg, 1);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::disablePayloadAck()
{
    RFM75Registers::FEATURE reg;
    registerController.unSetRegisterBit(reg, 1);
}
//-------------------------------------------------------------------------------------------------------------------
bool Rfm75ConfigController::isEnabledPayloadAck()
{
    RFM75Registers::FEATURE reg;
    return registerController.isRegisterBitSet(reg, 1);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::enableDynamicPayload()
{
    RFM75Registers::FEATURE reg;
    registerController.setRegisterBit(reg, 2);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::disableDynamicPayload()
{
    RFM75Registers::FEATURE reg;
    registerController.unSetRegisterBit(reg, 2);
}
//-------------------------------------------------------------------------------------------------------------------
bool Rfm75ConfigController::isEnabledDynamicPayload()
{
    RFM75Registers::FEATURE reg;
    return registerController.isRegisterBitSet(reg, 2);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75ConfigController::setTxAddress(std::initializer_list<uint8_t> addr)
{
    RFM75Registers::TX_ADDR reg;
    std::initializer_list<uint8_t>::const_iterator it;
    uint8_t i = 0;
    for (it = addr.begin(); it < addr.end(); ++it)
    {
        reg.data[i] = *it;
        ++i;
    }
    registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
}
//-------------------------------------------------------------------------------------------------------------------
// Private members
//-------------------------------------------------------------------------------------------------------------------
