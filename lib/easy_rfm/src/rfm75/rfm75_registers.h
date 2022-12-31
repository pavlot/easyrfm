#pragma once
#include <stdint.h>
#include <stddef.h>

#include "rfm75_bank_numbers.h"

namespace RFM75Registers
{
    struct RFM75Register
    {
        const RFM75BankNumber bank;
        const uint8_t addr;
        const size_t size;
        uint8_t *data;

        const uint8_t BYTE_LEN_BITS = 3;

        uint8_t getDataIndex(const uint8_t bit_num) const
        {
            return bit_num >> BYTE_LEN_BITS; // Div 8
        }

        bool isBitSet(const uint8_t bit_num) const
        {
            uint8_t index = getDataIndex(bit_num);
            uint8_t mask = bit_num - ((bit_num >> BYTE_LEN_BITS) << BYTE_LEN_BITS);
            mask = 1 << mask;
            return this->data[index] & mask;
        }

        void setBit(const uint8_t bit_num)
        {
            uint8_t index = getDataIndex(bit_num);
            uint8_t mask = bit_num - ((bit_num >> BYTE_LEN_BITS) << BYTE_LEN_BITS);
            mask = 1 << mask;
            this->data[index] = this->data[index] | mask;
        }

        void unsetBit(const uint8_t bit_num)
        {
            uint8_t index = getDataIndex(bit_num);
            uint8_t mask = bit_num - ((bit_num >> BYTE_LEN_BITS) << BYTE_LEN_BITS);
            mask = 1 << mask;
            this->data[index] = this->data[index] & ~mask;
        }
    };

    template <
        RFM75BankNumber reg_bank,
        uint8_t reg_addr,
        uint8_t reg_size>
    struct RFM75RegisterTemplate
    {
        const RFM75BankNumber bank = reg_bank;
        const uint8_t addr = reg_addr;
        const size_t size = reg_size;
        uint8_t data[reg_size] = {0};
    };

    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x00, 1> CONFIG;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x07, 1> STATUS;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x08, 4> B1_CHIP_ID;

    template <class RFM75RegisterImp>
    struct RFM75RegisterInterface : public RFM75RegisterImp
    {
        RFM75Register getStruct()
        {
            struct RFM75Register result = {.bank = this->bank, .addr = this->addr, .size = this->size, .data = this->data};
            return result;
        }
    };
} // namespace