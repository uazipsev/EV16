#include "pwm.h"
#include <xc.h>

void PWM_Init(void) {
    //First PWM output
    Timmer2Init();
    OC1CON1bits.OCM = 0b000;
    OC1R = 0x0F;
    OC1RS = 0x0F; //min PWM
    OC1CON1bits.OCTSEL = 0;
    OC1R = 0x0F;
    OC1CON1bits.OCM = 0b110;
}

void Timmer2Init(void) {
    T2CONbits.TON = 0;
    T2CONbits.TCS = 0;
    T2CONbits.TGATE = 0;
    T2CONbits.TCKPS = 0b10;
    TMR2 = 0x00;
    PR2 = 0x04FF;
    T2CONbits.TON = 1;
}

void PWMupdate(int output) {
    if (output > 100) {
        output = 100;
    }
    if (output < 0) {
        output = 0;
    }
    output = output * 35;
    OC1RS = output;
}

void PERupdate(int output) {
    // if(output > 100)
    // {
    //    output = 100;
    // }
    // if(output < 0)
    // {
    //    output = 0;
    // }
    //T2CONbits.TON = 0;
    TMR2 = 0x00;
    PR2 = output;
    //T2CONbits.TON = 1;
}

void PWMoff(){
    T2CONbits.TON = 0;
}

void PWMon(){
    T2CONbits.TON = 1;
}