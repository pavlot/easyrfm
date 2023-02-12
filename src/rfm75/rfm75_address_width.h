#pragma once
#include <stdint.h>

enum class RFM75AddressWidth
{
    ADDR_3 = 0b01,
    ADDR_4 = 0b10,
    ADDR_5 = 0b11
};

const uint8_t RFM75_ADDRES_WIDTH_MASK = 0b11;