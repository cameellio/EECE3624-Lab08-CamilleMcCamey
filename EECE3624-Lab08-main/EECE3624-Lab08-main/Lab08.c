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

    // Configure LED0 (PB0) as an output so the board can visibly blink
    // when data is received. This helps confirm serial activity.
    DDRB |= (1 << PB0);
    PORTB &= ~(1 << PB0);

    // Initialize the UART for serial communication using the required
    // settings: 9600 baud, 8 data bits, 1 stop bit, no parity.
    uart_init(BAUDRATE, DATABITS, STOPBITS, PARITY);

    // Show the startup banner on power-up or after an ESC reset.
    startupScreen();

    while (1)
    {
        // Wait for the next serial character from the terminal.
        c = uart_rx();

        // Blink the LED briefly to show that a byte was received.
        PORTB |= (1 << PB0);
        _delay_ms(75);
        PORTB &= ~(1 << PB0);

        // Echo the received character back to the terminal for interactive use.
        uart_tx(c);

        // If Enter was pressed, also send a line feed so the terminal output
        // appears on the next line correctly.
        if (c == CR)
        {
            uart_tx(LF);
        }

        // ESC acts as a soft reset: redisplay the startup screen and clear the
        // "end" detection state so the user can start over cleanly.
        if (c == ESC)
        {
            startupScreen();
            count = 0;
            continue;
        }

        // Track whether the user is typing the sequence "end".
        // This is a simple state machine: e -> n -> d.
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

        // Once the sequence "end" has been fully received, print a goodbye
        // message and halt the program so the RS232 server stops running.
        if (count == 3)
        {
            uart_tx(CR);
            uart_tx(LF);
            printString("Bye");
            uart_tx(CR);
            uart_tx(LF);

            while (1)
            { // stop execution after the goodbye message
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

    printString("Camille McCamey");
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