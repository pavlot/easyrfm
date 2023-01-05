#include "spi/spi_config.h"
#include "rfm75_controller.h"
#include "rfm75_commands.h"
//-------------------------------------------------------------------------------------------------------------------

Rfm75Controller::Rfm75Controller(
    SPIInterface *iSpi, GPIOPinInterface *cePin) : pSpi(iSpi), cePin(cePin),
                                                   registerController(pSpi),
                                                   configController(registerController)
{
}
//-------------------------------------------------------------------------------------------------------------------

RFM75Registers::B1_CHIP_ID Rfm75Controller::getChipId()
{
    RFM75Registers::B1_CHIP_ID reg;
    registerController.readRegister(reg.bank, reg.addr, reg.size, reg.data);
    return reg;
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75Controller::activateFeatures()
{
    pSpi->write(RFM75Commands::ACTIVATE_FEATURES, sizeof(RFM75Commands::ACTIVATE_FEATURES), true, true);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75Controller::ceOn()
{
    cePin->setHigh();
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75Controller::ceOff()
{
    cePin->setLow();
}
//-------------------------------------------------------------------------------------------------------------------
uint8_t Rfm75Controller::readRxPayloadLen()
{
    uint8_t result = 0;
    pSpi->exchange(&RFM75Commands::R_RX_PL_WID, 1, &result, 1, true, true);
    return result;
}

//-------------------------------------------------------------------------------------------------------------------
void Rfm75Controller::readRxPayload(const uint8_t size, uint8_t *buffer)
{
    pSpi->exchange(&RFM75Commands::R_RX_PAYLOAD, 1, buffer, size, true, true);
}

//-------------------------------------------------------------------------------------------------------------------
bool Rfm75Controller::isConnected()
{
    RFM75Registers::STATUS reg;
    registerController.readRegister(reg.bank, reg.addr, reg.size, reg.data);
    RFM75Registers::STATUS_B1 reg_b1;
    registerController.readRegister(reg_b1.bank, reg_b1.addr, reg_b1.size, reg_b1.data);
    return (reg.data[0] ^ reg_b1.data[0]) > 0;
}

//-------------------------------------------------------------------------------------------------------------------
void Rfm75Controller::powerUp()
{
    RFM75Registers::CONFIG reg;
    registerController.setRegisterBit(reg, 1);
}

//-------------------------------------------------------------------------------------------------------------------
void Rfm75Controller::powerDown()
{
    RFM75Registers::CONFIG reg;
    registerController.unSetRegisterBit(reg, 1);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75Controller::setModeTx()
{
    {
        RFM75Registers::CONFIG reg;
        registerController.unSetRegisterBit(reg, 0);
    }
    {
        RFM75Registers::STATUS reg;
        reg.data[0] = 0x70;
        registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
    }
    pSpi->write(&RFM75Commands::FLUSH_TX, 1, true, true);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75Controller::setModeRx()
{
    RFM75Registers::CONFIG reg;
    registerController.setRegisterBit(reg, 0);
}

//-------------------------------------------------------------------------------------------------------------------
void Rfm75Controller::writeTxPayload(const uint8_t size, const uint8_t *payload, const bool ack_send = false)
{
    uint8_t command = RFM75Commands::W_TX_PAYLOAD;
    if (getConfigController().getPipeConfigController().isEnabledAutoAcknowledge() && !ack_send)
    {
        command = RFM75Commands::W_TX_PAYLOAD_NO_ACK;
    }
    ceOff();
    pSpi->write(&command, 1, true, false);
    pSpi->write(payload, size, false, true);
    ceOn();
    ceOff();
}
//-------------------------------------------------------------------------------------------------------------------

bool Rfm75Controller::isMaxRt()
{
    RFM75Registers::STATUS reg;
    registerController.isRegisterBitSet(reg, 4);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75Controller::unsetMaxRt()
{
    RFM75Registers::STATUS reg;
    registerController.unSetRegisterBit(reg, 4);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75Controller::isDataSent()
{
    RFM75Registers::STATUS reg;
    registerController.isRegisterBitSet(reg, 5);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75Controller::unsetDataSent()
{
    RFM75Registers::STATUS reg;
    registerController.unSetRegisterBit(reg, 5);
}

//-------------------------------------------------------------------------------------------------------------------
void Rfm75Controller::flushRx()
{
    pSpi->write(&RFM75Commands::FLUSH_RX, 1, true, true);
}
