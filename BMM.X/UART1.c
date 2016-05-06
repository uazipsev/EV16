
#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "UART1.h"
#include "PinDef.h"
#include <libpic30.h> 
#include <stdio.h>
#define ON         0
#define OFF        1

void *memset(void *s, int c, size_t n);

struct UART1_ring_buff {
    unsigned char buf[UART_BUFFER_SIZE];
    int head;
    int tail;
    int count;
};

struct UART1_ring_buff input_buffer1;
struct UART1_ring_buff output_buffer1;

bool Transmit_stall1 = true;

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
    IEC1bits.U2RXIE = 0; // Enable RX interrupt
    IEC1bits.U2TXIE = 0; // Enable TX interrupt
    U2MODEbits.UARTEN = 1; // Enable UART
    U2STAbits.UTXEN = 1; // Enable UART TX

    __C30_UART=2;
}

//void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void) {
//    if (U2STAbits.OERR) {
//        U2STAbits.OERR = 0;
//    }
//    if (U2STAbits.FERR) {
//        U2RXREG;
//        IFS1bits.U2RXIF = 0; // Clear RX interrupt flag    
//        return;
//    }
//    if (U2STAbits.PERR) {
//        U2RXREG;
//        IFS1bits.U2RXIF = 0; // Clear RX interrupt flag
//        return;
//    }
//    if(U2STAbits.URXDA){
//    unsigned char data = U2RXREG;
//    UART1_buff_put(&input_buffer1, data);
//    }
//    IFS1bits.U2RXIF = 0; // Clear RX interrupt flag    
//}
//
//void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void) {
//    //LED ^= 1;
//    if (UART1_buff_size(&output_buffer1) > 0) {
//        U2TXREG = UART1_buff_get(&output_buffer1);
//    } else {
//        Transmit_stall1 = true;
//    }
//    IFS1bits.U2TXIF = 0; // Clear TX interrupt flag
//}