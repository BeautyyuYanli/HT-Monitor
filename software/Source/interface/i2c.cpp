#include "i2c.hpp"
I2c::I2c(u32 baseaddr) : baseaddr(baseaddr)
{
    // Set the RX_FIFO depth to maximum by setting RX_FIFO_PIRQ
    write_reg(baseaddr + RX_FIFO_PIRQ_OFFSET, 0x0f);
    // Reset the TX_FIFO
    write_reg(baseaddr + CR_OFFSET, 0x02);
    // Enable the AXI IIC, remove the TX_FIFO reset,
    // and disable the general call
    write_reg(baseaddr + CR_OFFSET, 0x01);
}
void I2c::readData(u32 addr, u8 *data, u32 len)
{
    // Check that all FIFOs are empty and that the bus is not busy
    // by reading the Status register
    u8 stat = read_reg(baseaddr + SR_OFFSET);
    while ((stat & 0xc0) != 0xc0 || (stat & 0x04))
        ;
    // Request for a read operation
    write_reg(baseaddr + TX_OFFSET, 0x100 | (addr << 1) | 0x01);
    write_reg(baseaddr + TX_OFFSET, 0x200 | len);
    for (u32 i = 0; i < len; i++)
    {
        // Wait for RX FIFO to have at least one byte
        while ((read_reg(baseaddr + SR_OFFSET) & 0x40) == 0x40)
            ;
        // Read the data from the RX_FIFO
        data[i] = read_reg(baseaddr + RX_OFFSET);
    }
}
void I2c::writeData(u32 addr, const u8 *data, u32 len)
{
    // Check that all FIFOs are empty and that the bus is not busy
    // by reading the Status register
    u8 stat = read_reg(baseaddr + SR_OFFSET);
    while ((stat & 0xc0) != 0xc0 || (stat & 0x04))
        ;
    // Request for a write operation
    write_reg(baseaddr + TX_OFFSET, 0x100 | (addr << 1));
    for (u32 i = 0; i < len - 1; i++)
    {
        // Wait for TX FIFO to be not full
        while ((read_reg(baseaddr + SR_OFFSET) & 0x10) == 0x10)
            ;
        // Write the data to the TX_FIFO
        write_reg(baseaddr + TX_OFFSET, data[i]);
    }
    while ((read_reg(baseaddr + SR_OFFSET) & 0x10) == 0x10)
        ;
    // Write the last byte of data to the TX_FIFO
    write_reg(baseaddr + TX_OFFSET, 0x200 | data[len - 1]);
    // Wait for the bus to be empty
    while ((read_reg(baseaddr + SR_OFFSET) & 0x80) != 0x80)
        ;
}