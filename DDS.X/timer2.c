/**
  TMR2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr2.c

  @Summary
    This is the generated driver implementation file for the TMR2 driver using MPLAB® Code Configurator

  @Description
    This source file provides APIs for TMR2.
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
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "timer2.h"



int LEDNUM_ENAB[6]=0;   // LED array to keep track which values are blinking (enabled) or not. All values default to 0.
int LEDState[6]=0;      // LED array to keep track which state the LEDS are in. All values default to 0
void TMR2_Initialize(void) {
    // Set TMR2 to the options selected in the User Interface

    // TMR2ON off; T2OUTPS 1:1; T2CKPS 1:16; 
    T2CON = 0x02;

    // PR2 249; 
    PR2 = 0xF9;

    // TMR2 0x0; 
    TMR2 = 0x00;

    // Clearing IF flag before enabling the interrupt.
    PIR1bits.TMR2IF = 0;

    // Enabling TMR2 interrupt.
    PIE1bits.TMR2IE = 1;

    // Start TMR2
    TMR2_StartTimer();
}

void TMR2_StartTimer(void) {
    // Start the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 1;
}

void TMR2_StopTimer(void) {
    // Stop the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 0;
}

uint8_t TMR2_ReadTimer(void) {
    uint8_t readVal;

    readVal = TMR2;

    return readVal;
}

void TMR2_WriteTimer(uint8_t timerVal) {
    // Write to the Timer2 register
    TMR2 = timerVal;
}

void TMR2_LoadPeriodRegister(uint8_t periodVal) {
    PR2 = periodVal;
}

void TMR2_ISR(void) {
    static volatile unsigned int CountCallBack = 0;

    // clear the TMR2 interrupt flag
    PIR1bits.TMR2IF = 0;

    // callback function - called every 10th pass
    if (++CountCallBack >= TMR2_INTERRUPT_TICKER_FACTOR) {
        // ticker function call
        TMR2_CallBack();

        // reset ticker counter
        CountCallBack = 0;
    }

    // add your TMR2 interrupt custom code
}

void TMR2_CallBack(void) {
    int i=0;
    while(i<=5){

   if(LEDNUM_ENAB[i]==1){
   switch (LEDState[i]) {  
           case 0:
           LED0_Toggle();
           LEDState[i]=1;
           break;
           case 1:
              LED0_Toggle();
           LEDState[i]=0;
           break;
   }
            }  
   i=i+1;  
    }
   
    
    
    // Add your custom callback code here
    // this code executes every TMR2_INTERRUPT_TICKER_FACTOR periods of TMR2
}


//Custom Function called by IO to set LED that are blinking.
void setLED(int led){
    switch (led){
            case 0: 
                LEDNUM_ENAB[0]=1;
                LEDState[0]=0;
                break;
            case 1: 
                LEDNUM_ENAB[1]=1;
                LEDState[1]=0;
                break;
            case 2: 
                LEDNUM_ENAB[2]=1;
                LEDState[2]=0;
                break;
            case 3: 
                LEDNUM_ENAB[3]=1;
                LEDState[3]=0;
                break;
            case 4: 
                LEDNUM_ENAB[4]=1;
                LEDState[4]=0;
                break;
            case 5: 
                LEDNUM_ENAB[5]=1;
                LEDState[5]=0;
                break;
    }
}
void Off_Led(int led){
    switch (led){
    case 0: 
                LEDNUM_ENAB[0]=0;
                LED0_SetLow(); 
                break;
    case 1: 
                LEDNUM_ENAB[1]=0;
                LED1_SetLow();  
                break;
    case 2: 
                LEDNUM_ENAB[2]=0;
                LED2_SetLow(); 
                break;
    case 3: 
                LEDNUM_ENAB[3]=0;
                LED3_SetLow(); 
                break;
    case 4: 
                LEDNUM_ENAB[4]=0;
                LED4_SetLow(); 
                break;
    case 5: 
                LEDNUM_ENAB[5]=0;
                LED5_SetLow() ;
                break;
                 }
}


void Change_Blink_Rate(int time){
time=TMR2_INTERRUPT_TICKER_FACTOR;
}

/**
  End of File
 */
