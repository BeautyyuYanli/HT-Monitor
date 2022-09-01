#ifndef DHT20_HPP
#define DHT20_HPP
#include "i2c.hpp"
class Dht20
{
    I2c *i2c;
    const u8 ADDRESS = 0x38;

public:
    /**
     * @brief init function
     * @return Return 0 if initialization succeeds, otherwise return non-zero and error code.
     */
    Dht20(I2c *i2c);
    int begin();
    float getTemperature();
    float getHumidity();
};
#endif