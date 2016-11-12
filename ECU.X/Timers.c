/*
 * File:   Timers.c
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015
 */
#include <xc.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Timers.h"
#include "debug.h"
#include "PinDef.h"

unsigned int TimeOut = 0;
unsigned int LastTime = 0;
bool TimeOutActive = 0;

volatile unsigned int SASTimerTime, DDSTimerTime, MCSTimerTime, PDUTimerTime, BMMTimerTime, BootTimerTime, DebugTimerTime, SSTimerTime, DeltaTimerTime = 0;
volatile unsigned int time;
volatile unsigned int talkTime;
volatile unsigned int talkTime1;
volatile unsigned int talkTime2;
volatile unsigned int talkTime3;

void initTimerOne() {
    T1CONbits.TON = 0; // turn off timer
    T1CONbits.TCS = 0;
    T1CONbits.TCKPS = 0; //0b10 - 64 divider
    PR1 = 37500; // 0.001s timer
    IFS0bits.T1IF = 0; // clear interrupt flag
    IEC0bits.T1IE = 1; // enable timer 1 interrupt
    T1CONbits.TON = 1; // turn on timer
}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    time++;
    talkTime++;
    talkTime1++;
    talkTime2++;
    talkTime3++;
    BootTimerTime++;
    DebugTimerTime++;
    DeltaTimerTime++;
    SSTimerTime++;
    SASTimerTime++;
    DDSTimerTime++;
    MCSTimerTime++;
    PDUTimerTime++;
    BMMTimerTime++;
    if(((time - LastTime) >= TimeOut) && (TimeOutActive == 1)){
        TimeOutActive = 0;
        MenuClearFlag();
    }
    IFS0bits.T1IF = 0; // clear interrupt flag
}

void TimeOutSet(int num){
    TimeOut = num;
    LastTime = time;
    TimeOutActive = 1;
    //INDICATOR ^= 1;
}

unsigned int GetTime(char data){
    if(data == SASTIMER){
        return SASTimerTime;
    }
    else if(data == DDSTIMER){
        return DDSTimerTime;
    }
    else if(data == MCSTIMER){
        return MCSTimerTime;
    }
    else if(data == PDUTIMER){
        return PDUTimerTime;
    }
    else if(data == BMMTIMER){
        return BMMTimerTime;
    }
    else if(data == DEBUGTIME){
        return DebugTimerTime;
    }
    else if(data == DELTATIMER){
        return DeltaTimerTime;
    }
    else if(data == SSTIMER){
        return SSTimerTime;
    }
    else if(data == TIME){
        return time;
    }
    else if(data == TALKTIME){
        return talkTime;
    }
    else if(data == TALKTIME1){
        return talkTime1;
    }
    else return 255;
}

void SetTime(char data){
    if(data == SASTIMER){
        SASTimerTime = 0;
    }
    else if(data == DDSTIMER){
        DDSTimerTime = 0;
    }
    else if(data == MCSTIMER){
        MCSTimerTime = 0;
    }
    else if(data == PDUTIMER){
        PDUTimerTime = 0;
    }
    else if(data == BMMTIMER){
        BMMTimerTime = 0;
    }
    else if(data == DEBUGTIME){
        DebugTimerTime = 0;
    }
    else if(data == SSTIMER){
        SSTimerTime = 0;
    }
    else if(data == TIME){
        time = 0;
    }
    else if(data == TALKTIME){
        talkTime = 0;
    }
    else if(data == TALKTIME1){
        talkTime1 = 0;
    }
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {

    IFS0bits.T2IF = 0; // clear timer interrupt flag
}
