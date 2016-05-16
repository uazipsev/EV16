
/**
  Section: Included Files
 */

#include <xc.h>
#include "tmr1.h"
#include "../Global.h"
#include "../Tempeture.h"
#include "../Battery.h"
#include "../Current.h"
#include "pin_manager.h"
#include "../Functions.h"

/**
  Section: Global Variable Definitions
 */
volatile uint16_t timer1ReloadVal;

/**
  Section: TMR1 APIs
 */

void TMR1_Initialize(void) {
    //Set the Timer to the options selected in the GUI

    //T1OSCEN disabled; T1RD16 disabled; T1CKPS 1:8; TMR1CS FOSC/4; T1SYNC do_not_synchronize; TMR1ON disabled; 
    T1CON = 0x34;

    //T1GVAL disabled; T1GSPM disabled; T1GSS T1G; T1GTM disabled; T1GPOL low; TMR1GE disabled; T1GGO done; 
    T1GCON = 0x00;

    //TMR1H 11; 
    TMR1H = 0x0B;

    //TMR1L 220; 
    TMR1L = 0xDC;

    // Load the TMR value to reload variable
    timer1ReloadVal = TMR1;

    // Clearing IF flag before enabling the interrupt.
    PIR1bits.TMR1IF = 0;

    // Enabling TMR1 interrupt.
    PIE1bits.TMR1IE = 1;

    // Start TMR1
    TMR1_StartTimer();
}

void TMR1_StartTimer(void) {
    // Start the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 1;
}

void TMR1_StopTimer(void) {
    // Stop the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 0;
}

uint16_t TMR1_ReadTimer(void) {
    uint16_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;

    readValLow = TMR1L;
    readValHigh = TMR1H;

    readVal = ((uint16_t) readValHigh << 8) | readValLow;

    return readVal;
}

void TMR1_WriteTimer(uint16_t timerVal) {
    if (T1CONbits.T1SYNC == 1) {
        // Stop the Timer by writing to TMRxON bit
        T1CONbits.TMR1ON = 0;

        // Write to the Timer1 register
        TMR1H = (timerVal >> 8);
        TMR1L = (uint8_t) timerVal;

        // Start the Timer after writing to the register
        T1CONbits.TMR1ON = 1;
    } else {
        // Write to the Timer1 register
        TMR1H = (timerVal >> 8);
        TMR1L = (uint8_t) timerVal;
    }
}

void TMR1_Reload(void) {
    // Write to the Timer1 register
    TMR1H = (timer1ReloadVal >> 8);
    TMR1L = (uint8_t) timer1ReloadVal;
}

void TMR1_StartSinglePulseAcquisition(void) {
    T1GCONbits.T1GGO = 1;
}

uint8_t TMR1_CheckGateValueStatus(void) {
    return T1GCONbits.T1GVAL;
}

void TMR1_ISR(void) {
    static volatile unsigned int CountCallBack = 0;

    // Clear the TMR1 interrupt flag
    PIR1bits.TMR1IF = 0;

    // Write to the Timer1 register
    TMR1H = (timer1ReloadVal >> 8);
    TMR1L = (uint8_t) timer1ReloadVal;

    // callback function - called every 4th pass
    if (++CountCallBack >= TMR1_INTERRUPT_TICKER_FACTOR)
    {
        // ticker function call
        Indicator_Toggle();
        // reset ticker counter
        CountCallBack = 0;
    }
    else if(CountCallBack == 1)
    {
        CodeRuning = 1;
        Current_Read();
    }
    else if(CountCallBack == 2)
    {
        CodeRuning = 1;
        Battery_Read();
    }
    else if(CountCallBack == 3)
    {
        CodeRuning = 1;
        Temp_Read();
    }
}

void TMR1_CallBack(void)
{
    // Add your custom callback code here
}

/**
 End of File
 */
