#pragma once
#include <stdint.h>

namespace RFM75Commands
{
    const uint8_t WRITE = 0x20;
    const uint8_t ACTIVATE_FEATURES[] = {0x50, 0x73};
    const uint8_t R_RX_PL_WID = 0x60;
    const uint8_t R_RX_PAYLOAD = 0x61;
    const uint8_t W_TX_PAYLOAD = 0xA0;
    const uint8_t W_TX_PAYLOAD_NO_ACK = 0xB0;
    const uint8_t FLUSH_TX = 0xE1;
    const uint8_t FLUSH_RX = 0xE2;

};
