/**
  CCP5 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    ccp5.c

  @Summary
    This is the generated driver implementation file for the CCP5 driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for CCP5.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - v3.00
        Device            :  PIC18F45K22
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20
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

#include <xc.h>
#include "ccp5.h"

/**
  Section: Capture Module APIs
*/

void CCP5_Initialize(void)
{
    // Set the CCP5 to the options selected in the User Interface

    // CCP5M Falling edge; DC5B 0; 
    CCP5CON = 0x04;    

    // CCPR5L 0; 
    CCPR5L = 0x00;    

    // CCPR5H 0; 
    CCPR5H = 0x00;    
    
    // Selecting Timer 1
    CCPTMRS1bits.C5TSEL = 0x0;

    // Clear the CCP5 interrupt flag
    PIR4bits.CCP5IF = 0;

    // Enable the CCP5 interrupt
    PIE4bits.CCP5IE = 1;
}

void CCP5_CaptureISR(void)
{
    CCP_PERIOD_REG_T module;

    // Clear the CCP5 interrupt flag
    PIR4bits.CCP5IF = 0;
    
    // Copy captured value.
    module.ccpr5l = CCPR5L;
    module.ccpr5h = CCPR5H;
    
    // Return 16bit captured value
    CCP5_CallBack(module.ccpr5_16Bit);
}

void CCP5_CallBack(uint16_t capturedValue)
{
    // Add your code here
}
/**
 End of File
*/