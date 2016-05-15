

#include "Timers.h"
#include "BatteryManagment.h"
#include "Function.h" //TODO get rid of
unsigned long int slaveTime,time,ADCTime;
unsigned long int LEDtime = 0, talkTime = 0, time =0;
static unsigned long int lastLEDTime=0, lastTalkTime=0, lastSlaveTime=0,lastADCTime=0;// TODO could be issue with timer was intilized in update timers with not decleration. 

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    time++;
    IFS0bits.T1IF = 0; // clear interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {
    
    
    CurrentCoulombCount(time);
    IFS0bits.T2IF = 0; // clear timer interrupt flag
}

void initTimerOne(void) {
    T1CONbits.TON = 0; // turn off timer
    T1CONbits.TCS = 0; //internal instruction clock (36,000,000 Hertz)
    T1CONbits.TCKPS = 0b10; //0b10 - 64 divider 0-1:1
    TMR1 = 0x00;
    PR1 = 700; //37500// 0.001s timer
    IFS0bits.T1IF = 0; // clear interrupt flag
    IEC0bits.T1IE = 1; // enable timer 1 interrupt
    T1CONbits.TON = 1; // turn on timer
}

void initTimerTwo(void) {
    // timer 2
    T2CONbits.T32 = 0;
    T2CONbits.TON = 0; //disable timer 2
    T2CONbits.TCS = 0; //internal instruction clock (36,000,000 Hertz)
    T2CONbits.TGATE = 0; //disable gated timer mode
    T2CONbits.TCKPS = 0b11; // 1:256 prescalar    36MHz/256= 140.625KHz (7.111us)
    TMR2 = 0x00; //clear timer register
    PR2 = 65535; //- set to 279 ms per overflow (7.111us * x)= 466 ms
    IFS0bits.T2IF = 0; // clear timer2 interrupt flag
    IEC0bits.T2IE = 1; // enable timer2 interrupt
    T2CONbits.TON = 1; //enable timer 2
}

void updateTimers() {
    //if (lastLEDTime != time) {
        LEDtime += (time - lastLEDTime);
        lastLEDTime = time;
    //}
    //if (lastSlaveTime != time) {
        slaveTime += (time - lastSlaveTime);
        lastSlaveTime = time;
    //}
    //if (lastTalkTime != time) {
        talkTime += (time - lastTalkTime);
        lastTalkTime = time;
    //}
        ADCTime += (time - lastADCTime);
        lastADCTime = time;
}

int time_get(char WhatTime){
    if(WhatTime == 1){
        return LEDtime;
    }
    else if(WhatTime == 2){
        return slaveTime;
    }
    else if(WhatTime == 3){
        return talkTime;
    }
    else if(WhatTime == 4){
        return ADCTime;
    }
    return -1;
}

void time_Set(char WhatTime, int value){
    if(WhatTime == 1){
        LEDtime = value;
    }
    else if(WhatTime == 2){
        slaveTime = value;
    }
    else if(WhatTime == 3){
        talkTime = value;
    }
    else if(WhatTime == 4){
        ADCTime = value;
    }
}

void TalkTimeSet(int value){
    talkTime = value;
}
