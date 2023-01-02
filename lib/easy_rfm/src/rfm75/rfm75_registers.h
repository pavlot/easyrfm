#pragma once
#include <stdint.h>
#include <stddef.h>

#include "rfm75_bank_numbers.h"

namespace RFM75Registers
{
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
    // Bank 0 registers
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x00, 1> CONFIG;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x03, 1> SETUP_AW;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x05, 1> RF_CH;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x06, 1> RF_SETUP;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x07, 1> STATUS;
    // End of Bank 0 registers

    // Bank 1 registers
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x00, 4> B1_REG_00;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x01, 4> B1_REG_01;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x02, 4> B1_REG_02;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x03, 4> B1_REG_03;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x04, 4> B1_REG_04;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x05, 4> B1_REG_05;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x08, 4> B1_CHIP_ID;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x0C, 4> B1_REG_0C;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x0D, 4> B1_REG_0D;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x0E, 11> B1_REG_0E;
    // End of Bank 1 registers

    // template <class RFM75RegisterImp>
    // struct RFM75RegisterInterface : public RFM75RegisterImp
    // {
    //     RFM75Register getStruct()
    //     {
    //         struct RFM75Register result = {.bank = this->bank, .addr = this->addr, .size = this->size, .data = this->data};
    //         return result;
    //     }
    // };
} // namespace