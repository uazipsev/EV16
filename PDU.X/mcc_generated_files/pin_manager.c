/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25
        Device            :  PIC18F45K22
        Driver Version    :  1.02
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

#include <xc.h>
#include "pin_manager.h"

void PIN_MANAGER_Initialize(void)
{
    LATA = 0x00;
    TRISA = 0xF7;
    ANSELA = 0x27;

    LATB = 0x01;
    TRISB = 0xFE;
    ANSELB = 0x3E;
    WPUB = 0x00;

    LATC = 0x00;
    TRISC = 0xDF;
    ANSELC = 0x1C;

    LATD = 0x00;
    TRISD = 0x0F;
    ANSELD = 0x0F;

    LATE = 0x00;
    TRISE = 0x07;
    ANSELE = 0x07;
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;
    TRISCbits.RC5 = 1;
    TRISCbits.RC1 = 0;
    LATCbits.LATC5 = 1;
    LATCbits.LATC6 = 1;
    LATCbits.LATC7 = 1;
    ANSELCbits.ANSC5 =0;
    ANSELCbits.ANSC6 =0;
    ANSELCbits.ANSC7 =0;

    INTCON2bits.nRBPU = 0x01;
    
    DIGI_INC_SetDigitalOutput();
    DIGI_UP_DN_SetDigitalOutput();
    DIGI_CS_SetDigitalOutput();
    
    TRISDbits.RD1 = 0; //Set FAN PWM as a output
    
    DIGI_UP_DN_SetDigitalMode();
    CLK_SetDigitalMode();
    DIGI_INC_SetDigitalMode();
    
    ANSELCbits.ANSC4 = 1;
    ANSELDbits.ANSD3 = 1;
    ANSELDbits.ANSD2 = 1;
    TRISCbits.RC4 = 1;
    TRISDbits.RD3 = 1;
    TRISDbits.RD2 = 1;
    
    
        
}
/**
 End of File
*/