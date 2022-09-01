#include "esp8266.hpp"
#include "common.hpp"
#define COMMAND_MAX_LENGTH 32
const char *const OK = "OK";
void readUntil(Uart *uart, const char *const pattern)
{
    char buf[1023];
    do
    {
        uart->readString(buf, 1023);
    } while (strcmp(buf, pattern));
}
Esp8266::Esp8266(Uart *uart) : uart(uart)
{
    uart->clearTxFifo();
    uart->clearRxFifo();
    uart->sendString("AT\r\n");
    readUntil(uart, ::OK);
    uart->clearRxFifo();
}
void Esp8266::wifi_connect(const char *ssid, const char *password)
{
    char buf[1024] = "";
    uart->sendString("AT+CWMODE=1\r\n");
    readUntil(uart, ::OK);
    strncat(buf, "AT+CWJAP=\"", COMMAND_MAX_LENGTH);
    strncat(buf, ssid, COMMAND_MAX_LENGTH);
    strncat(buf, "\",\"", COMMAND_MAX_LENGTH);
    strncat(buf, password, COMMAND_MAX_LENGTH);
    strncat(buf, "\"\r\n", COMMAND_MAX_LENGTH);
    uart->sendString(buf);
    readUntil(uart, ::OK);
    uart->clearRxFifo();
}
void Esp8266::tcp_connect(const char *ip, const char *port)
{
    char buf[1024] = "";
    uart->clearRxFifo();
    uart->sendString("AT+CIPMUX=0\r\n");
    readUntil(uart, ::OK);
    strncat(buf, "AT+CIPSTART=\"TCP\",\"", COMMAND_MAX_LENGTH);
    strncat(buf, ip, COMMAND_MAX_LENGTH);
    strncat(buf, "\",", COMMAND_MAX_LENGTH);
    strncat(buf, port, COMMAND_MAX_LENGTH);
    strncat(buf, "\r\n", COMMAND_MAX_LENGTH);
    uart->clearRxFifo();
    uart->sendString(buf);
    readUntil(uart, ::OK);
    uart->clearRxFifo();
}
void Esp8266::tcp_send(const char *data)
{
    char buf[1024] = "";
    u32 data_size = strlen(data) + COMMAND_MAX_LENGTH;
    strncat(buf, "AT+CIPSEND=", COMMAND_MAX_LENGTH);
    itostr(data_size, buf + strlen(buf), 10);
    strncat(buf, "\r\n", COMMAND_MAX_LENGTH);
    u32 temp = strlen(buf);
    strncat(buf, data, strlen(data));
    for (int i = 0; i + temp < COMMAND_MAX_LENGTH; ++i)
        strncat(buf, "\n", COMMAND_MAX_LENGTH);
    uart->clearRxFifo();
    uart->clearTxFifo();
    uart->sendString(buf);
    uart->clearRxFifo();
    uart->clearTxFifo();
}