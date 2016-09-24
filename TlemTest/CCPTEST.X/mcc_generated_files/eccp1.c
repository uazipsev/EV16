/**
  ECCP1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eccp1.c

  @Summary
    This is the generated driver implementation file for the ECCP1 driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for ECCP1.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.16
        Device            :  PIC18F45K20
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "eccp1.h"
#include <stdio.h>

/**
  Section: Capture Module APIs
*/

void ECCP1_Initialize(void)
{
    // Set the ECCP1 to the options selected in the User Interface
    ECCPTMRS0 = 0x00;
    // CCP1M Every rising edge; DC1B 0; P1M single; 
    CCP1CON = 0x05;    

    // CCPR1L 0; 
    CCPR1L = 0x00;    

    // CCPR1H 0; 
    CCPR1H = 0x00;    

    // Clear the ECCP1 interrupt flag
    PIR1bits.CCP1IF = 0;

    // Enable the ECCP1 interrupt
    PIE1bits.CCP1IE = 1;
}

void ECCP1_CaptureISR(void)
{
    CCP_PERIOD_REG_T module;

    // Clear the ECCP1 interrupt flag
    PIR1bits.CCP1IF = 0;
    
    // Copy captured value.
    module.ccpr1l = CCPR1L;
    module.ccpr1h = CCPR1H;
    
    // Return 16bit captured value
    ECCP1_CallBack(module.ccpr1_16Bit);
}

void ECCP1_CallBack(uint16_t capturedValue)
{
    printf("The elapsed time since the last pulse is %f ", capturedValue);
    // Add your code here
}
/**
 End of File
*/