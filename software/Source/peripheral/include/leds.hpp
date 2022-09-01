/*
LEDS driver
*/
#ifndef LEDS_HPP
#define LEDS_HPP
#include "gpio.hpp"
class Leds
{
    Gpio *gpio;
    u32 length, offset, state;

public:
    /// Create a LEDs array bundled with a GPIO device, channel 1
    /// @param gpio: GPIO device
    /// @param length: number of LEDs, 0-31
    /// @param offset: offset of the first LED to the gpio device, 0-31
    Leds(Gpio *gpio, u32 length, u32 offset) : gpio(gpio), length(length), offset(offset) {}
    /// Turn on a LED
    void on(u32 index);
    /// Turn off a LED
    void off(u32 index);
};
#endif