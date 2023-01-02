#pragma once

#include "rfm75_register_controller.h"
#include "rfm75_tx_power.h"
#include "rfm75_address_width.h"
#include "rfm75_data_rate.h"

class Rfm75ConfigController
{
public:
    explicit Rfm75ConfigController(RFM75RegisterController &registerController);
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

    /*

        def chip_init(self, speed: str):
            """Initialize chip with different magic numbers, required for proper operation

            :param speed: One of: "1Msps","2Msps","250ksps"
            """
            logging.info("Data rate is: {}".format(speed))
            if speed == "1Msps":
                self._register_controller.unset_register_bit(
                    Rfm75Registers.RF_SETUP, 3)
                self._register_controller.unset_register_bit(
                    Rfm75Registers.RF_SETUP, 5)
            if speed == "2Msps":
                self._register_controller.set_register_bit(
                    Rfm75Registers.RF_SETUP, 3)
                self._register_controller.unset_register_bit(
                    Rfm75Registers.RF_SETUP, 5)
            if speed == "250ksps":
                self._register_controller.unset_register_bit(
                    Rfm75Registers.RF_SETUP, 3)
                self._register_controller.set_register_bit(
                    Rfm75Registers.RF_SETUP, 5)

            B1_REG_04_VALUES = {
                "1Msps": [0xF9, 0x96, 0x82, 0x1B],
                "2Msps": [0xF9, 0x96, 0x82, 0xDB],
                "250ksps": [0xF9, 0x96, 0x8A, 0xDB]
            }
            B1_REG_05_VALUES = {
                "1Msps": [0x24, 0x06, 0x0F, 0xA6],
                "2Msps": [0x24, 0x06, 0x0F, 0xB6],
                "250ksps": [0x24, 0x06, 0x0F, 0xB6]
            }
            # Set of magic values provided by datasheet
            self._register_controller.write_register(
                Rfm75Registers.B1_REG_00, [0x40, 0x4B, 0x01, 0xE2])
            self._register_controller.write_register(
                Rfm75Registers.B1_REG_01, [0xC0, 0x4B, 0x00, 0x00])
            self._register_controller.write_register(
                Rfm75Registers.B1_REG_02, [0xD0, 0xFC, 0x8C, 0x02])
            self._register_controller.write_register(
                Rfm75Registers.B1_REG_03, [0x99, 0x00, 0x39, 0x41])
            self._register_controller.write_register(
                Rfm75Registers.B1_REG_04, B1_REG_04_VALUES[speed])
            self._register_controller.write_register(
                Rfm75Registers.B1_REG_05, B1_REG_05_VALUES[speed])
            self._register_controller.write_register(
                Rfm75Registers.B1_REG_0C, [0x00, 0x12, 0x73, 0x00])
            self._register_controller.write_register(
                Rfm75Registers.B1_REG_0D, [0x36, 0xB4, 0x80, 0x00])
            self._register_controller.write_register(
                Rfm75Registers.B1_REG_0E, [0x41, 0x20, 0x08, 0x04, 0x81, 0x20, 0xCF, 0xF7, 0xFE, 0xFF, 0xFF])

        def enable_dynamic_acknowledge(self) -> bytearray:
            return self._register_controller.set_register_bit(Rfm75Registers.FEATURE, 0)

        def is_enabled_dynamic_acknowledge(self) -> bool:
            return self._register_controller.read_register_bit(Rfm75Registers.FEATURE, 0) > 0

        def disable_dynamic_acknowledge(self) -> bytearray:
            return self._register_controller.unset_register_bit(Rfm75Registers.FEATURE, 0)

        def enable_payload_ack(self):
            return self._register_controller.set_register_bit(
                Rfm75Registers.FEATURE, 1)

        def disable_payload_ack(self):
            return self._register_controller.unset_register_bit(
                Rfm75Registers.FEATURE, 1)

        def is_enabled_payload_ack(self):
            return self._register_controller.read_register_bit(
                Rfm75Registers.FEATURE, 1) > 0

        def enable_dynamic_payload(self):
            return self._register_controller.set_register_bit(
                Rfm75Registers.FEATURE, 2)

        def disable_dynamic_payload(self):
            return self._register_controller.unset_register_bit(
                Rfm75Registers.FEATURE, 2)  # Disable dynamic payload

        def is_enabled_dynamic_payload(self):
            return self._register_controller.read_register_bit(Rfm75Registers.FEATURE, 2) > 0

        def set_tx_address(self, address: bytearray) -> bytearray:
            """Set address for TX operation.

            :param address: bytearray with address values. Length depends on value set by set_address_width() method for RX device

            :return:  address bytearray for TX
            """
            logging.info("TX address set to {}".format(address.hex()))
            return self._register_controller.write_register(Rfm75Registers.TX_ADDR, address)*/

private:
    void chipInitRfSetup(const RFM75DataRate data_rate);

    RFM75RegisterController &registerController;
};