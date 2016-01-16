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


#define BAUD_SET 57600
#define UART_BUFFER_SIZE 200
#define CLOCK_RATE   36000000
#define BAUD_RATE (((CLOCK_RATE/BAUD_SET)/16)-1)
void *memset(void *s, int c, size_t n);

struct UART_ring_buff2 {
    unsigned char buf[UART_BUFFER_SIZE];
    int head;
    int tail;
    int count;
};

struct UART_ring_buff2 input_buffer2;
struct UART_ring_buff2 output_buffer2;

bool Transmit_stall2 = true;

void UART_init2(void);
void UART_buff_init2(struct UART_ring_buff2* _this);
void UART_buff_put2(struct UART_ring_buff2* _this, const unsigned char c);
unsigned char UART_buff_get2(struct UART_ring_buff2* _this);
void UART_buff_flush2(struct UART_ring_buff2* _this, const int clearBuffer);
int UART_buff_size2(struct UART_ring_buff2* _this);
unsigned int UART_buff_modulo_inc2(const unsigned int value, const unsigned int modulus);
unsigned char UART_buff_peek2(struct UART_ring_buff2* _this);


unsigned char Receive_peek2(void);
int Receive_available2(void);
unsigned char Receive_get2(void);
void Send_put2(unsigned char _data);

#endif	/* UART_HANDLER_H */

