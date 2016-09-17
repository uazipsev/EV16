/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - v3.00
        Device            :  PIC18F45K22
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20

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

#include <xc.h>
#include "pin_manager.h"

void PIN_MANAGER_Initialize(void)
{
    LATB = 0x0;
    LATA = 0x0;
    ANSELE = 0x7;
    LATE = 0x0;
    LATD = 0x0;
    LATC = 0x0;
    ANSELA = 0x2F;
    ANSELB = 0x3F;
    ANSELC = 0xEC;  // TODO: Used to be 0xCC, I don't know whay why change.....
    ANSELD = 0x3F;
    WPUB = 0xFC;
    TRISD = 0xF2;
    TRISE = 0x7;
    TRISB = 0xC4;
    TRISC = 0xD4;
    TRISA = 0x37;

    INTCON2bits.nRBPU = 0x0;
    
    MUX_S0_SetDigitalMode();
    MUX_S1_SetDigitalMode();
    
    MUX_S0_SetDigitalOutput();
    MUX_S1_SetDigitalOutput();
    
    // enable interrupt-on-change globally
    // interrupts-on-change are globally disabled
    INTCONbits.RBIE = 0;
    
    ANSELC = 0;
    ANSELA = 0;
    TRISCbits.TRISC0=0;
    TRISCbits.TRISC1=0;
    TRISCbits.TRISC2=0;
    TRISAbits.TRISA6=0;
    TRISAbits.TRISA7=0;
    TRISBbits.TRISB3=0;
    TRISBbits.TRISB4=0;
    TRISBbits.TRISB5=0;
    TRISDbits.TRISD4 = 0;
    
    LATBbits.LATB3=0;
    LATBbits.LATB5=0;
    LATBbits.LATB4=0;
}


void PIN_MANAGER_IOC(void)
{    
}

/**
 End of File
*/