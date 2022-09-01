#include "DS_CM3.h"
#include "common.hpp"
#include "gpio.hpp"
#include "uart.hpp"
#include "iic.hpp"
#include "leds.hpp"
#include "esp8266.hpp"
#include "dht20.hpp"
#define WIFI_NAME "TP-LINK_111"
#define WIFI_PASS "12345678"
#define TCP_ADDR "192.168.1.101"
#define TCP_PORT "50002"
int main()
{
    delay_ms(1000);
    volatile u32 tri = *(volatile u32 *)(0x40000004);
    volatile u32 dat = *(volatile u32 *)(0x40000000);
    *(volatile u32 *)0x40000000 = 0x00000001;
    tri = *(volatile u32 *)(0x40000004);
    dat = *(volatile u32 *)(0x40000000);
    *(volatile u32 *)0x40000004 = 0xfffffffe;
    tri = *(volatile u32 *)(0x40000004);
    dat = *(volatile u32 *)(0x40000000);
    *(volatile u32 *)0x40000000 = 0x00000002;
    tri = *(volatile u32 *)(0x40000004);
    dat = *(volatile u32 *)(0x40000000);
}