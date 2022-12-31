#pragma once
#include "rfm75_register_controller.h"
#include "spi/spi_config.h"

//---------- Typedefs --------------------------------
typedef void (*PDebugFunction)(const char *s);
//---------- End of Typedefs -------------------------

//---------- Forward declarations --------------------
//---------- End of Forward declarations -------------

class Rfm75Controller
{
public:
    explicit Rfm75Controller(SPIInterface *iSpi);
    void setOnDebug(PDebugFunction);
    void debug(const char *s);

    void resetConfig();
    RFM75Registers::RFM75Register getChipId();
    RFM75RegisterController& getRegisterController(){return registerController;}; 


private:
    PDebugFunction pDebugFunction = nullptr;
    SPIInterface *pSpi;
    RFM75RegisterController registerController; 
};