/*
 * File:   PWM.c
 * Author: Rick
 *
 * Created on May 20, 2015, 3:05 AM
 *
 * Controlls PWM for dsPIC
 *
 */

#include "pwm.h"
#include <xc.h>
#define TimerPeriod 9320
//Init the PWM channel

void PWM_Init(void) {
    Timmer2Init();
    OC1CONbits.OCM = 0b110;
    OC1R = 0;
    OC1RS = 0x0F; //min PWM
    OC1CONbits.OCTSEL = 0;
}

//The PWM runs off of Timer 2

void Timmer2Init(void) {
    T2CONbits.TON = 0;
    T2CONbits.TCS = 0;
    T2CONbits.TGATE = 0;
    T2CONbits.TCKPS = 0b11;
    TMR2 = 0x00;
    PR2 = TimerPeriod;
    T2CONbits.TON = 1;
}

//sets PWM duty

void PWMupdate(int output) {
    if (output > 100) {
        output = 100;
    }
    if (output < 0) {
        output = 0;
    }
    OC1RS = (output/100.0)*TimerPeriod;
}