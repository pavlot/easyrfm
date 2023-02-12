#pragma once

#include "rfm75_register_controller.h"

class Rfm75PipeConfigController
{
public:
    explicit Rfm75PipeConfigController(RFM75RegisterController &registerController);
    void enablePipe(const uint8_t pipe_no);

    void disablePipe(const uint8_t pipe_no);
    void disableAutoAcknowledge();
    bool isEnabledAutoAcknowledge();

    void enablePipeAutoAcknowledge(const uint8_t pipe_no);
    void disablePipeAutoAcknowledge(const uint8_t pipe_no);
    bool isEnabledPipeAutoAcknowledge(const uint8_t pipe_no);

    void enablePipeDynamicPayload(const uint8_t pipe_no);
    void disablePipeDynamicPayload(const uint8_t pipe_no);
    bool isEnabledPipeDynamicPayload(const uint8_t pipe_no);

    template <typename PipeAddrRegType>
    void setRxPipeAddress(const PipeAddrRegType &reg)
    {
        registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
    }

    template <typename PipeAddrRegType>
    PipeAddrRegType getRxPipeAddress()
    {
        PipeAddrRegType reg;
        registerController.readRegister(reg.bank, reg.addr, reg.size, reg.data);
        return reg;
    }

    template <typename PipePayloadWidthRegType>
    void setRxPipePayloadWidth(const uint8_t pld_width)
    {
        PipePayloadWidthRegType reg;
        reg.data[0] = pld_width;
        registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
    }
    template <typename PipePayloadWidthRegType>
    uint8_t getRxPipePayloadWidth()
    {
        PipePayloadWidthRegType reg;
        registerController.readRegister(reg.bank, reg.addr, reg.size, reg.data);
        return reg.data[0];
    }

private:
    RFM75RegisterController &registerController;
};