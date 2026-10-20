/***************************************************************************
 *	    File: UARTLibrary.h
 *           (Needed for Lab07 and Lab08)
 *    Author: Dr. Greg Nordstrom
 *   Created: 12/30/17
 *  Modified: 1/17/21
 * Processor: ATmega128A (on the ReadyAVR board)
 *
 * This header file defines three simple UART (comm port) functions for
 * initializing and using the UART hardware in the ATmega128A processor.
 * Before using the comm port to send/receive data, you must initialize
 * the hardware's baud rate, number of data bits, number of stop bits,
 * and type of parity. Allowable values for these parameters are:
 *
 *       baud rate: 9600, 19200, 38400, or 57600
 *       data bits: 7 or 8
 *       stop bits: 1 or 2
 *     parity type: 0 (none), 1 (odd), or 2 (even)
 *
 * NOTE: UARTLibrary only works with the default USART1 port
 * on the ReadyAVR, so JP2 must have jumpers on PD3 and PD2.
 *
 * Example usage:
 *     #include "UARTLibrary.h"  // Requires libUARTLibrary.a be a part
 *                               // of your project. Place the file in
 *                               // your project directory and add it to
 *                               // the project via Libraries | Add Library
 *                               // in the Solution Explorer panel).
 *
 *     #define BAUDRATE   9600
 *     #define DATABITS   7
 *     #define STOPBITS   2
 *     #define PARITY     2      // 2=even parity
 *
 *     int main(void)
 *     {
 *     	  unsigned char c;
 *
 *     	  // initialize the UART
 *     	  uart_init(BAUDRATE, DATABITS, STOPBITS, PARITY);
 *
 *        // transmit a value (0x41) to the comm port
 *        c = 0x41;
 *        uart_tx(c);
 *
 *        // receive a byte from the comm port
 *        c = uart_rx();
 *     }
 *
 **************************************************************************/ 

#ifndef UARTLIBRARY_H_
#define UARTLIBRARY_H_

// Set default oscillator frequency for ATmega128A (7.3728 MHz)
#define F_OSC 7372800

// function prototypes
void uart_init(long unsigned int baudrate, unsigned char databits, unsigned char stopbits, unsigned char parity);
void uart_tx(unsigned char data);
unsigned char uart_rx(void);

#endif /* UARTLIBRARY_H_ */