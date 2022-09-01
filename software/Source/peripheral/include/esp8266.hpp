/*
ESP8266 driver
*/
#ifndef ESP8266_HPP
#define ESP8266_HPP
#include "uart.hpp"
class Esp8266
{
    Uart *uart;

public:
    /// Create a ESP8266 device with its UART device
    Esp8266(Uart *uart);
    void wifi_connect(const char *ssid, const char *password);
    void tcp_connect(const char *ip, const char *port);
    void tcp_send(const char *data);
};

#endif