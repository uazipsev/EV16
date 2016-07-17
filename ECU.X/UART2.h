/* 
 * File:   UART2.h
 * Author: Igor
 *  Application Expansion: Zac Kilburn
 *
 * Created on March 23, 2015, 11:15 AM
 * Edited on May 31, 2015
 */

#ifndef UART2_H
#define	UART2_H

#ifdef	__cplusplus
extern "C" {
#endif



#define BAUD_SET 115200
#define UART_BUFFER_SIZE 200
#define CLOCK_RATE   36000000
#define BAUD_RATE (((CLOCK_RATE/BAUD_SET)/16)-1)

    extern volatile unsigned int talkTime2;
    void *memset(void *s, int c, size_t n);

    void UART2_init(void);
    unsigned char Receive_peek2(void);
    int Receive_available2(void);
    unsigned char Receive_get2(void);
    void Send_put2(unsigned char _data);


#ifdef	__cplusplus
}
#endif

#endif	/* UART2_H */

