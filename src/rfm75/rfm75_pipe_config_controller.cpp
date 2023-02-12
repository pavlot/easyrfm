#include "rfm75_pipe_config_controller.h"

Rfm75PipeConfigController::Rfm75PipeConfigController(RFM75RegisterController &registerController) : registerController(registerController){};

//-------------------------------------------------------------------------------------------------------------------
void Rfm75PipeConfigController::enablePipe(const uint8_t pipe_no)
{
    RFM75Registers::EN_RXADDR reg;
    registerController.setRegisterBit(reg, pipe_no);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75PipeConfigController::disablePipe(const uint8_t pipe_no)
{
    RFM75Registers::EN_RXADDR reg;
    registerController.unSetRegisterBit(reg, pipe_no);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75PipeConfigController::disableAutoAcknowledge()
{
    RFM75Registers::EN_AA reg;
    registerController.writeRegister(reg.bank, reg.addr, reg.size, reg.data);
}
//-------------------------------------------------------------------------------------------------------------------
bool Rfm75PipeConfigController::isEnabledAutoAcknowledge()
{
    RFM75Registers::EN_AA reg;
    registerController.readRegister(reg.bank, reg.addr, reg.size, reg.data);
    return reg.data[0] == 0;
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75PipeConfigController::enablePipeAutoAcknowledge(const uint8_t pipe_no)
{
    RFM75Registers::EN_AA reg;
    registerController.setRegisterBit(reg, pipe_no);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75PipeConfigController::disablePipeAutoAcknowledge(const uint8_t pipe_no)
{
    RFM75Registers::EN_AA reg;
    registerController.unSetRegisterBit(reg, pipe_no);
}
//-------------------------------------------------------------------------------------------------------------------
bool Rfm75PipeConfigController::isEnabledPipeAutoAcknowledge(const uint8_t pipe_no)
{
    RFM75Registers::EN_AA reg;
    return registerController.isRegisterBitSet(reg, pipe_no);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75PipeConfigController::enablePipeDynamicPayload(const uint8_t pipe_no)
{
    RFM75Registers::DYNPD reg;
    registerController.setRegisterBit(reg, pipe_no);
}
//-------------------------------------------------------------------------------------------------------------------
void Rfm75PipeConfigController::disablePipeDynamicPayload(const uint8_t pipe_no)
{
    RFM75Registers::DYNPD reg;
    registerController.unSetRegisterBit(reg, pipe_no);
}
//-------------------------------------------------------------------------------------------------------------------
bool Rfm75PipeConfigController::isEnabledPipeDynamicPayload(const uint8_t pipe_no)
{
    RFM75Registers::DYNPD reg;
    return registerController.isRegisterBitSet(reg, pipe_no);
}
//-------------------------------------------------------------------------------------------------------------------
