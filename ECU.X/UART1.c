/*
 * File:   UART1.c
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015
 */

#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "UART1.h"
#include "PinDef.h"
#define ON         0
#define OFF        1

void UART1_init(void) {
    // UART config
    U2MODEbits.STSEL = 0; // 1-stop bit
    U2MODEbits.PDSEL = 0; // No parity, 8-data bits
    U2MODEbits.ABAUD = 0; // Auto-baud disabled
    U2BRG = BAUD_RATE; // Baud Rate setting for 57600
    U2STAbits.URXISEL = 0b01; // Interrupt after all TX character transmitted
    U2STAbits.URXISEL = 0b00; // Interrupt after one RX character is received
    IFS1bits.U2RXIF = 0; // Clear RX interrupt flag
    IFS1bits.U2TXIF = 0; // Clear TX interrupt flag
    IEC1bits.U2RXIE = 1; // Enable RX interrupt
    IEC1bits.U2TXIE = 1; // Enable TX interrupt

    UART1_buff_init(&input_buffer1);
    UART1_buff_init(&output_buffer1);
    U2MODEbits.UARTEN = 1; // Enable UART
    U2STAbits.UTXEN = 1; // Enable UART TX
}

void UART1_buff_init(struct UART1_ring_buff* _this) {
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

void UART1_buff_put(struct UART1_ring_buff* _this, const unsigned char c) {
    if (_this->count < UART_BUFFER_SIZE) {
        _this->buf[_this->head] = c;
        _this->head = UART1_buff_modulo_inc(_this->head, UART_BUFFER_SIZE);
        ++_this->count;
    } else {
        _this->buf[_this->head] = c;
        _this->head = UART1_buff_modulo_inc(_this->head, UART_BUFFER_SIZE);
        _this->tail = UART1_buff_modulo_inc(_this->tail, UART_BUFFER_SIZE);

    }
}

unsigned char UART1_buff_get(struct UART1_ring_buff* _this) {
    unsigned char c;
    if (_this->count > 0) {
        c = _this->buf[_this->tail];
        _this->tail = UART1_buff_modulo_inc(_this->tail, UART_BUFFER_SIZE);
        --_this->count;
    } else {
        c = 0;
    }
    return (c);
}

void UART1_buff_flush(struct UART1_ring_buff* _this, const int clearBuffer) {
    _this->count = 0;
    _this->head = 0;
    _this->tail = 0;
    if (clearBuffer) {
        memset(_this->buf, 0, sizeof (_this->buf));
    }
}

int UART1_buff_size(struct UART1_ring_buff* _this) {
    return (_this->count);
}

unsigned int UART1_buff_modulo_inc(const unsigned int value, const unsigned int modulus) {
    unsigned int my_value = value + 1;
    if (my_value >= modulus) {
        my_value = 0;
    }
    return (my_value);
}

unsigned char UART1_buff_peek(struct UART1_ring_buff* _this) {
    return _this->buf[_this->tail];
}

unsigned char Receive_peek1(void) {
    return UART1_buff_peek(&input_buffer1);
}

int Receive_available1(void) {
    return UART1_buff_size(&input_buffer1);
}

unsigned char Receive_get1(void) {
    return UART1_buff_get(&input_buffer1);
}

void Send_put1(unsigned char _data) {
    UART1_buff_put(&output_buffer1, _data);
    if (Transmit_stall1 == true) {
        Transmit_stall1 = false;
        U2TXREG = UART1_buff_get(&output_buffer1);
    }
}

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void) {
    if (U2STAbits.OERR) {
        U2STAbits.OERR = 0;
    }
    unsigned char data = U2RXREG;
    UART1_buff_put(&input_buffer1, data);
    IFS1bits.U2RXIF = 0; // Clear RX interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void) {

    if (UART1_buff_size(&output_buffer1) > 0) {
        U2TXREG = UART1_buff_get(&output_buffer1);
    } else {
        Transmit_stall1 = true;
        talkTime1 = 0;
    }
    IFS1bits.U2TXIF = 0; // Clear TX interrupt flag
}