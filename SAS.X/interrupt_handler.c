#include <xc.h>
#include <stdbool.h>
#include "interrupt_handler.h"
#include "PinDef.h"

extern volatile unsigned int ADCTime;

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {   
    LEDtime++;
    talkTime++;
    ADCTime++;
    IFS0bits.T1IF = 0; // clear interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0; // clear timer interrupt flag
}


