#pragma once
#include <stdint.h>
#include <stddef.h>
#include "rfm75_bank_numbers.h"
#include "std/initializer_list.h"

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

        void setData(std::initializer_list<uint8_t> args)
        {
            std::initializer_list<uint8_t>::iterator it;
            uint8_t i = 0;
            for (it = args.begin(); it != args.end(); ++it)
            {
                data[i] = *it;
                ++i;
            }
        }
    };
    // Bank 0 registers
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x00, 1> CONFIG;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x01, 1> EN_AA;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x02, 1> EN_RXADDR;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x03, 1> SETUP_AW;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x04, 1> SETUP_RETR;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x05, 1> RF_CH;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x06, 1> RF_SETUP;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x07, 1> STATUS;

    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x0A, 5> RX_ADDR_P0;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x0B, 5> RX_ADDR_P1;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x0C, 1> RX_ADDR_P2;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x0D, 1> RX_ADDR_P3;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x0E, 1> RX_ADDR_P4;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x0F, 1> RX_ADDR_P5;

    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x10, 5> TX_ADDR;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x11, 1> RX_PW_P0;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x12, 1> RX_PW_P1;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x13, 1> RX_PW_P2;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x14, 1> RX_PW_P3;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x15, 1> RX_PW_P4;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x16, 1> RX_PW_P5;

    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x1C, 5> DYNPD;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_0, 0x1D, 5> FEATURE;
    // End of Bank 0 registers

    // Bank 1 registers
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x00, 4> B1_REG_00;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x01, 4> B1_REG_01;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x02, 4> B1_REG_02;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x03, 4> B1_REG_03;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x04, 4> B1_REG_04;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x05, 4> B1_REG_05;
    typedef RFM75RegisterTemplate<RFM75BankNumber::BANK_1, 0x07, 1> STATUS_B1;
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