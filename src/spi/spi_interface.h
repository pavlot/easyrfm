#pragma once
#include <stdint.h>

template <class SPIImplementation>
class SPITemplate : public SPIImplementation
{
public:
    void init(const uint32_t clock, const uint8_t bitOrder, const uint8_t dataMode) { this->_init(clock, bitOrder, dataMode); }
    void pins(const uint8_t pinMOSI, const uint8_t pinMISO, const uint8_t pinSCK, const uint8_t pinSS)
    {
        this->_pins(pinMOSI, pinMISO, pinSCK, pinSS);
    }
    void write(
        const uint8_t *write_buffer,
        const uint8_t write_len,
        const bool begin_transaction = false,
        const bool end_transaction = false) { this->_write(write_buffer, write_len, begin_transaction, end_transaction); }
    void exchange(
        const uint8_t *write_buffer,
        const uint8_t write_len,
        uint8_t *read_buffer,
        const uint8_t read_len,
        const bool begin_transaction = false,
        const bool end_transaction = false) { this->_exchange(write_buffer, write_len, read_buffer, read_len, begin_transaction, end_transaction); }
};
