#include "DS_CM3.h"
#include "common.hpp"
#include "gpio.hpp"
#include "uart.hpp"
#include "i2c.hpp"
#include "leds.hpp"
#include "esp8266.hpp"
#include "dht20.hpp"
// To be configured before compiling
#define WIFI_NAME "TP-LINK_111"
#define WIFI_PASS "12345678"
#define TCP_ADDR "192.168.1.101"
#define TCP_PORT "50002"
int main()
{
	delay_ms(500);
	// Create low level interfaces
	Uart uart(0x40600000);
	Gpio gpio(0x40000000);
	I2c i2c(0x40800000);

	Leds leds(&gpio, 3, 0);

	// start DHT20
	Dht20 dht20(&i2c);
	leds.on(0);

	// start ESP8266
	Esp8266 esp8266(&uart);
	esp8266.wifi_connect(WIFI_NAME, WIFI_PASS);
	leds.on(1);

	esp8266.tcp_connect(TCP_ADDR, TCP_PORT);
	while (1)
	{
		leds.on(2);
		float t = dht20.getTemperature(),
			  h = dht20.getHumidity();
		char buf[64] = "";
		itostr(t * 1000, buf, 10);
		strncat(buf, ",", 64);
		itostr(h * 1000, buf + strlen(buf), 10);
		esp8266.tcp_send(buf);
		leds.off(2);
		delay_ms(3000);
	}
}
