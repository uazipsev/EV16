#include "Timers.h"
#include <xc.h>
unsigned int talkTime, LEDtime,safetyTime,bootTime;

void timerOne(void) {
    T1CONbits.TON = 0; // turn off timer
    T1CONbits.TCS = 0; //internal instruction clock (36,000,000 Hertz)
    T1CONbits.TCKPS = 0b10; //11/10 /01  /00   //0b10 - 64 divider 0-1:1
    PR1 = 586; //75/600/4500/37500// 0.001s timer
    IFS0bits.T1IF = 0; // clear interrupt flag
    IEC0bits.T1IE = 1; // enable timer 1 interrupt
    T1CONbits.TON = 1; // turn on timer
}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    LEDtime++;
    if(bootTime<5005){
        bootTime++;
    }
    talkTime++;
    safetyTime++;
    IFS0bits.T1IF = 0; // clear interrupt flag
}

int getLEDTime(){
    return LEDtime;
}

void ClearLEDTime(){
    LEDtime = 0;
}

void setLEDTime(int value){
    LEDtime = value;
}

int GetSafetyTime(){
    return safetyTime;
}

void ClearSafetyTime(){
    safetyTime = 0;
}

int GetTalkTime(){
    return talkTime;
}

void ClearTalkTime(){
    talkTime = 0;
}

int GetBootTime(){
    return bootTime;
}

void ClearBootTime(){
    bootTime = 0;
}
