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

volatile unsigned int SAS, DDS, MCS, PDU, BMM, BootTimer, DebugTimer, SSTimer, DeltaTimer;
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
    BootTimer++;
    DebugTimer++;
    DeltaTimer++;
    SSTimer++;
    SAS++;
    DDS++;
    MCS++;
    PDU++;
    BMM++;
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
        return SAS;
    }
    else if(data == DDSTIMER){
        return DDS;
    }
    else if(data == MCSTIMER){
        return MCS;
    }
    else if(data == PDUTIMER){
        return PDU;
    }
    else if(data == BMMTIMER){
        return BMM;
    }
    else if(data == DEBUGTIME){
        return DebugTimer;
    }
    else if(data == DELTATIMER){
        return DeltaTimer;
    }
    else if(data == SSTIMER){
        return SSTimer;
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
        SAS = 0;
    }
    else if(data == DDSTIMER){
        DDS = 0;
    }
    else if(data == MCSTIMER){
        MCS = 0;
    }
    else if(data == PDUTIMER){
        PDU = 0;
    }
    else if(data == BMMTIMER){
        BMM = 0;
    }
    else if(data == DEBUGTIME){
        DebugTimer = 0;
    }
    else if(data == SSTIMER){
        SSTimer = 0;
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
