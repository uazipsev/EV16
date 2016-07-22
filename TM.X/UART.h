/* 
 * File:   UART.h
 * Author: Igor
 *  Application Expansion: Zac Kilburn
 *
 * Created on March 23, 2015, 11:15 AM
 * Edited on May 31, 2015
 */

#ifndef UART_HANDLER_H
#define	UART_HANDLER_H

#define BAUD_SET 9600
#define UART_BUFFER_SIZE 200
#define CLOCK_RATE   36000000
#define BAUD_RATE (((CLOCK_RATE/BAUD_SET)/16)-1)


void *memset(void *s, int c, size_t n);

void UART_init(void);

unsigned char Receive_peek(void);
int Receive_available(void);
unsigned char Receive_get(void);
void Send_put(unsigned char _data);

#endif	/* UART_HANDLER_H */

