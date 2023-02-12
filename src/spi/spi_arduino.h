#pragma once
#include <stdint.h>
// Arduino based SPI implementation
#include <SPI.h>
#include "spi_interface.h"

class SPIArduino
{
protected:
    void _init(const uint32_t clock, const uint8_t bitOrder, const uint8_t dataMode)
    {
        SPI.begin();

        SPI.setClockDivider(clock); // SPI_CLOCK_DIV4
        SPI.setBitOrder(bitOrder);  // MSBFIRST
        SPI.setDataMode(dataMode);  // SPI_MODE0
    };

    void _pins(const uint8_t pinMOSI, const uint8_t pinMISO, const uint8_t pinSCK, const uint8_t pinSS)
    {
        this->pinCS = pinSS;
        SPI.pins(pinMOSI, pinMISO, pinSCK, pinSS);
        pinMode(pinSS, OUTPUT);
    };

    void _write(const uint8_t *write_buffer,
                const uint8_t write_len,
                const bool begin_transaction = false,
                const bool end_transaction = false)
    {
        if (begin_transaction)
        {
            pinSSOn();
        }

        if (write_buffer && write_len > 0)
        {
            for (int i = 0; i < write_len; ++i)
            {
                SPI.transfer(write_buffer[i]);
            }
        }
        if (end_transaction)
        {
            pinSSOff();
        }
    };
    
    void _exchange(const uint8_t *write_buffer,
                   const uint8_t write_len,
                   uint8_t *read_buffer,
                   const uint8_t read_len,
                   const bool begin_transaction = false,
                   const bool end_transaction = false)
    {
        if (begin_transaction)
        {
            pinSSOn();
        }
        this->_write(write_buffer, write_len, false, false);
        if (read_buffer && read_len > 0)
        {
            for (int i = 0; i < read_len; ++i)
            {
                read_buffer[i] = SPI.transfer(0);
            }
        }
        if (end_transaction)
        {
            pinSSOff();
        }
    };

private:
    void pinSSOn() { digitalWrite(pinCS, LOW); }
    void pinSSOff() { digitalWrite(pinCS, HIGH); }
    uint8_t pinCS = 0;
};

typedef SPITemplate<SPIArduino> SPIInterface;
