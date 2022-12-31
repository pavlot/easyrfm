#include <Arduino.h>
#include <spi/spi_config.h>
#include <rfm75/rfm75_controller.h>

SPIInterface spiInterface;
Rfm75Controller rfm75Controller(&spiInterface);

void outputRegisterValue(const RFM75Registers::RFM75Register &reg)
{
  for (int i = 0; i < reg.size; ++i)
  {
    Serial.write(reg.data[i]);
  }
}
void SPI_init()
{
  spiInterface.init(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0);
  spiInterface.pins(14, 15, 16, 2);
}
void setup()
{
  Serial.begin(9600);
  SPI_init();
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
  char a = 251;
  //    Serial.write(static_cast<uint8_t>(rfm75Controller.getRegisterController().getBankNumber()));
  delay(100);
  outputRegisterValue(rfm75Controller.getChipId());
  // rfm75Controller.resetConfig();
  //  rfm75Controller.getRegisterController().getBankNumber();
  //  rfm75Controller.getRegisterController().switchBankNumber();
  //  rfm75Controller.getRegisterController().getBankNumber();

  // RFM75Registers::RFM75RegisterInterface<RFM75Registers::CONFIG> reg_interface;
  // RFM75Registers::RFM75Register reg = reg_interface.getStruct();
  // rfm75Controller.getRegisterController().setRegisterBit(reg, 2);
  // rfm75Controller.getRegisterController().readRegister(reg);

  // Serial.write(a);
  // uint8_t b = reg.getAs<uint8_t>();
  // Serial.write(b);

  // rfm75Controller.getRegisterController().unSetRegisterBit(reg, 2);
  // rfm75Controller.getRegisterController().readRegister(reg);
  delay(100);
  // Serial.print("Test");
}