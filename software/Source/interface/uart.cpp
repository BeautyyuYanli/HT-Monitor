#include "uart.hpp"
void Uart::sendByte(u8 byte)
{
    // if TX FIFO is not full, write byte to TX FIFO
    while (read_reg(baseaddr + STAT_OFFSET) & 0x08)
        ;
    write_reg(baseaddr + TX_OFFSET, byte);
}
u8 Uart::readByte()
{
    // if RX FIFO is valid, read byte from RX FIFO
    while (!(read_reg(baseaddr + STAT_OFFSET) & 0x01))
        ;
    return read_reg(baseaddr + RX_OFFSET);
}

Uart::Uart(u32 baseaddr) : baseaddr(baseaddr)
{
    clearRxFifo();
    clearTxFifo();
}
void Uart::clearRxFifo()
{
    while ((read_reg(baseaddr + STAT_OFFSET) & 0x01))
        write_reg(baseaddr + CTRL_OFFSET, 0x02);
}
void Uart::clearTxFifo()
{
    write_reg(baseaddr + CTRL_OFFSET, 0x04);
}
void Uart::sendString(const char *str)
{
    while (*str)
    {
        sendByte(*str);
        str++;
    }
    // wait for TX FIFO to be empty
    while (read_reg(baseaddr + STAT_OFFSET) & 0x04)
        ;
}
void Uart::readString(char *const str, const u32 max_length)
{
    u32 i;
    do
    {
        for (i = 0; i < max_length; ++i)
        {
            str[i] = readByte();
            if (str[i] == '\n' || str[i] == '\r' || str[i] == '\0')
            {
                break;
            }
        }
    } while (str[0] == '\n' || str[0] == '\r' || str[0] == '\0');
    str[i] = '\0';
}