
#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "UART1.h"
#include "PinDef.h"
#include <libpic30.h> 
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
    //IEC1bits.U2RXIE = 1; // Enable RX interrupt
    //IEC1bits.U2TXIE = 1; // Enable TX interrupt
    U2MODEbits.UARTEN = 1; // Enable UART
    U2STAbits.UTXEN = 1; // Enable UART TX
    
    __C30_UART = 2; 
}