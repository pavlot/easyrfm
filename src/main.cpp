#include <Arduino.h>
#include <spi/spi_config.h>
#include <rfm75/rfm75_controller.h>
#include <rfm75/rfm75_data_rate.h>

SPIInterface spiInterface;
GPIOPinInterface cePin;
Rfm75Controller rfm75Controller(&spiInterface, &cePin);

#define CE_PIN 0
#define PIPE_NO 0                              // Pipe number used to receive data
#define ADDR_WIDTH 5                           // How many bytes used for address
#define PIPE_ADDR {0x11, 0x22, 0x33, 0x22, 0x11} // Addres for selected pipe
#define RF_CHANNEL 0x02                        // Operating Rf Channel
#define DATA_RATE RFM75DataRate::DR_1MSPS      // Transfer speed
#define PAYLOAD_SIZE 0x01                      // Static payload size up to 1b

template <typename RegisterType>
void outputRegisterValue(const RegisterType &reg)
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

void RFM75_init()
{
  cePin.setPinId(CE_PIN);
  cePin.pinMode(OUTPUT);
  cePin.setLow();

  outputRegisterValue(rfm75Controller.getChipId());
  rfm75Controller.powerDown();
  rfm75Controller.getConfigController().resetConfig();
  rfm75Controller.getConfigController().setRfChannel(RF_CHANNEL);
  rfm75Controller.getConfigController().setLnaGainLow();
  rfm75Controller.getConfigController().chipInit(DATA_RATE);
  rfm75Controller.getConfigController().disableDynamicPayload();
  rfm75Controller.getConfigController().disableDynamicAcknowledge();
  rfm75Controller.activateFeatures();
  rfm75Controller.getConfigController().setAddressWidth(RFM75AddressWidth::ADDR_5);
  rfm75Controller.getConfigController().getPipeConfigController().enablePipe(PIPE_NO);
  RFM75Registers::RX_ADDR_P0 reg;
  reg.setData(PIPE_ADDR);
  rfm75Controller.getConfigController().getPipeConfigController().setRxPipeAddress(reg);
  rfm75Controller.getConfigController().getPipeConfigController().setRxPipePayloadWidth<RFM75Registers::RX_PW_P0>(PAYLOAD_SIZE);
  rfm75Controller.getConfigController().getPipeConfigController().disableAutoAcknowledge();
//  rfm75Controller.getConfigController().getCrcConfigController().setCrcLen(RFM75CrcLen::CRC_2);
  rfm75Controller.getConfigController().getCrcConfigController().disableCrc();
  rfm75Controller.setModeRx();
  rfm75Controller.powerUp();
  rfm75Controller.ceOn();

}
void setup()
{
  Serial.begin(9600);
  SPI_init();
  RFM75_init();

  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
  char a = 254;
  Serial.write(a);
  //    Serial.write(static_cast<uint8_t>(rfm75Controller.getRegisterController().getBankNumber()));
  if(rfm75Controller.readRxPayloadLen()>0)
  {
    uint8_t data = 0;
    rfm75Controller.readRxPayload(1, &data);
    Serial.flush();
    Serial.write(data);
  }
//  Serial.write(a);
  //  rfm75Controller.getRegisterController().getBankNumber();
  //  rfm75Controller.getRegisterController().switchBankNumber();
  //  rfm75Controller.getRegisterController().getBankNumber();

  // RFM75Registers::RFM75RegisterInterface<RFM75Registers::CONFIG> reg_interface;
  // RFM75Registers::RFM75Register reg = reg_interface.getStruct();
  // rfm75Controller.getRegisterController().setRegisterBit(reg, 2);
  // rfm75Controller.getRegisterController().readRegister(reg.bank, reg.addr, reg.size, reg.data);

  // Serial.write(a);
  // uint8_t b = reg.getAs<uint8_t>();
  // Serial.write(b);

  // rfm75Controller.getRegisterController().unSetRegisterBit(reg, 2);
  // rfm75Controller.getRegisterController().readRegister(reg.bank, reg.addr, reg.size, reg.data);
  // Serial.print("Test");
}