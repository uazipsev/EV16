/**
  EUSART1 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart1.h

  @Summary
    This is the generated header file for the EUSART1 driver using MPLAB® Code Configurator

  @Description
    This header file provides APIs for driver for EUSART1.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC18F45K22
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#ifndef _EUSART1_H
#define _EUSART1_H

/**
  Section: Included Files
 */

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


    /**
      Section: Macro Declarations
     */

#define EUSART1_DataReady  (eusart1RxCount)

    /**
      Section: Data Type Definitions
     */

    /**
     Section: Global variables
     */
    extern volatile uint8_t eusart1TxBufferRemaining;
    extern volatile uint8_t eusart1RxCount;


    /**
      Section: EUSART1 APIs
     */

    /**
      @Summary
        Initialization routine that takes inputs from the EUSART1 GUI.

      @Description
        This routine initializes the EUSART1 driver.
        This routine must be called before any other EUSART1 routine is called.

      @Preconditions
        None

      @Param
        None

      @Returns
        None

      @Comment

      @Example
     */
    void EUSART1_Initialize(void);

    /**
      @Summary
        Read a byte of data from the EUSART1.

      @Description
        This routine reads a byte of data from the EUSART1.

      @Preconditions
        EUSART1_Initialize() function should have been called
        before calling this function. The transfer status should be checked to see
        if the receiver is not empty before calling this function.
	
        EUSART1_DataReady is a macro which checks if any byte is received.
        Call this macro before using this function.

      @Param
        None

      @Returns
        A data byte received by the driver.
	
      @Example
        <code>
                void main(void) {
                                    // initialize the device
                                    SYSTEM_Initialize();
                                    uint8_t data;
								
                                    // Enable the Global Interrupts
                                    INTERRUPT_GlobalInterruptEnable();
								
                                    // Enable the Peripheral Interrupts
                                    INTERRUPT_PeripheralInterruptEnable();
								
                                    printf("\t\tTEST CODE\n\r");		//Enable redirect STDIO to USART before using printf statements
                                    printf("\t\t---- ----\n\r");
                                    printf("\t\tECHO TEST\n\r");
                                    printf("\t\t---- ----\n\n\r");
                                    printf("Enter any string: ");
                                    do{
                                    data = EUSART1_Read();		// Read data received
                                    EUSART_Write(data);			// Echo back the data received
                                    }while(!EUSART1_DataReady);		//check if any data is received
								
                                }
        </code>
     */
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

#endif  // _EUSART1_H
/**
 End of File
 */
