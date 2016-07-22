/*
 * File:   UART.c
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015
 */

#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "UART2.h"
#include "PinDef.h"
#define ON         0
#define OFF        1

void UART2_init(void) {
    // UART config
    U2MODEbits.STSEL = 0; // 1-stop bit
    U2MODEbits.PDSEL = 0; // No parity, 8-data bits
    U2MODEbits.ABAUD = 0; // Auto-baud disabled
    U2BRG = BAUD_RATE; // Baud Rate setting for 57600
    U2STAbits.URXISEL = 0b01; // Interrupt after all TX character transmitted
    U2STAbits.URXISEL = 0b00; // Interrupt after one RX character is received
    //IFS0bits.U1RXIF = 0; // Clear RX interrupt flag
    //IFS0bits.U1TXIF = 0; // Clear TX interrupt flag
    //IEC0bits.U1RXIE = 1; // Enable RX interrupt
    //IEC0bits.U1TXIE = 1; // Enable TX interrupt

    UART_buff_init2(&input_buffer);
    UART_buff_init2(&output_buffer);
    U2MODEbits.UARTEN = 1; // Enable UART
    U2STAbits.UTXEN = 1; // Enable UART TX
}

void UART2_buff_init(struct UART_ring_buff* _this) {
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

void UART2_buff_put(struct UART_ring_buff* _this, const unsigned char c) {
    if (_this->count < UART_BUFFER_SIZE) {
        _this->buf[_this->head] = c;
        _this->head = UART2_buff_modulo_inc(_this->head, UART_BUFFER_SIZE);
        ++_this->count;
    } else {
        _this->buf[_this->head] = c;
        _this->head = UART2_buff_modulo_inc(_this->head, UART_BUFFER_SIZE);
        _this->tail = UART2_buff_modulo_inc(_this->tail, UART_BUFFER_SIZE);

    }
}

unsigned char UART2_buff_get(struct UART_ring_buff* _this) {
    unsigned char c;
    if (_this->count > 0) {
        c = _this->buf[_this->tail];
        _this->tail = UART2_buff_modulo_inc(_this->tail, UART_BUFFER_SIZE);
        --_this->count;
    } else {
        c = 0;
    }
    return (c);
}

void UART2_buff_flush(struct UART_ring_buff* _this, const int clearBuffer) {
    _this->count = 0;
    _this->head = 0;
    _this->tail = 0;
    if (clearBuffer) {
        memset(_this->buf, 0, sizeof (_this->buf));
    }
}

int UART2_buff_size(struct UART_ring_buff* _this) {
    return (_this->count);
}

unsigned int UART2_buff_modulo_inc(const unsigned int value, const unsigned int modulus) {
    unsigned int my_value = value + 1;
    if (my_value >= modulus) {
        my_value = 0;
    }
    return (my_value);
}

unsigned char UART2_buff_peek(struct UART_ring_buff* _this) {
    return _this->buf[_this->tail];
}

unsigned char Receive_peek2(void) {
    return UART2_buff_peek(&input_buffer);
}

int Receive_available2(void) {
    return UART2_buff_size(&input_buffer);
}

unsigned char Receive_get2(void) {
    return UART2_buff_get(&input_buffer);
}

void Send_put2(unsigned char _data) {
    UART2_buff_put(&output_buffer, _data);
    if (Transmit_stall == true) {
        Transmit_stall = false;
        U1TXREG = UART_buff_get(&output_buffer);
    }
}

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void) {
    if (U2STAbits.OERR) {
        U2STAbits.OERR = 0;
    }
    unsigned char data = U2RXREG;
    UART2_buff_put(&input_buffer, data);
    IFS0bits.U1RXIF = 0; // Clear RX interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void) {
    //LED ^= 1;
    if (UART2_buff_size(&output_buffer) > 0) {
        U2TXREG = UART2_buff_get(&output_buffer);
    } else {

        //talkTime = 0;
        Transmit_stall = true;
    }
    IFS0bits.U1TXIF = 0; // Clear TX interrupt flag
}