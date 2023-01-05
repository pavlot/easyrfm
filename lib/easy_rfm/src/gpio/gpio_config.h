#pragma once
#ifdef GPIO_ARDUINO
#include "gpio_arduino.h"
#elif GPIO_MOCK
#include "gpio_mock.h"
#else
#include "gpio_arduino.h"
#endif