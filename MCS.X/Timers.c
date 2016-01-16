#include "Timers.h"
#include <xc.h>
volatile unsigned int talkTime, LEDtime,safetyTime,bootTime;
void timerOne(void) {
    T1CONbits.TON = 0; // turn off timer
    T1CONbits.TCS = 0; //internal instruction clock (36,000,000 Hertz)
    T1CONbits.TCKPS = 0b10; //11/10 /01  /00   //0b10 - 64 divider 0-1:1
    PR1 = 586; //75/600/4500/37500// 0.001s timer
    IFS0bits.T1IF = 0; // clear interrupt flag
    IEC0bits.T1IE = 1; // enable timer 1 interrupt
    T1CONbits.TON = 1; // turn on timer
}
//

void timerTwo(void) {
    // timer 2
    T2CONbits.T32 = 0;
    T2CONbits.TON = 0; //disable timer 2
    T2CONbits.TCS = 0; //internal instruction clock (36,000,000 Hertz)
    T2CONbits.TGATE = 0; //disable gated timer mode
    T2CONbits.TCKPS = 0b11; // 1:256 prescalar    60MHz/256= 234.375KHz (4.266us)
    //TMR2 = 0x00; //clear timer register
    PR2 = 30000; //- set to 279 ms per overflow (4.266 us * 65535)= 279 ms
    IFS0bits.T2IF = 0; // clear timer2 interrupt flag
    IEC0bits.T2IE = 1; // enable timer2 interrupt
    T2CONbits.TON = 1; //enable timer 2
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

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0; // clear timer interrupt flag
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