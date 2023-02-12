#pragma once
#include <stdint.h>

enum class RFM75TxPower
{
    TX_PWR_LOW = 0b000,
    TX_PWR_1 = 0b010,
    TX_PWR_2 = 0b100,
    TX_PWR_HIGH = 0b110
};

const uint8_t RFM75_TX_POWER_MASK = 0b110;