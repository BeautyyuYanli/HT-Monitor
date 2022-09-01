/*
GPIO adapter
*/
#ifndef GPIO_HPP
#define GPIO_HPP
#include "common.hpp"
class Gpio
{
    const u32 CHANNEL_OFFSET = 8;
    u32 baseaddr, channel_data[2] = {0, 0}, channel_direction[2] = {0, 0};

public:
    /// Create a GPIO device with its base address
    Gpio(u32 baseaddr) : baseaddr(baseaddr) {}
    /// Set a bit in a GPIO channel of data to a value
    /// @param channel: 0 or 1
    /// @param bit: 0-31
    /// @param value: bool value
    void set_bit(u32 channel, u32 bit, bool value);
    bool read_bit(u32 channel, u32 bit);
    void set_direction(u32 channel, u32 bit, bool direction);
};
#endif