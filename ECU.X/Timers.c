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

int TimeOut = 0;
int LastTime = 0;
bool TimeOutActive = 0;

unsigned int SAS, DDS, MCS, PDU, BMM, BootTimer,DebugTimer;
unsigned int time;
unsigned int talkTime;
unsigned int talkTime1;
unsigned int talkTime2;
unsigned int talkTime3;

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
    if (SAS < COMM_TIMER_MAX_TIME)
        SAS++;
    if (DDS < COMM_TIMER_MAX_TIME)
        DDS++;
    if (MCS < COMM_TIMER_MAX_TIME)
        MCS++;
    if (PDU < COMM_TIMER_MAX_TIME)
        PDU++;
    if (BMM< COMM_TIMER_MAX_TIME)
        BMM++;
    if((time - LastTime) > TimeOut){
        TimeOutActive = 1;
        LastTime = time; 
    }
    IFS0bits.T1IF = 0; // clear interrupt flag
}

void TimeOutSet(int num){
    TimeOut = num;
}

int GetTime(char data){
    if(data == SASTimer){
        return SAS;
    }
    if(data == DDSTimer){
        return DDS;
    }
    if(data == MCSTimer){
        return MCS;
    }
    if(data == PDUTimer){
        return PDU;
    }
    if(data == BMMTimer){
        return BMM;
    }
}

void SetTime(char data){
    if(data == SASTimer){
        SAS = 0;
    }
    if(data == DDSTimer){
        DDS = 0;
    }
    if(data == MCSTimer){
        MCS = 0;
    }
    if(data == PDUTimer){
        PDU = 0;
    }
    if(data == BMMTimer){
        BMM = 0;
    }
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {

    IFS0bits.T2IF = 0; // clear timer interrupt flag
}
