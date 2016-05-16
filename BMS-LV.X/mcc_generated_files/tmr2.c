
/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr2.h"
#include "../Battery.h"
#include "../Current.h"
#include "../Tempeture.h"

/**
  Section: TMR2 APIs
*/

void TMR2_Initialize(void)
{
    // Set TMR2 to the options selected in the User Interface

    // TMR2ON off; T2CKPS 1:16; T2OUTPS 1:1; 
    T2CON = 0x02;

    // PR2 124; 
    PR2 = 0x7C;

    // TMR2 0x0; 
    TMR2 = 0x00;

    // Clearing IF flag before enabling the interrupt.
    PIR1bits.TMR2IF = 0;

    // Enabling TMR2 interrupt.
    PIE1bits.TMR2IE = 1;

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
    //1mS intervals
    PIR1bits.TMR2IF = 0;
    //CallADC read fcn....
    Battery_Read();
    Temp_Read();
}
/**
  End of File
*/