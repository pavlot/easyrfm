#pragma once
#ifdef SPI_ARDUINO
#include "spi_arduino.h"
#elif SPI_MOCK
#include "spi_mock.h"
#else
#include "spi_arduino.h"
#endif