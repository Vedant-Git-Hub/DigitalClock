#include <avr/io.h>     //hardware registers
#include <stdbool.h>    //bool type
#include "uart.h"



#include <util/setbaud.h>   //BAUD registers calculations



/** Stream function wrapper. */
static int uart_putc(char c, FILE *stream)
{
    (void)stream;   //suppress unused warning
    uart_transmit(c);
    return 0;
}
/** Stream function wrapper. */
static int uart_getc(FILE *stream)
{
    (void)stream;   //suppress unused warning
    return uart_receive();
}

//stream setups
//https://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html
FILE uart_out = FDEV_SETUP_STREAM(uart_putc, NULL, _FDEV_SETUP_WRITE);
FILE uart_in = FDEV_SETUP_STREAM(NULL, uart_getc, _FDEV_SETUP_READ);



void uart_init(void)
{
    //setbaud.h values
    //https://www.nongnu.org/avr-libc/user-manual/group__util__setbaud.html
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

    #if USE_2X
        UCSR0A |= (1 << U2X0);
    #endif

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);


    //redirect by default
    #ifndef NO_UART_STD
        stdout = &uart_out;
        stdin = &uart_in;
    #endif
}



/**
 * Returns true if a byte has been received and is ready to be read.
 * Will be reset when the data register UDR0 is read.
 *
 * @return if a byte has been received and is ready to be read
 */
static bool uart_isReceiveComplete(void)
{
    return UCSR0A & (1 << RXC0);
}

/**
 * Returns true when a transmission is completed.
 *
 * @returns if a transmission is completed
 */
static bool uart_isTransmitComplete(void)
{
    return UCSR0A & (1 << TXC0);
}

/**
 * Returns true when the data register UDR0 is empty
 * and new data can be written into it.
 *
 * @returns if the data register UDR0 is empty
 */
static bool uart_isDataEmpty(void)
{
    return UCSR0A & (1 << UDRE0);
}



void uart_transmit(uint8_t data)
{
    while(!uart_isDataEmpty())
        ;

    UDR0 = data;

    //wait for completed transmission so the user can be sure
    //that the byte is completely clocked out
    //and hopefully has been received by someone
    while(!uart_isTransmitComplete())
        ;
}

void uart_transmitBurst(uint8_t *data, size_t len)
{
    while(len--)
    {
        while(!uart_isDataEmpty())
            ;

        UDR0 = *data++;
    }

    while(!uart_isTransmitComplete())
        ;
}


uint8_t uart_receive(void)
{
    while(!uart_isReceiveComplete())
        ;

    return UDR0;
}

void uart_receiveBurst(uint8_t *data, size_t len)
{
    while(len--)
        *data++ = uart_receive();
}
