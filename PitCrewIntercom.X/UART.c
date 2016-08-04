#include <stdbool.h>
#include "UART.h"
#include <xc.h>
#include <string.h>

/**
  Section: Macro Declarations
 */
#define EUSART1_TX_BUFFER_SIZE 8
#define EUSART1_RX_BUFFER_SIZE 8

/**
  Section: Global Variables
 */

static char eusart1TxHead = 0;
static char eusart1TxTail = 0;
static char eusart1TxBuffer[EUSART1_TX_BUFFER_SIZE];
volatile char eusart1TxBufferRemaining;

static char eusart1RxHead = 0;
static char eusart1RxTail = 0;
static char eusart1RxBuffer[EUSART1_RX_BUFFER_SIZE];
volatile char eusart1RxCount;

/**
  Section: EUSART1 APIs
 */

void EUSART1_Initialize(void) {
    // disable interrupts before changing states
    PIE1bits.RCIE = 0;
    PIE1bits.TXIE = 0;

    SPBRG = 0x25;

    RCSTA = 0b100100000;

    TXSTA = 0b001000000;

    UART_buff_init(&input_buffer);
    UART_buff_init(&output_buffer);
    // enable receive interrupt
    PIE1bits.RCIE = 1;
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
        TXREG = UART_buff_get(&output_buffer);
        PIE1bits.TXIE = 1;
    }
}

char getch(void) {
    return Receive_get();
}

void putch(char txData) {
    Send_put(txData);
}

void EUSART1_Receive_ISR(void) {
    if (1 == RCSTAbits.OERR) {
        // EUSART1 error - restart

        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    unsigned char data = RCREG;
    UART_buff_put(&input_buffer, data);
}

void EUSART1_Transmit_ISR(void) {
    //LED ^= 1;
    if (UART_buff_size(&output_buffer) > 0) {
        TXREG = UART_buff_get(&output_buffer);
    } else {
        Transmit_stall = 1;
        PIE1bits.TXIE = 0;
    }
}