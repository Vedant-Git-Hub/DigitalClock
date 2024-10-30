#ifndef H_SPI_H
#define H_SPI_H

#include <stdint.h>
#include <stdbool.h>

#define SPI_PORT	PORTB
#define SCK			PB5
#define MOSI		PB3
#define MISO		PB4
#define CS			PB2


void spi_init(void);
bool spi_writeNonBlocking(uint8_t *, uint16_t);

#endif
