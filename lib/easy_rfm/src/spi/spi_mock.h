#pragma once
#include <stdint.h>
// Mock SPI implementation for testing purposes
#include "spi_interface.h"

class SPIMock
{
protected:
    void _init(const uint32_t clock, const uint8_t bitOrder, const uint8_t dataMode)
    {
    };

    void _pins(const uint8_t pinMOSI, const uint8_t pinMISO, const uint8_t pinSCK, const uint8_t pinSS)
    {
    };

    void _write(const uint8_t *write_buffer,
                const uint8_t write_len,
                const bool begin_transaction = false,
                const bool end_transaction = false)
    {
    };
    
    void _exchange(const uint8_t *write_buffer,
                   const uint8_t write_len,
                   uint8_t *read_buffer,
                   const uint8_t read_len,
                   const bool begin_transaction = false,
                   const bool end_transaction = false)
    {
    };
};

typedef SPITemplate<SPIMock> SPIInterface;
