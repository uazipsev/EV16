/**
  EUSART1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart1.c

  @Summary
    This is the generated driver implementation file for the EUSART1 driver using MPLAB® Code Configurator

  @Description
    This header file provides implementations for driver APIs for EUSART1.
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

/**
  Section: Included Files
 */
#include "eusart1.h"

/**
  Section: Macro Declarations
 */
#define EUSART1_TX_BUFFER_SIZE 8
#define EUSART1_RX_BUFFER_SIZE 8

/**
  Section: Global Variables
 */

static uint8_t eusart1TxHead = 0;
static uint8_t eusart1TxTail = 0;
static uint8_t eusart1TxBuffer[EUSART1_TX_BUFFER_SIZE];
volatile uint8_t eusart1TxBufferRemaining;

static uint8_t eusart1RxHead = 0;
static uint8_t eusart1RxTail = 0;
static uint8_t eusart1RxBuffer[EUSART1_RX_BUFFER_SIZE];
volatile uint8_t eusart1RxCount;

/**
  Section: EUSART1 APIs
 */

void EUSART1_Initialize(void) {
    // disable interrupts before changing states
    PIE1bits.RC1IE = 0;
    PIE1bits.TX1IE = 0;

    // Set the EUSART1 module to the options selected in the user interface.

    // ABDEN disabled; WUE disabled; RCIDL idle; ABDOVF no_overflow; CKTXP async_noninverted_sync_fallingedge; BRG16 16bit_generator; DTRXP not_inverted;
    BAUD1CON = 0x48;

    // ADDEN enabled; RX9 8-bit; RX9D 0x0; FERR no_error; CREN enabled; SPEN enabled; SREN disabled; OERR no_error;
    RC1STA = 0x98;

    // CSRC slave_mode; TRMT TSR_empty; TXEN enabled; BRGH hi_speed; SYNC asynchronous; SENDB sync_break_complete; TX9D 0x0; TX9 8-bit;
    TX1STA = 0x26;

    // Baud Rate = 57600; SPBRGL 34(0x22); @38400 ~ 68
    SPBRG1 = BAUD_RATE;

    // Baud Rate = 57600; SPBRGH 0;
    SPBRGH1 = 0x00;

    // TXREG 0;
    TXREG1 = 0x00;

    // RCREG 0;
    RCREG1 = 0x00;

    UART_buff_init(&input_buffer);
    UART_buff_init(&output_buffer);
    // enable receive interrupt
    PIE1bits.RC1IE = 1;
    //PIE1bits.TX1IE = 1;
}

void UART_buff_init(struct UART_ring_buff* _this) {
    /*****
      The following clears:
        -> buf
        -> head
        -> tail
        -> count
      and sets head = tail
     ***/
    memset(_this, 0, sizeof (*_this));
}

void UART_buff_put(struct UART_ring_buff* _this, const unsigned char c) {
    if (_this->count < UART_BUFFER_SIZE) {
        _this->buf[_this->head] = c;
        _this->head = UART_buff_modulo_inc(_this->head, UART_BUFFER_SIZE);
        ++_this->count;
    } else {
        _this->buf[_this->head] = c;
        _this->head = UART_buff_modulo_inc(_this->head, UART_BUFFER_SIZE);
        _this->tail = UART_buff_modulo_inc(_this->tail, UART_BUFFER_SIZE);

    }
}

unsigned char UART_buff_get(struct UART_ring_buff* _this) {
    unsigned char c;
    if (_this->count > 0) {
        c = _this->buf[_this->tail];
        _this->tail = UART_buff_modulo_inc(_this->tail, UART_BUFFER_SIZE);
        --_this->count;
    } else {
        c = 0;
    }
    return (c);
}

void UART_buff_flush(struct UART_ring_buff* _this, const int clearBuffer) {
    _this->count = 0;
    _this->head = 0;
    _this->tail = 0;
    if (clearBuffer) {
        memset(_this->buf, 0, sizeof (_this->buf));
    }
}

int UART_buff_size(struct UART_ring_buff* _this) {
    return (_this->count);
}

unsigned int UART_buff_modulo_inc(const unsigned int value, const unsigned int modulus) {
    unsigned int my_value = value + 1;
    if (my_value >= modulus) {
        my_value = 0;
    }
    return (my_value);
}

unsigned char UART_buff_peek(struct UART_ring_buff* _this) {
    return _this->buf[_this->tail];
}

unsigned char Receive_peek(void) {
    return UART_buff_peek(&input_buffer);
}

int Receive_available(void) {
    return UART_buff_size(&input_buffer);
}

unsigned char Receive_get(void) {
    return UART_buff_get(&input_buffer);
}

void Send_put(unsigned char _data) {
    UART_buff_put(&output_buffer, _data);
    if (Transmit_stall == 1) {
        Transmit_stall = 0;
        TXREG1 = UART_buff_get(&output_buffer);
        PIE1bits.TX1IE = 1;
    }
}

char getch(void) {
    return Receive_get();
}

void putch(char txData) {
    Send_put(txData);
}

void EUSART1_Receive_ISR(void) {
    if (1 == RC1STAbits.OERR) {
        // EUSART1 error - restart

        RC1STAbits.CREN = 0;
        RC1STAbits.CREN = 1;
    }
    unsigned char data = RCREG1;
    UART_buff_put(&input_buffer, data);
}

void EUSART1_Transmit_ISR(void) {
    //LED ^= 1;
    if (UART_buff_size(&output_buffer) > 0) {
        TXREG1 = UART_buff_get(&output_buffer);
    } else {
        Transmit_stall = 1;
        PIE1bits.TX1IE = 0;
    }
}