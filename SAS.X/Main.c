
#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "PinDef.h"
#include "main.h"
#include "ADDRESSING.h"
#include "ADC.h"
#include <stdio.h>
#include <stdlib.h>

void ledDebug();

int main(void) {
    Setup();
    LED = 1;
    while (1) {
        ledDebug();
        //Comms handling
        updateComms();
        if(ADCDataReady) {
            FilterADC();
            ADCDataReady = false;
            IEC0bits.AD1IE = 1;
        }
    }
}

void ledDebug() {
    if (LEDtime > 1000) {
        LED ^= 1;
        //printf("T1: %0.2f T2: %0.2f \n", GetADC(Throttle1), GetADC(Throttle2));
        //printf("B1: %0.2f B2: %0.2f \n", GetADC(Brake1), GetADC(Brake2));
        LEDtime = 0;
    }
}


