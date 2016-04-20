/**
  EUSART2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart2.c

  @Summary
    This is the generated driver implementation file for the EUSART2 driver using MPLAB® Code Configurator

  @Description
    This header file provides implementations for driver APIs for EUSART2.
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
#include "eusart2.h"

/**
  Section: Macro Declarations
 */
#define EUSART2_TX_BUFFER_SIZE 8
#define EUSART2_RX_BUFFER_SIZE 8

/**
  Section: Global Variables
 */

static uint8_t eusart2TxHead = 0;
static uint8_t eusart2TxTail = 0;
static uint8_t eusart2TxBuffer[EUSART2_TX_BUFFER_SIZE];
volatile uint8_t eusart2TxBufferRemaining;

static uint8_t eusart2RxHead = 0;
static uint8_t eusart2RxTail = 0;
static uint8_t eusart2RxBuffer[EUSART2_RX_BUFFER_SIZE];
volatile uint8_t eusart2RxCount;

/**
  Section: EUSART2 APIs
 */

void EUSART2_Initialize(void) {
    // disable interrupts before changing states
    PIE3bits.RC2IE = 0;
    PIE3bits.TX2IE = 0;

    // Set the EUSART2 module to the options selected in the user interface.

    // ABDEN disabled; WUE disabled; RCIDL idle; ABDOVF no_overflow; CKTXP async_noninverted_sync_fallingedge; BRG16 16bit_generator; DTRXP not_inverted; 
    BAUD2CON = 0x48;

    // ADDEN disabled; RX9 8-bit; RX9D 0x0; FERR no_error; CREN enabled; SPEN enabled; SREN disabled; OERR no_error; 
    RC2STA = 0x90;

    // CSRC slave_mode; TRMT TSR_empty; TXEN enabled; BRGH hi_speed; SYNC asynchronous; SENDB sync_break_complete; TX9D 0x0; TX9 8-bit; 
    TX2STA = 0x26;

    // Baud Rate = 9600; SPBRGL 160; 
    SPBRG2 = 0xA0;

    // Baud Rate = 9600; SPBRGH 1; 
    SPBRGH2 = 0x01;


    // initializing the driver state
    eusart2TxHead = 0;
    eusart2TxTail = 0;
    eusart2TxBufferRemaining = sizeof (eusart2TxBuffer);

    eusart2RxHead = 0;
    eusart2RxTail = 0;
    eusart2RxCount = 0;

    // enable receive interrupt
    PIE3bits.RC2IE = 1;
}

uint8_t EUSART2_Read(void) {
    uint8_t readValue = 0;

    while (0 == eusart2RxCount) {
    }

    PIE3bits.RC2IE = 0;

    readValue = eusart2RxBuffer[eusart2RxTail++];
    if (sizeof (eusart2RxBuffer) <= eusart2RxTail) {
        eusart2RxTail = 0;
    }
    eusart2RxCount--;
    PIE3bits.RC2IE = 1;

    return readValue;
}

void EUSART2_Write(uint8_t txData) {
    while (0 == eusart2TxBufferRemaining) {
    }

    if (0 == PIE3bits.TX2IE) {
        TXREG2 = txData;
    } else {
        PIE3bits.TX2IE = 0;
        eusart2TxBuffer[eusart2TxHead++] = txData;
        if (sizeof (eusart2TxBuffer) <= eusart2TxHead) {
            eusart2TxHead = 0;
        }
        eusart2TxBufferRemaining--;
    }
    PIE3bits.TX2IE = 1;
}

char getch(void) {
    return EUSART2_Read();
}

void putch(char txData) {
    EUSART2_Write(txData);
}

void EUSART2_Transmit_ISR(void) {

    // add your EUSART2 interrupt custom code
    if (sizeof (eusart2TxBuffer) > eusart2TxBufferRemaining) {
        TXREG2 = eusart2TxBuffer[eusart2TxTail++];
        if (sizeof (eusart2TxBuffer) <= eusart2TxTail) {
            eusart2TxTail = 0;
        }
        eusart2TxBufferRemaining++;
    } else {
        PIE3bits.TX2IE = 0;
    }
}

void EUSART2_Receive_ISR(void) {
    if (1 == RC2STAbits.OERR) {
        // EUSART2 error - restart

        RC2STAbits.CREN = 0;
        RC2STAbits.CREN = 1;
    }

    // buffer overruns are ignored
    eusart2RxBuffer[eusart2RxHead++] = RCREG2;
    if (sizeof (eusart2RxBuffer) <= eusart2RxHead) {
        eusart2RxHead = 0;
    }
    eusart2RxCount++;
}
/**
  End of File
 */
