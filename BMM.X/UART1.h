///*
// * File:   UART1.h
// * Author: Igor
// *  Application Expansion: Zac Kilburn
// *
// * Created on March 23, 2015, 11:15 AM
// * Edited on May 31, 2015
// */
//
//#ifndef UART1_HANDLER_H
//#define	UART1_HANDLER_H
//
//#define BAUD_SET 38400
//#define UART_BUFFER_SIZE 200
//#define CLOCK_RATE   36000000
//#define BAUD_RATE (((CLOCK_RATE/BAUD_SET)/16)-1)
//
//void *memset(void *s, int c, size_t n);
//
//struct UART1_ring_buff {
//    unsigned char buf[UART_BUFFER_SIZE];
//    int head;
//    int tail;
//    int count;
//};
//
//struct UART1_ring_buff input_buffer1;
//struct UART1_ring_buff output_buffer1;
//
//bool Transmit_stall1 = true;
//
//void UART1_init(void);
//void UART1_buff_init(struct UART1_ring_buff* _this);
//void UART1_buff_put(struct UART1_ring_buff* _this, const unsigned char c);
//unsigned char UART1_buff_get(struct UART1_ring_buff* _this);
//void UART1_buff_flush(struct UART1_ring_buff* _this, const int clearBuffer);
//int UART1_buff_size(struct UART1_ring_buff* _this);
//unsigned int UART1_buff_modulo_inc(const unsigned int value, const unsigned int modulus);
//unsigned char UART1_buff_peek(struct UART1_ring_buff* _this);
//
//
//unsigned char Receive_peek1(void);
//int Receive_available1(void);
//unsigned char Receive_get1(void);
//void Send_put1(unsigned char _data);
//
//#endif	/* UART_HANDLER_H */
//
