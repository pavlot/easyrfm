#pragma once
#include "rfm75_register_controller.h"
#include "rfm75_config_controller.h"
#include "spi/spi_config.h"
#include "gpio/gpio_config.h"

//---------- Typedefs --------------------------------
typedef void (*PDebugFunction)(const char *s);
//---------- End of Typedefs -------------------------

//---------- Forward declarations --------------------
//---------- End of Forward declarations -------------

class Rfm75Controller
{
public:
    explicit Rfm75Controller(SPIInterface *iSpi, GPIOPinInterface *cePin);
    RFM75Registers::B1_CHIP_ID getChipId();
    RFM75RegisterController &getRegisterController() { return registerController; };
    Rfm75ConfigController &getConfigController() { return configController; };

    void activateFeatures();
    void ceOn();
    void ceOff();
    uint8_t readRxPayloadLen();

    void readRxPayload(const uint8_t size, uint8_t *buffer);

    bool isConnected();

    void powerUp();

    void powerDown();
    void setModeTx();
    void setModeRx();

    void writeTxPayload(const uint8_t size, const uint8_t *payload, const bool ack_send = false);

    bool isMaxRt();
    void unsetMaxRt();
    bool isRxDr();
    void unsetRxDr();
    bool isDataSent();
    void unsetDataSent();

    void flushRx();

private:
    PDebugFunction pDebugFunction = nullptr;
    SPIInterface *pSpi;
    GPIOPinInterface *cePin;
    RFM75RegisterController registerController;
    Rfm75ConfigController configController;
};