#pragma once

#include <stdint.h>

template <class GPIOPinImplementation>
class GPIOPinTemplate : public GPIOPinImplementation
{
public:
    void setPinId(const uint8_t pin_id) { this->_setPinId(pin_id); };
    uint8_t getPinId() { return this->_getPinId(); };
    void pinMode(const uint8_t mode) { this->_pinMode(mode); };
    void setHigh() { this->_setHigh(); };
    void setLow() { this->_setLow(); };
    void isHigh() { this->_isHigh(); };
};