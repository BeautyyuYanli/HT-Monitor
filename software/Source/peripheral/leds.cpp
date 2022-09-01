#include "leds.hpp"
void Leds::on(u32 index)
{
    gpio->set_bit(0, index + offset, true);
}
void Leds::off(u32 index)
{
    gpio->set_bit(0, index + offset, false);
}