
/*
 * File:   UART3.c
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015
 */

#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "UART3.h"
#include "PinDef.h"

extern volatile unsigned int talkTime3;
void *memset(void *s, int c, size_t n);

struct UART3_ring_buff {
    unsigned char buf[UART3_BUFFER_SIZE];
    int head;
    int tail;
    int count;
};

struct UART3_ring_buff input_buffer3;
struct UART3_ring_buff output_buffer3;

volatile bool Transmit_stall3 = true;

void UART3_buff_init(struct UART3_ring_buff* _this);
void UART3_buff_put(struct UART3_ring_buff* _this, const unsigned char c);
unsigned char UART3_buff_get(struct UART3_ring_buff* _this);
void UART3_buff_flush(struct UART3_ring_buff* _this, const int clearBuffer);
int UART3_buff_size(struct UART3_ring_buff* _this);
unsigned int UART3_buff_modulo_inc(const unsigned int value, const unsigned int modulus);
unsigned char UART3_buff_peek(struct UART3_ring_buff* _this);
    
void UART3_init(void) {
    // UART config
    U4MODEbits.STSEL = 0; // 1-stop bit
    U4MODEbits.PDSEL = 0; // No parity, 8-data bits
    U4MODEbits.ABAUD = 0; // Auto-baud disabled
    U4BRG = UART3_BAUD_RATE; // Baud Rate setting for 57600
    U4STAbits.URXISEL = 0b01; // Interrupt after all TX character transmitted
    U4STAbits.URXISEL = 0b00; // Interrupt after one RX character is received
    IFS5bits.U4RXIF = 0; // Clear RX interrupt flag
    IFS5bits.U4TXIF = 0; // Clear TX interrupt flag
    IEC5bits.U4RXIE = 1; // Enable RX interrupt
    IEC5bits.U4TXIE = 1; // Enable TX interrupt

    UART3_buff_init(&input_buffer3);
    UART3_buff_init(&output_buffer3);
    U4MODEbits.UARTEN = 1; // Enable UART
    U4STAbits.UTXEN = 1; // Enable UART TX
}

void UART3_buff_init(struct UART3_ring_buff* _this) {
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

void UART3_buff_put(struct UART3_ring_buff* _this, const unsigned char c) {
    if (_this->count < UART3_BUFFER_SIZE) {
        _this->buf[_this->head] = c;
        _this->head = UART3_buff_modulo_inc(_this->head, UART3_BUFFER_SIZE);
        ++_this->count;
    } else {
        _this->buf[_this->head] = c;
        _this->head = UART3_buff_modulo_inc(_this->head, UART3_BUFFER_SIZE);
        _this->tail = UART3_buff_modulo_inc(_this->tail, UART3_BUFFER_SIZE);

    }
}

unsigned char UART3_buff_get(struct UART3_ring_buff* _this) {
    unsigned char c;
    if (_this->count > 0) {
        c = _this->buf[_this->tail];
        _this->tail = UART3_buff_modulo_inc(_this->tail, UART3_BUFFER_SIZE);
        --_this->count;
    } else {
        c = 0;
    }
    return (c);
}

void UART3_buff_flush(struct UART3_ring_buff* _this, const int clearBuffer) {
    _this->count = 0;
    _this->head = 0;
    _this->tail = 0;
    if (clearBuffer) {
        memset(_this->buf, 0, sizeof (_this->buf));
    }
}

int UART3_buff_size(struct UART3_ring_buff* _this) {
    return (_this->count);
}

unsigned int UART3_buff_modulo_inc(const unsigned int value, const unsigned int modulus) {
    unsigned int my_value = value + 1;
    if (my_value >= modulus) {
        my_value = 0;
    }
    return (my_value);
}

unsigned char UART3_buff_peek(struct UART3_ring_buff* _this) {
    return _this->buf[_this->tail];
}

unsigned char Receive_peek3(void) {
    return UART3_buff_peek(&input_buffer3);
}

int Receive_available3(void) {
    return UART3_buff_size(&input_buffer3);
}

unsigned char Receive_get3(void) {
    return UART3_buff_get(&input_buffer3);
}

void Send_put3(unsigned char _data) {
    UART3_buff_put(&output_buffer3, _data);
    if (Transmit_stall3 == true) {
        Transmit_stall3 = false;
        U4TXREG = UART3_buff_get(&output_buffer3);
    }
}

void __attribute__((interrupt, no_auto_psv)) _U4RXInterrupt(void) {
    if (U4STAbits.OERR) {
        U4STAbits.OERR = 0;
    }
    unsigned char data = U4RXREG;
    UART3_buff_put(&input_buffer3, data);
    IFS5bits.U4RXIF = 0; // Clear RX interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _U4TXInterrupt(void) {
    //LED ^= 1;
    if (UART3_buff_size(&output_buffer3) > 0) {
        U4TXREG = UART3_buff_get(&output_buffer3);
    } else {
        Transmit_stall3 = true;
    }
    IFS5bits.U4TXIF = 0; // Clear TX interrupt flag
}