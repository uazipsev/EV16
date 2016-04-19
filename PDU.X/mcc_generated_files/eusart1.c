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
        Product Revision  :  MPLAB® Code Configurator - v2.25
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
#define EUSART1_RX_BUFFER_SIZE 32

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

void EUSART1_Initialize(void)
{
    // disable interrupts before changing states
    PIE1bits.RC1IE = 0;
    PIE1bits.TX1IE = 0;

    // Set the EUSART1 module to the options selected in the user interface.

    // ABDEN disabled; WUE disabled; RCIDL idle; ABDOVF no_overflow; CKTXP async_noninverted_sync_fallingedge; BRG16 16bit_generator; DTRXP not_inverted; 
    BAUD1CON = 0x48;

    // ADDEN disabled; RX9 8-bit; RX9D 0x0; FERR no_error; CREN enabled; SPEN enabled; SREN disabled; OERR no_error; 
    RC1STA = 0x90;

    // CSRC slave_mode; TRMT TSR_empty; TXEN enabled; BRGH hi_speed; SYNC asynchronous; SENDB sync_break_complete; TX9D 0x0; TX9 8-bit; 
    TX1STA = 0x26;

    // Baud Rate = 57600; SPBRGL 34; 
    SPBRG1 = 0x22;

    // Baud Rate = 57600; SPBRGH 0; 
    SPBRGH1 = 0x00;

    // TXREG 0; 
    TXREG1 = 0x00;

    // RCREG 0; 
    RCREG1 = 0x00;


    // initializing the driver state
    eusart1TxHead = 0;
    eusart1TxTail = 0;
    eusart1TxBufferRemaining = sizeof(eusart1TxBuffer);

    eusart1RxHead = 0;
    eusart1RxTail = 0;
    eusart1RxCount = 0;

    // enable receive interrupt
    PIE1bits.RC1IE = 1;
}

uint8_t EUSART1_Read(void)
{
    uint8_t readValue  = 0;

    while(0 == eusart1RxCount)
    {
    }

    PIE1bits.RC1IE = 0;

    readValue = eusart1RxBuffer[eusart1RxTail++];
    if(sizeof(eusart1RxBuffer) <= eusart1RxTail)
    {
        eusart1RxTail = 0;
    }
    eusart1RxCount--;
    PIE1bits.RC1IE = 1;

    return readValue;
}

void EUSART1_Write(uint8_t txData)
{
    while(0 == eusart1TxBufferRemaining)
    {
    }

    if(0 == PIE1bits.TX1IE)
    {
        TXREG1 = txData;
    }
    else
    {
        PIE1bits.TX1IE = 0;
        eusart1TxBuffer[eusart1TxHead++] = txData;
        if(sizeof(eusart1TxBuffer) <= eusart1TxHead)
        {
            eusart1TxHead = 0;
        }
        eusart1TxBufferRemaining--;
    }
    PIE1bits.TX1IE = 1;
}

char getch(void)
{
    return EUSART1_Read();
}

void putch(char txData)
{
    EUSART1_Write(txData);
}

void EUSART1_Transmit_ISR(void)
{

    // add your EUSART1 interrupt custom code
    if(sizeof(eusart1TxBuffer) > eusart1TxBufferRemaining)
    {
        TXREG1 = eusart1TxBuffer[eusart1TxTail++];
        if(sizeof(eusart1TxBuffer) <= eusart1TxTail)
        {
            eusart1TxTail = 0;
        }
        eusart1TxBufferRemaining++;
    }
    else
    {
        PIE1bits.TX1IE = 0;
    }
}

void EUSART1_Receive_ISR(void)
{
    if(1 == RC1STAbits.OERR)
    {
        // EUSART1 error - restart

        RC1STAbits.CREN = 0;
        RC1STAbits.CREN = 1;
    }

    // buffer overruns are ignored
    eusart1RxBuffer[eusart1RxHead++] = RCREG1;
    if(sizeof(eusart1RxBuffer) <= eusart1RxHead)
    {
        eusart1RxHead = 0;
    }
    eusart1RxCount++;
}
/**
  End of File
*/
