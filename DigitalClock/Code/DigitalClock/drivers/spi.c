#include "spi.h"
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>


void spi_init()
{
	//Set MOSI, SCK and CS pin as output
	SPI_PORT |= (1 << SCK) | (1 << MOSI) | (1 << CS);
	//Set MISO pin as input
	SPI_PORT &= ~(1 << MISO);
	//Enable SPI and configure as master
	SPCR |= (1 << SPE) | (1 << MSTR);
	//SPI mode selected as SPI-0
	SPCR &= ~(1 << CPOL) & ~(1 << CPHA);
	//SPI speed set to 16MHz/4 and enable SPI interrupt
	SPCR &= ~(1 << SPR1) & ~(1 << SPR0);
	SPSR |= (1 << SPI2X);
	SPCR |= (1 << SPIE);
	//Clear interrupt flags by reading status and data register
	char temp = SPSR;
	temp = SPDR;
	temp++;
	//Enable global interrupts
	sei();
}

bool spi_writeNonBlocking(uint8_t *data, uint16_t bytes)
{
	bool write_status = false;

	return write_status;
}
