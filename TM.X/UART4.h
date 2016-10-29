/* 
 * File:   UART4.h
 * Author: Rick
 *
 * Created on August 20, 2016, 11:48 PM
 */

#ifndef UART4_H
#define	UART4_H

#define BAUD_SET 9600
#define UART_BUFFER_SIZE 1000
#define CLOCK_RATE   36000000
#define BAUD_RATE (((CLOCK_RATE/BAUD_SET)/16)-1)

//void *memset(void *s, int c, size_t n);

void UART4_init(void);

unsigned char Receive_peek4(void);
int Receive_available4(void);
unsigned char Receive_get4(void);
void Send_put4(unsigned char _data);
void UART4_Clear();

#endif	/* UART4_H */

