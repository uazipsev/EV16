/**
  ECCP2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eccp2.c

  @Summary
    This is the generated driver implementation file for the ECCP2 driver using MPLAB® Code Configurator

  @Description
    This source file provides APIs for ECCP2.
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

#include <xc.h>
#include "eccp2.h"

/**
  Section: Capture Module APIs
 */

void ECCP2_Initialize(void) {
    // Set the ECCP2 to the options selected in the User Interface

    // CCP2M capture_risingedge; P2M single; DC2B LSBs; 
    CCP2CON = 0x05;

    // CCPR2L 0x0; 
    CCPR2L = 0x00;

    // CCPR2H 0x0; 
    CCPR2H = 0x00;

    // Clear the ECCP2 interrupt flag
    PIR2bits.CCP2IF = 0;

    // Enable the ECCP2 interrupt
    PIE2bits.CCP2IE = 1;

    // Selecting Timer1
    CCPTMRS0bits.C2TSEL = 0x0;
}

void ECCP2_CaptureISR(void) {
    CCP_PERIOD_REG_T module;

    // Clear the ECCP2 interrupt flag
    PIR2bits.CCP2IF = 0;

    // Copy captured value.
    module.ccpr2l = CCPR2L;
    module.ccpr2h = CCPR2H;

    // Return 16bit captured value
    ECCP2_CallBack(module.ccpr2_16Bit);
}

void ECCP2_CallBack(uint16_t capturedValue) {
    // Add your code here
}
/**
 End of File
 */