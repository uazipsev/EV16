#include "UART4.h"
#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "PinDef.h"
#include <string.h>
#include <stdio.h>

struct UART4_ring_buff {
    unsigned char buf[UART_BUFFER_SIZE];
    int head;
    int tail;
    int count;
};

struct UART4_ring_buff input_buffer4;
struct UART4_ring_buff output_buffer4;

volatile bool Transmit_stall4 = true;

void UART4_buff_init(struct UART4_ring_buff* _this);
void UART4_buff_put(struct UART4_ring_buff* _this, const unsigned char c);
unsigned char UART4_buff_get(struct UART4_ring_buff* _this);
void UART4_buff_flush(struct UART4_ring_buff* _this, const int clearBuffer);
int UART4_buff_size(struct UART4_ring_buff* _this);
unsigned int UART4_buff_modulo_inc(const unsigned int value, const unsigned int modulus);
unsigned char UART4_buff_peek(struct UART4_ring_buff* _this);

void UART4_init(void) {
    // UART config
    U4MODEbits.STSEL = 0; // 1-stop bit
    U4MODEbits.PDSEL = 0; // No parity, 8-data bits
    U4MODEbits.ABAUD = 0; // Auto-baud disabled
    U4BRG = BAUD_RATE; // Baud Rate setting for 57600
    U4STAbits.UTXISEL0 = 1; // Interrupt after all TX character transmitted
    U4STAbits.UTXISEL1 = 0; // Interrupt after all TX character transmitted
    U4STAbits.URXISEL = 0b00; // Interrupt after one RX character is received
    IFS5bits.U4RXIF = 0; // Clear RX interrupt flag
    IFS5bits.U4TXIF = 0; // Clear TX interrupt flag
    IEC5bits.U4RXIE = 1; // Enable RX interrupt


    UART4_buff_init(&input_buffer4);
    UART4_buff_init(&output_buffer4);
    U4MODEbits.UARTEN = 1; // Enable UART
    U4STAbits.UTXEN = 1; // Enable UART TX
}

void UART4_Clear(){
    UART4_buff_flush(&input_buffer4,0);
}

void UART4_buff_init(struct UART4_ring_buff* _this) {
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

void UART4_buff_put(struct UART4_ring_buff* _this, const unsigned char c) {
    if (_this->count < UART_BUFFER_SIZE) {
        _this->buf[_this->head] = c;
        _this->head = UART4_buff_modulo_inc(_this->head, UART_BUFFER_SIZE);
        ++_this->count;
    } else {
        _this->buf[_this->head] = c;
        _this->head = UART4_buff_modulo_inc(_this->head, UART_BUFFER_SIZE);
        _this->tail = UART4_buff_modulo_inc(_this->tail, UART_BUFFER_SIZE);

    }
}

unsigned char UART4_buff_get(struct UART4_ring_buff* _this) {
    unsigned char c;
    if (_this->count > 0) {
        c = _this->buf[_this->tail];
        _this->tail = UART4_buff_modulo_inc(_this->tail, UART_BUFFER_SIZE);
        --_this->count;
    } else {
        c = 0;
    }
    return (c);
}

void UART4_buff_flush(struct UART4_ring_buff* _this, const int clearBuffer) {
    _this->count = 0;
    _this->head = 0;
    _this->tail = 0;
    if (clearBuffer) {
        memset(_this->buf, 0, sizeof (_this->buf));
    }
}

int UART4_buff_size(struct UART4_ring_buff* _this) {
    return (_this->count);
}

unsigned int UART4_buff_modulo_inc(const unsigned int value, const unsigned int modulus) {
    unsigned int my_value = value + 1;
    if (my_value >= modulus) {
        my_value = 0;
    }
    return (my_value);
}

unsigned char UART4_buff_peek(struct UART4_ring_buff* _this) {
    return _this->buf[_this->tail];
}

unsigned char Receive_peek4(void) {
    return UART4_buff_peek(&input_buffer4);
}

int Receive_available4(void) {
    return UART4_buff_size(&input_buffer4);
}

unsigned char Receive_get4(void) {
    return UART4_buff_get(&input_buffer4);
}

void Send_put4(unsigned char _data) {
    UART4_buff_put(&output_buffer4, _data);
    if (Transmit_stall4 == true) {
        Transmit_stall4 = false;
        U4TXREG = UART4_buff_get(&output_buffer4);
        IEC5bits.U4TXIE = 1; // Enable TX interrupt
    }
}

void __attribute__((interrupt, no_auto_psv)) _U4RXInterrupt(void) {
    if (U4STAbits.OERR) {
        U4STAbits.OERR = 0;
    }
    unsigned char data = U4RXREG;
    UART4_buff_put(&input_buffer4, data);
    IFS5bits.U4RXIF = 0; // Clear RX interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _U4TXInterrupt(void) {
    if (UART4_buff_size(&output_buffer4) > 0) {
        U4TXREG = UART4_buff_get(&output_buffer4);
        
    } else {
        IEC5bits.U4TXIE = 0; // Enable TX interrupt
        //talkTime = 0;
        Transmit_stall4 = true;
    }
    
    IFS5bits.U4TXIF = 0; // Clear TX interrupt flag
}