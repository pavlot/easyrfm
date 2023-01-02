#include "spi/spi_config.h"
#include "rfm75_controller.h"

Rfm75Controller::Rfm75Controller(SPIInterface *iSpi):pSpi(iSpi),registerController(pSpi),configController(registerController)
{

}

RFM75Registers::B1_CHIP_ID Rfm75Controller::getChipId()
{
        // RFM75Registers::RFM75RegisterInterface<RFM75Registers::B1_CHIP_ID> reg_interface;
        // RFM75Registers::RFM75Register reg = reg_interface.getStruct();
        RFM75Registers::B1_CHIP_ID reg;
        registerController.readRegister(reg.bank, reg.addr, reg.size, reg.data); 
        return reg;
}
