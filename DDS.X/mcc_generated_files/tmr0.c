

/**
  Section: Included Files
 */

#include <xc.h>
#include "tmr0.h"
#include "pin_manager.h"
#include "../IO.h"

/**
  Section: Global Variables Definitions
 */
volatile uint16_t timer0ReloadVal16bit;

/**
  Section: TMR0 APIs
 */


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
    static volatile uint16_t CountCallBack = 0;
    // reload TMR0
    // Write to the Timer0 register
    TMR0H = timer0ReloadVal16bit >> 8;
    TMR0L = (uint8_t) timer0ReloadVal16bit;

    for (int x = 0; x < 8; x++) {
        ReadButtonState(x);
    }
    time++;
    // callback function - called every 5th pass
    if (++CountCallBack >= TMR0_INTERRUPT_TICKER_FACTOR) {
        // ticker function call
        TMR0_CallBack();

        // reset ticker counter
        CountCallBack = 0;
    }
    // clear the TMR0 interrupt flag
    INTCONbits.TMR0IF = 0;
}

void TMR0_CallBack(void) {
//    INDICATOR_Toggle();
    //    bit a = Button8_PORT;
    // Add your custom callback code here
    // this code executes every 5 TMR0 periods
}
/**
  End of File
 */