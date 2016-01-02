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

    struct UART2_ring_buff {
        unsigned char buf[UART_BUFFER_SIZE];
        int head;
        int tail;
        int count;
    };

    struct UART2_ring_buff input_buffer2;
    struct UART2_ring_buff output_buffer2;

    volatile bool Transmit_stall2 = true;

    void UART2_init(void);

    unsigned char Receive_peek2(void);
    int Receive_available2(void);
    unsigned char Receive_get2(void);
    void Send_put2(unsigned char _data);

    void UART2_buff_init(struct UART2_ring_buff* _this);
    void UART2_buff_put(struct UART2_ring_buff* _this, const unsigned char c);
    unsigned char UART2_buff_get(struct UART2_ring_buff* _this);
    void UART2_buff_flush(struct UART2_ring_buff* _this, const int clearBuffer);
    int UART2_buff_size(struct UART2_ring_buff* _this);
    unsigned int UART2_buff_modulo_inc(const unsigned int value, const unsigned int modulus);
    unsigned char UART2_buff_peek(struct UART2_ring_buff* _this);





#ifdef	__cplusplus
}
#endif

#endif	/* UART2_H */

