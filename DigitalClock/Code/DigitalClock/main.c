#include <stdio.h>

#include <avr/io.h>
#include <util/delay.h>

#include "spi.h"
#include "i2c.h"
#include "ds3231.h"
#include "max7219.h"
#include "uart.h"

int main(void)
{
	spi_init();
	i2c_init();
	ds3231_init();
	max7219_init();
	uart_init();
	char arr[] = "Hello";
	while(1)
	{
//		uart_transmit('V');
		fputs(arr, stdout);
		_delay_ms(100);
	}
	return 0;
}
