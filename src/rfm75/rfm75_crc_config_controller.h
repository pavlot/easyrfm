#pragma once

#include "rfm75_register_controller.h"
#include "rfm75_crc_len.h"

class Rfm75CrcConfigController
{
public:
    explicit Rfm75CrcConfigController(RFM75RegisterController &registerController);
    void setCrcLen(const RFM75CrcLen crc_len);
    RFM75CrcLen getCrcLen();
    void enableCrc();
    void disableCrc();
    bool isCrcEnabled();
private:
    RFM75RegisterController &registerController;
};