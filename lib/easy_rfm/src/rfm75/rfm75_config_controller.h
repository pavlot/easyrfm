#pragma once

#include "rfm75_register_controller.h"
#include "rfm75_crc_config_controller.h"
#include "rfm75_pipe_config_controller.h"
#include "rfm75_tx_power.h"
#include "rfm75_address_width.h"
#include "rfm75_data_rate.h"

class Rfm75ConfigController
{
public:
    explicit Rfm75ConfigController(RFM75RegisterController &registerController);

    Rfm75CrcConfigController &getCrcConfigController() { return crcConfigController; };
    Rfm75PipeConfigController &getPipeConfigController() { return pipeConfigController; };

    /**
     * @brief The RF channel frequency determines the center of the channel used by RFM75. The
     * frequency is set by the RF_CH register in register bank 0 according to the following
     * formula: F0= 2400 + RF_CH (MHz). The resolution of the RF channel frequency is 1MHz.
     * return channel number set
     *
     * @param channel Channel number to be set
     * @return uint8_t Value stored in channel register
     */
    uint8_t setRfChannel(uint8_t channel);
    uint8_t getRfChannel();

    /**
     * @brief Setup LNA gain to high
     *          0:Low gain(20dB down)
     *          1:High gain
     * */

    void setLnaGainHigh(void);
    void setLnaGainLow(void);
    bool isLnaGainLow(void);

    void setTxPower(const RFM75TxPower power);
    RFM75TxPower getTxPower();

    void resetConfig();

    void setAddressWidth(const RFM75AddressWidth address_width);
    RFM75AddressWidth getAddressWidth();

    void chipInit(const RFM75DataRate data_rate);

    void enableDynamicAcknowledge();
    void disableDynamicAcknowledge();
    bool isEnabledDynamicAcknowledge();

    void enablePayloadAck();
    void disablePayloadAck();
    bool isEnabledPayloadAck();

    void enableDynamicPayload();
    void disableDynamicPayload();
    bool isEnabledDynamicPayload();

    void setTxAddress(std::initializer_list<uint8_t> addr);

private:
    RFM75RegisterController &registerController;
    Rfm75CrcConfigController crcConfigController;
    Rfm75PipeConfigController pipeConfigController;
};