/*
UART adapter
*/
#ifndef UART_HPP
#define UART_HPP
#include "common.hpp"
class Uart
{
    const u32 RX_OFFSET = 0x00, TX_OFFSET = 0x04, STAT_OFFSET = 0x08, CTRL_OFFSET = 0x0C;
    u32 baseaddr;
    void sendByte(u8 byte);
    u8 readByte();

public:
    /// Create a UART device with its base address
    Uart(u32 baseaddr);
    /// Clear RX FIFO
    void clearRxFifo();
    /// Clear TX FIFO
    void clearTxFifo();
    /// Send a 0-terminated string to the UART
    void sendString(const char *str);
    /// Read a 0-terminated string from the UART, with a maximum length
    void readString(char *str, const u32 max_length);
};
#endif