/* 
 * File:   UART.h
 * Author: Rick
 *
 * Created on August 3, 2016, 11:38 AM
 */

#ifndef UART_H
#define	UART_H

#include <stdbool.h>
#define BAUD_SET 38400
#define UART_BUFFER_SIZE 20
#define CLOCK_RATE   16000000
#define BAUD_RATE (((CLOCK_RATE/BAUD_SET)/4)-1)

    extern volatile unsigned int talkTime;
    //void *memset(void *s, int c, size_t n);

    struct UART_ring_buff {
        unsigned char buf[UART_BUFFER_SIZE];
        int head;
        int tail;
        int count;
    };

    struct UART_ring_buff input_buffer;
    struct UART_ring_buff output_buffer;

    bool Transmit_stall = true;
    void EUSART1_Initialize(void);
    void UART_buff_init(struct UART_ring_buff* _this);
    void UART_buff_put(struct UART_ring_buff* _this, const unsigned char c);
    unsigned char UART_buff_get(struct UART_ring_buff* _this);
    void UART_buff_flush(struct UART_ring_buff* _this, const int clearBuffer);
    int UART_buff_size(struct UART_ring_buff* _this);
    unsigned int UART_buff_modulo_inc(const unsigned int value, const unsigned int modulus);
    void EUSART1_Receive_ISR();
    void EUSART1_Transmit_ISR(void);
    char getch(void);
    void putch(char txData);
    void Send_put(unsigned char _data);
    unsigned char Receive_get(void);


#endif	/* UART_H */

