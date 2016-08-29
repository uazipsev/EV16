/**
  TMR2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr2.c

  @Summary
    This is the generated driver implementation file for the TMR2 driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for TMR2.
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
#include "tmr2.h"
#include "mcc.h"
#include <stdio.h>
#include <stdlib.h>
/**
  Section: TMR2 APIs
*/
int k=0;
int LEDNUM_ENAB[6]=0;   // LED array to keep track which values are blinking (enabled) or not. All values default to 0.
int LEDState[6]=0;      // LED array to keep track which state the LEDS are in. All values default to 0
void TMR2_Initialize(void)
{
    // Set TMR2 to the options selected in the User Interface

    // T2CKPS 1:16; T2OUTPS 1:16; TMR2ON on; 
    T2CON = 0x7E;

    // PR2 48; 
    PR2 = 0x30;

    // TMR2 0; 
    TMR2 = 0x00;

    // Clearing IF flag before enabling the interrupt.
    PIR1bits.TMR2IF = 0;

    // Enabling TMR2 interrupt.
    PIE1bits.TMR2IE = 1;

    // Set Default Interrupt Handler
    TMR2_SetInterruptHandler(TMR2_DefaultInterruptHandler);

    // Start TMR2
    TMR2_StartTimer();
}

void TMR2_StartTimer(void)
{
    // Start the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 1;
}

void TMR2_StopTimer(void)
{
    // Stop the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 0;
}

uint8_t TMR2_ReadTimer(void)
{
    uint8_t readVal;

    readVal = TMR2;

    return readVal;
}

void TMR2_WriteTimer(uint8_t timerVal)
{
    // Write to the Timer2 register
    TMR2 = timerVal;
}

void TMR2_LoadPeriodRegister(uint8_t periodVal)
{
   PR2 = periodVal;
}

void TMR2_ISR(void)
{

    // clear the TMR2 interrupt flag
    PIR1bits.TMR2IF = 0;

    // ticker function call;
    // ticker is 1 -> Callback function gets called everytime this ISR executes
    TMR2_CallBack();
}

void TMR2_CallBack(void) {
   
        int i = 0;
        while (i <= 5) {

            if (LEDNUM_ENAB[i] == 1) {
                switch (LEDState[i]) {
                    case 0:
                        switch (i) {
                            case 0:
                                LED0_Toggle();
                                break;
                            case 1:
                                LED1_Toggle();
                                break;
                            case 2:
                                LED2_Toggle();
                                break;
                            case 3:
                                LED3_Toggle();
                                break;
                            case 4:
                                LED4_Toggle();
                                break;
                            case 5:
                                LED5_Toggle();
                                break;
                        }
                        LEDState[i] = 1;
                        break;
                    case 1:
                        switch (i) {
                            case 0:
                                LED0_Toggle();
                                break;
                            case 1:
                                LED1_Toggle();
                                break;
                            case 2:
                                LED2_Toggle();
                                break;
                            case 3:
                                LED3_Toggle();
                                break;
                            case 4:
                                LED4_Toggle();
                                break;
                            case 5:
                                LED5_Toggle();
                                break;
                        }
                        LEDState[i] = 0;
                        break;
                }
            }
            i = i + 1;
        }
     
     
    
     if(TMR2_InterruptHandler)
    {
        TMR2_InterruptHandler();
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
                LEDState[0]=0;
                LED0_SetLow(); 
                break;
    case 1: 
                LEDNUM_ENAB[1]=0;
                LEDState[1]=0;
                LED1_SetLow();  
                break;
    case 2: 
                LEDNUM_ENAB[2]=0;
                LEDState[2]=0;
                LED2_SetLow(); 
                break;
    case 3: 
                LEDNUM_ENAB[3]=0;
                LEDState[3]=0;
                LED3_SetLow(); 
                break;
    case 4: 
                LEDNUM_ENAB[4]=0;
                LEDState[4]=0;
                LED4_SetLow(); 
                break;
    case 5: 
                LEDNUM_ENAB[5]=0;
                LEDState[5]=0;
                LED5_SetLow() ;
                break;
                 }
    
}
int Get_Blink_State(int LED){
    switch (LED)
    {
        case 0: 
            return LEDState[0]=0;
        case 1: 
            return LEDState[1]=0; 
        case 2: 
            return LEDState[2]=0;
        case 3: 
            return LEDState[3]=0;
        case 4: 
            return LEDState[4]=0;
        case 5: 
            return LEDState[5]=0;
        default:
            return 0;
    }
}
//Problem with int function
void Change_Blink_Rate(int time){
PR2=time;
}



void TMR2_SetInterruptHandler(void* InterruptHandler){
    TMR2_InterruptHandler = InterruptHandler;
}

void TMR2_DefaultInterruptHandler(void){
    // add your TMR2 interrupt custom code
    // or set custom function using TMR2_SetInterruptHandler()
}

/**
  End of File
*/