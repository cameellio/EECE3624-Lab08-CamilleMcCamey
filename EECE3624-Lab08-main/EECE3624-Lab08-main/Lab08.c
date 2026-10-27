/*****************************************************************************
 *      File: Lab08.c
 *  Lab Name: RS232 Communication Server
 *    Author: Camille McCamey
 *
 * Processor: ATmega128A (ReadyAVR Board)
 *
 * This program implements a communication server.
 *  1. ESC redisplays the startup screen.
 *  2. Typing "end" displays "Bye" and halts.
 *****************************************************************************/

#define F_CPU 7372800UL

#define CR   0x0D
#define LF   0x0A
#define ESC  0x1B

#include <avr/io.h>
#include <util/delay.h>
#include "UARTLibrary.h"

#define BAUDRATE 9600
#define DATABITS 8
#define STOPBITS 1
#define PARITY   0

// Function Prototypes
void printString(const char *str);
void startupScreen(void);

int main(void)
{
    unsigned char c;
    unsigned char count = 0;

    // Configure LED0 (PB0) as output
    DDRB |= (1 << PB0);
    PORTB &= ~(1 << PB0);

    // Initialize UART
    uart_init(BAUDRATE, DATABITS, STOPBITS, PARITY);

    // Display startup message
    startupScreen();

    while (1)
    {
        c = uart_rx();

        PORTB |= (1 << PB0);
        _delay_ms(75);
        PORTB &= ~(1 << PB0);

        uart_tx(c);

        if (c == CR)
        {
            uart_tx(LF);
        }

        if (c == ESC)
        {
            startupScreen();
            count = 0;
            continue;
        }

        // look for end
        switch (count)
        {
            case 0:
                if (c == 'e')
                    count = 1;
                else
                    count = 0;
                break;

            case 1:
                if (c == 'n')
                    count = 2;
                else if (c == 'e')
                    count = 1;
                else
                    count = 0;
                break;

            case 2:
                if (c == 'd')
                    count = 3;
                else if (c == 'e')
                    count = 1;
                else
                    count = 0;
                break;
        }

        // If "end"
        if (count == 3)
        {
            uart_tx(CR);
            uart_tx(LF);

            printString("Bye");

            while (1)
            { //stop
            }
        }
    }

    return 0;
}

void printString(const char *str)
{
    while (*str != '\0')
    {
        uart_tx(*str);
        str++;
    }
}

void startupScreen(void)
{
    uart_tx(CR);
    uart_tx(LF);

    printString("RS232 Communications Server");
    uart_tx(CR);
    uart_tx(LF);

    printString("Status: Active");
    uart_tx(CR);
    uart_tx(LF);

    printString("Julia Camille McCamey");
    uart_tx(CR);
    uart_tx(LF);

    printString("EECE3624");
    uart_tx(CR);
    uart_tx(LF);

    printString("Fall 2026");
    uart_tx(CR);
    uart_tx(LF);

    uart_tx(CR);
    uart_tx(LF);
}