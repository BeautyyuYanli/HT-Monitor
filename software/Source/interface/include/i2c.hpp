/*
I2C adapter
*/
#ifndef I2C_HPP
#define I2C_HPP
#include "common.hpp"
class I2c
{
    u32 baseaddr;
    const u32 CR_OFFSET = 0x100, SR_OFFSET = 0x104,
              TX_OFFSET = 0x108, RX_OFFSET = 0x10c,
              RX_FIFO_PIRQ_OFFSET = 0x120;

public:
    I2c(u32 baseaddr);
    void readData(u32 addr, u8 *data, u32 len);
    void writeData(u32 addr, const u8 *data, u32 len);
};
#endif