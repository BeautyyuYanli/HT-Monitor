#include "dht20.hpp"
#include "common.hpp"

Dht20::Dht20(I2c *i2c) : i2c(i2c)
{
    u8 readCMD[3] = {0x71};
    u8 data;
    do
    {
        delay_ms(500);
        // check if the IIC communication works
        i2c->writeData(ADDRESS, readCMD, 1);
        delay_ms(10);
        i2c->readData(ADDRESS, &data, 1);
    } while ((data & 0x18) != 0x18);
}
float Dht20::getTemperature()
{
    delay_ms(10);
    u8 readCMD[3] = {0xac, 0x33, 0x00};
    u8 data[6] = {0};
    int retries = 10;
    float temperature;
    i2c->writeData(ADDRESS, readCMD, 3);
    while (retries--)
    {
        delay_ms(80);
        i2c->readData(ADDRESS, data, 6);
        if ((data[0] >> 7) == 0)
            break;
    }
    u32 temp = data[3] & 0xff;
    u32 temp1 = data[4] & 0xff;
    u32 rawData = 0;
    rawData = ((temp & 0xf) << 16) + (temp1 << 8) + (data[5]);
    temperature = (float)rawData / 5242 - 50;
    return temperature;
}
float Dht20::getHumidity()
{
    delay_ms(10);
    u8 readCMD[3] = {0xac, 0x33, 0x00};
    u8 data[6] = {0};
    int retries = 10;
    float humidity;
    i2c->writeData(ADDRESS, readCMD, 3);
    while (retries--)
    {
        ::delay_ms(20);
        i2c->readData(ADDRESS, data, 6);
        if ((data[0] >> 7) == 0)
            break;
    }
    u32 temp = data[1] & 0xff;
    u32 temp1 = data[2] & 0xff;
    u32 rawData = 0;
    rawData = (temp << 12) + (temp1 << 4) + ((data[3] & 0xf0) >> 4);
    humidity = (float)rawData / 0x100000;
    return humidity;
}