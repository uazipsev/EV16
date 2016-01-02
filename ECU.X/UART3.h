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

#ifdef	__cplusplus
extern "C" {
#endif



#define BAUD_SET 38400
#define UART_BUFFER_SIZE 200
#define CLOCK_RATE   36000000
#define BAUD_RATE (((CLOCK_RATE/BAUD_SET)/16)-1)

    extern volatile unsigned int talkTime3;
    void *memset(void *s, int c, size_t n);

    struct UART3_ring_buff {
        unsigned char buf[UART_BUFFER_SIZE];
        int head;
        int tail;
        int count;
    };

    struct UART3_ring_buff input_buffer3;
    struct UART3_ring_buff output_buffer3;

    volatile bool Transmit_stall3 = true;

    void UART3_init(void);

    unsigned char Receive_peek3(void);
    int Receive_available3(void);
    unsigned char Receive_get3(void);
    void Send_put3(unsigned char _data);

    void UART3_buff_init(struct UART3_ring_buff* _this);
    void UART3_buff_put(struct UART3_ring_buff* _this, const unsigned char c);
    unsigned char UART3_buff_get(struct UART3_ring_buff* _this);
    void UART3_buff_flush(struct UART3_ring_buff* _this, const int clearBuffer);
    int UART3_buff_size(struct UART3_ring_buff* _this);
    unsigned int UART3_buff_modulo_inc(const unsigned int value, const unsigned int modulus);
    unsigned char UART3_buff_peek(struct UART3_ring_buff* _this);





#ifdef	__cplusplus
}
#endif

#endif	/* UART3_H */

