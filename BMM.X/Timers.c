

#include "Timers.h"
#include "BatteryManagment.h"
volatile unsigned long int slaveTime,time,ADCTime;
volatile unsigned long int LEDtime = 0, talkTime = 0;
void updateTimers();

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
    static unsigned long int lastLEDTime, lastTalkTime, lastSlaveTime,lastADCTime;
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