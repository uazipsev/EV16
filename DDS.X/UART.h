/* 
 * File:   UART.h
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015, 8:07 PM
 *
 * Provides support interface for FastTransfer communications system
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
    uint8_t EUSART1_Read(void);

    /**
     @Summary
       Writes a byte of data to the EUSART1.

     @Description
       This routine writes a byte of data to the EUSART1.

     @Preconditions
       EUSART1_Initialize() function should have been called
       before calling this function. The transfer status should be checked to see
       if transmitter is not busy before calling this function.

     @Param
       txData  - Data byte to write to the EUSART1

     @Returns
       None

     @Example
         <code>
             Refer to EUSART1_Read() for an example
         </code>
     */
    void EUSART1_Write(uint8_t txData);

    /**
      @Summary
        Maintains the driver's transmitter state machine and implements its ISR.

      @Description
        This routine is used to maintain the driver's internal transmitter state
        machine.This interrupt service routine is called when the state of the
        transmitter needs to be maintained in a non polled manner.

      @Preconditions
        EUSART1_Initialize() function should have been called
        for the ISR to execute correctly.

      @Param
        None

      @Returns
        None
     */
    void EUSART1_Transmit_ISR(void);

    /**
      @Summary
        Maintains the driver's receiver state machine and implements its ISR

      @Description
        This routine is used to maintain the driver's internal receiver state
        machine.This interrupt service routine is called when the state of the
        receiver needs to be maintained in a non polled manner.

      @Preconditions
        EUSART1_Initialize() function should have been called
        for the ISR to execute correctly.

      @Param
        None

      @Returns
        None
     */
    void EUSART1_Receive_ISR(void);

    char getch(void);
    void putch(char txData);
#define BAUD_SET 38400
#define UART_BUFFER_SIZE 200
#define CLOCK_RATE   16000000
#define BAUD_RATE (((CLOCK_RATE/BAUD_SET)/4)-1)

    extern volatile unsigned int talkTime;
    void *memset(void *s, int c, size_t n);

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
    unsigned char UART_buff_peek(struct UART_ring_buff* _this);


    unsigned char Receive_peek(void);
    int Receive_available(void);
    unsigned char Receive_get(void);
    void Send_put(unsigned char _data);



#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

