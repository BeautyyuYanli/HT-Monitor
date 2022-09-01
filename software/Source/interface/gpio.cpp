#include "gpio.hpp"
void Gpio::set_bit(u32 channel, u32 bit, bool value)
{
    if (value)
    {
        channel_data[channel] |= (1 << bit);
    }
    else
    {
        channel_data[channel] &= ~(1 << bit);
    }
    write_reg(baseaddr + channel * CHANNEL_OFFSET, channel_data[channel]);
}
bool Gpio::read_bit(u32 channel, u32 bit)
{
    return (read_reg(baseaddr + channel * CHANNEL_OFFSET) >> bit) & 1;
}
void Gpio::set_direction(u32 channel, u32 bit, bool direction)
{
    if (direction)
    {
        channel_direction[channel] |= (1 << bit);
    }
    else
    {
        channel_direction[channel] &= ~(1 << bit);
    }
    write_reg(baseaddr + channel * CHANNEL_OFFSET + 4, channel_direction[channel]);
}
