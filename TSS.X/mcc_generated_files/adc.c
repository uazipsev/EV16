/**
  ADC Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adc.c

  @Summary
    This is the generated driver implementation file for the ADC driver using MPLAB® Code Configurator

  @Description
    This source file provides implementations for driver APIs for ADC.
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
#include "adc.h"

/**
  Section: ADC Module APIs
 */

void ADC_Initialize(void) {
    // set the ADC to the options selected in the User Interface

    // GO_nDONE stop; ADON enabled; CHS AN0; 
    ADCON0 = 0x01;

    // PVCFG VDD; TRIGSEL CTMU; NVCFG VSS; 
    ADCON1 = 0x80;

    // ADFM right; ADCS FOSC/32; ACQT 2; 
    ADCON2 = 0x8A;

    // ADRESL 0x0; 
    ADRESL = 0x00;

    // ADRESH 0x0; 
    ADRESH = 0x00;

    // Enabling ADC interrupt.
    PIE1bits.ADIE = 1;
}

void ADC_StartConversion(adc_channel_t channel) {
    // select the A/D channel
    ADCON0bits.CHS = channel;

    // Turn on the ADC module
    ADCON0bits.ADON = 1;


    // Start the conversion
    ADCON0bits.GO_nDONE = 1;
}

bool ADC_IsConversionDone() {
    // Start the conversion
    return (!ADCON0bits.GO_nDONE);
}

adc_result_t ADC_GetConversionResult(void) {
    // Conversion finished, return the result
    return ((ADRESH << 8) + ADRESL);
}

adc_result_t ADC_GetConversion(adc_channel_t channel) {
    // Select the A/D channel
    ADCON0bits.CHS = channel;

    // Turn on the ADC module
    ADCON0bits.ADON = 1;


    // Start the conversion
    ADCON0bits.GO_nDONE = 1;

    // Wait for the conversion to finish
    while (ADCON0bits.GO_nDONE) {
    }

    // Conversion finished, return the result
    return ((ADRESH << 8) + ADRESL);
}

void ADC_ISR(void) {
    // Clear the ADC interrupt flag
    PIR1bits.ADIF = 0;
}
/**
 End of File
 */