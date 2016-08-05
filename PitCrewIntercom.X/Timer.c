#include "Timer.h"
#include <xc.h>
/**
  Section: TMR2 APIs
*/

unsigned int ticker = 0;

void TMR2_Initialize(void)
{
    // Set TMR2 to the options selected in the User Interface

    // T2CKPS 1:16; T2OUTPS 1:16; TMR2ON on; 0x7c
    T2CON = 0x00;
    T2CONbits.TMR2ON = 0;

    // PR2 48; 
    PR2 = 18;

    // TMR2 0; 
    TMR2 = 0;

    // Clearing IF flag before enabling the interrupt.
    PIR1bits.TMR2IF = 0;

    // Enabling TMR2 interrupt.
    PIE1bits.TMR2IE = 1;

    // Set Default Interrupt Handler
    //TMR2_SetInterruptHandler(TMR2_DefaultInterruptHandler);

    // Start TMR2
    //TMR2_StartTimer();
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

void TMR2_ISR(void)
{
    // ticker function call;
    ticker++;
    // clear the TMR2 interrupt flag
    PIR1bits.TMR2IF = 0;

}

void ClearTicker(void){
    ticker = 0;
}

unsigned int GetTicker(){
    return ticker;
}
/**
  End of File
*/
