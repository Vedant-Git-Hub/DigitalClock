#ifndef H_UART_H
#define H_UART_H

#include <stddef.h> //size_t type
#include <stdint.h> //uint8_t type
#include <stdio.h>  //FILE type



//default to 9600
#ifndef BAUD
    #define BAUD 115200
#endif



/** Stream that outputs to the UART. */
extern FILE uart_out;
/** Stream that reads from the UART. */
extern FILE uart_in;



/**
 * Initializes the UART peripherals to enable transmitting and receiving
 * and redirects stdout and stdin to the UART if NO_UART_STD is not defined.
 * The BAUD rate is set by using setbaud.h.
 */
void uart_init(void);

/**
 * Transmits a single byte and blocks until the transmission is completed.
 *
 * @param data byte to transmit
 */
void uart_transmit(uint8_t data);
/**
 * Transmits the bytes from the given location
 * and blocks until the transmission is completed.
 *
 * @param data location of the bytes to transmit
 * @param len number of bytes to transmit
 */
void uart_transmitBurst(uint8_t *data, size_t len);

/**
 * Blocks until a single byte is received and then returns it.
 *
 * @return the received byte
 */
uint8_t uart_receive(void);
/**
 * Blocks until the given number of bytes are received
 * and writes them to the provided location.
 *
 * @param data location for the received bytes to be written to
 * @param len number of bytes to receive
 */
void uart_receiveBurst(uint8_t *data, size_t len);

#endif
