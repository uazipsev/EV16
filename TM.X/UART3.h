/* 
 * File:   UART3.h
 * Author: Rick
 *
 * Created on August 20, 2016, 11:47 PM
 */

#ifndef UART3_H
#define	UART3_H

#define BAUD_SET 38400
#define UART_BUFFER_SIZE 200
#define CLOCK_RATE   36000000
#define BAUD_RATE (((CLOCK_RATE/BAUD_SET)/16)-1)

//void *memset(void *s, int c, size_t n);

void UART3_init(void);



unsigned char Receive_peek3(void);
int Receive_available3(void);
unsigned char Receive_get3(void);
void Send_put3(unsigned char _data);

#endif	/* UART3_H */

