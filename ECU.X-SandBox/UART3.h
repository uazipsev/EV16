/* 
 * File:   UART3.h
 * Author: Igor
 *  Application Expansion: Zac Kilburn
 *
 * Created on March 23, 2015, 11:15 AM
 * Edited on May 31, 2015
 */

#ifndef UART3_H
#define	UART3_H

#define UART3_BAUD_SET 38400
#define UART3_BUFFER_SIZE 200
#define CLOCK_RATE   36000000
#define UART3_BAUD_RATE (((CLOCK_RATE/UART3_BAUD_SET)/16)-1)

void UART3_init(void);
unsigned char Receive_peek3(void);
int Receive_available3(void);
unsigned char Receive_get3(void);
void Send_put3(unsigned char _data);


#endif	/* UART3_H */

