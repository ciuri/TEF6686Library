#include "TEF6686I2CComm.h"
#include <Wire.h>

void TEF6686I2CComm::GetCommand(uint8_t module, uint8_t cmd, uint16_t *response, uint8_t responseLength)
{
    Wire.beginTransmission(DEVICE_ADDR);
    Wire.write(module);
    Wire.write(cmd);
    Wire.write(1);
    Wire.endTransmission();
    uint8_t dataLength = Wire.requestFrom(DEVICE_ADDR, (uint8_t)(responseLength * 2));
    for (int i = 0; i < dataLength / 2; i++)
    {
        uint8_t msb = Wire.read();
        uint8_t lsb = Wire.read();
        response[i] = msb << 8 | lsb;
    }
}

void TEF6686I2CComm::SetCommand(uint8_t module, uint8_t cmd, uint16_t *params, uint8_t paramsCount)
{
    Wire.beginTransmission(DEVICE_ADDR);
    Wire.write(module);
    Wire.write(cmd);
    Wire.write(1);
    for (int i = 0; i < paramsCount; i++)
    {
        uint8_t msb = params[i] >> 8;
        uint8_t lsb = params[i];
        Wire.write(msb);
        Wire.write(lsb);
    }
    Wire.endTransmission();
}
