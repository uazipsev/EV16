/*
 * File:   UART1.h
 * Author: Igor
 *  Application Expansion: Zac Kilburn
 *
 * Created on March 23, 2015, 11:15 AM
 * Edited on May 31, 2015
 */

#ifndef UART1_HANDLER_H
#define	UART1_HANDLER_H

#define BAUD_SET 38400
#define UART_BUFFER_SIZE 200
#define CLOCK_RATE   32000000
#define BAUD_RATE (((CLOCK_RATE/BAUD_SET)/16)-1)

void UART1_init(void);


unsigned char Receive_peek2(void);
int Receive_available2(void);
unsigned char Receive_get2(void);
void Send_put2(unsigned char _data);

#endif	/* UART_HANDLER_H */

