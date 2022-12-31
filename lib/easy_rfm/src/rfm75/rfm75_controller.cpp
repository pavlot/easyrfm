#include "spi/spi_config.h"
#include "rfm75_controller.h"

Rfm75Controller::Rfm75Controller(SPIInterface *iSpi):pSpi(iSpi),registerController(pSpi)
{

}

void Rfm75Controller::setOnDebug(void (*f)(const char *s))
{
    pDebugFunction = f;
}

void Rfm75Controller::debug(const char *s)
{
    if (pDebugFunction)
    {
        pDebugFunction(s);
    }
}
void Rfm75Controller::resetConfig()
{
        RFM75Registers::RFM75RegisterInterface<RFM75Registers::CONFIG> reg_interface;
        RFM75Registers::RFM75Register reg = reg_interface.getStruct();
        reg.data[0] = 0;
        registerController.writeRegister(reg); 
}

RFM75Registers::RFM75Register Rfm75Controller::getChipId()
{
        RFM75Registers::RFM75RegisterInterface<RFM75Registers::B1_CHIP_ID> reg_interface;
        RFM75Registers::RFM75Register reg = reg_interface.getStruct();
        registerController.readRegister(reg); 
        return reg;
}
