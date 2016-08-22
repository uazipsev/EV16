

/**
  Section: Included Files
 */

#include <xc.h>
#include "tmr0.h"
#include "PinDef.h"

/**
  Section: Global Variables Definitions
 */
volatile uint16_t timer0ReloadVal16bit;

/**
  Section: TMR0 APIs
 */

unsigned long time = 0;


void TMR0_Initialize(void) {
    // Set TMR0 to the options selected in the User Interface

    // TMR0ON enabled; T0SE Increment_hi_lo; PSA assigned; T0CS FOSC/4; T08BIT 16-bit; T0PS 1:32; 
    T0CON = 0x94;

    // TMR0H 207; 
    TMR0H = 0xCF;

    // TMR0L 44; 
    TMR0L = 0x2C;

    // Load TMR0 value to the 16-bit reload variable
    timer0ReloadVal16bit = 53036;

    // Clear Interrupt flag before enabling the interrupt
    INTCONbits.TMR0IF = 0;

    // Enabling TMR0 interrupt.
    INTCONbits.TMR0IE = 1;

    // Start TMR0
    TMR0_StartTimer();
}

void TMR0_StartTimer(void) {
    // Start the Timer by writing to TMR0ON bit
    T0CONbits.TMR0ON = 1;
}

void TMR0_StopTimer(void) {
    // Stop the Timer by writing to TMR0ON bit
    T0CONbits.TMR0ON = 0;
}

uint16_t TMR0_Read16bitTimer(void) {
    uint16_t readVal;
    uint8_t readValLow;
    uint8_t readValHigh;

    readValLow = TMR0L;
    readValHigh = TMR0H;
    readVal = ((uint16_t) readValHigh << 8) + readValLow;

    return readVal;
}

void TMR0_Write16bitTimer(uint16_t timerVal) {
    // Write to the Timer0 register
    TMR0H = timerVal >> 8;
    TMR0L = (uint8_t) timerVal;
}

void TMR0_Reload16bit(void) {
    // Write to the Timer0 register
    TMR0H = timer0ReloadVal16bit >> 8;
    TMR0L = (uint8_t) timer0ReloadVal16bit;
}

void TMR0_ISR(void) {
    // reload TMR0
    // Write to the Timer0 register
    TMR0H = timer0ReloadVal16bit >> 8;
    TMR0L = (uint8_t) timer0ReloadVal16bit;

    time++; //ticker for time
    //INDICATOR ^= 1; 
    // clear the TMR0 interrupt flag
    INTCONbits.TMR0IF = 0;
}

long GetTime(){
    return time;
}

void SetTime(){
    time = 0;
}

/**
  End of File
 */

