/*******************************************************************
 * @brief           Radio.c
 * @brief           Controls radio functions, state system 
 * @return          N/A
 * @note            
 *******************************************************************/
#include <stdbool.h>
#include "UART.h"
#include <xc.h>
#include <string.h>

/**
  Section: EUSART1 APIs
 */

void EUSART1_Initialize(void) {
    // ABDOVF no_overflow; SCKP Non-Inverted; BRG16 16bit_generator; WUE disabled; ABDEN disabled; 
    BAUDCON = 0x08;

    // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RCSTA = 0x90;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave; 
    TXSTA = 0x24;

    // Baud Rate = 9600; SPBRGL 103; 
    SPBRGL = 0x67;

    // Baud Rate = 9600; SPBRGH 0; 
    SPBRGH = 0x00;
}

char EUSART_Read(void)
{

    while(!PIR1bits.RCIF)
    {
    }

    if(1 == RCSTAbits.OERR)
    {
        // EUSART error - restart

        RCSTAbits.CREN = 0; 
        RCSTAbits.CREN = 1; 
    }

    return RCREG;
}

void EUSART_Write(char txData)
{
    while(0 == PIR1bits.TXIF)
    {
    }

    TXREG = txData;    // Write the data byte to the USART.
}

char getch(void)
{
    return EUSART_Read();
}

void putch(char txData)
{
    EUSART_Write(txData);
}