#pragma once
#include "Arduino.h"
#include "gpio_interface.h"

class GPIOPinArduino
{
protected:
    void _setPinId(const uint8_t pin_id) { this->pin_id = pin_id; };
    uint8_t _getPinId() { return this->pin_id; };
    void _pinMode(const uint8_t mode) { pinMode(this->pin_id, mode); };
    void _setHigh() { digitalWrite(this->pin_id, HIGH); };
    void _setLow() { digitalWrite(this->pin_id, LOW); };
    bool _isHigh() { return digitalRead(this->pin_id) == HIGH; };
    uint8_t pin_id = 0;
};

typedef GPIOPinTemplate<GPIOPinArduino> GPIOPinInterface;