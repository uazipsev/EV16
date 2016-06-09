

#include "Timers.h"
#include "BatteryManagment.h"
#include "Function.h" //TODO get rid of
int timer_3_Function=0;

unsigned long int slaveTime,time,ADCTime;
unsigned long int LEDtime = 0, talkTime = 0, time =0;
static unsigned long int lastLEDTime=0, lastTalkTime=0, lastSlaveTime=0,lastADCTime=0;// TODO could be issue with timer was intilized in update timers with not decleration. 
int FaultValueHistory=0;
   unsigned long count=0;
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    time++;
    IFS0bits.T1IF = 0; // clear interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {
    
   FaultValue=Read_Total_Voltage(cell_codes_Bank1, cell_codes_Bank2);
   if (FaultValue==0){
    FaultValue=Read_Total_GPIO(Aux_codes_Bank1,Aux_codes_Bank2);
   //Temprature sensors.
   }
    CurrentCoulombCount(time);
    
    IFS0bits.T2IF = 0; // clear timer interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void) {
    if (timer_3_Function==1){
     
       
    }
    else if (timer_3_Function==2){
        if (count>100000){
 INDICATOR = !INDICATOR; // TODO may change LED to different LED 
      
    count=0;}
    
    count=count+1;
    ;}
 
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

void initTimerThree(int mode) {
    // timer 3 Fault Timer
    T3CONbits.TON = 0; //disable timer 3
    T3CONbits.TCS = 0; //internal instruction clock (36,000,000 Hertz)
    T3CONbits.TGATE = 0; //disable gated timer mode
    T3CONbits.TCKPS = 0b11; // 1:256 prescalar    36MHz/256= 140.625KHz (7.111us)
    TMR3 = 0x00; //clear timer register
    if (mode==1)//run mode
    { PR3 = 65535; //- set to 279 ms per overflow (7.111us * x)= 100 ms 14063}
    timer_3_Function=1;}
    else if (mode==2)//charge mode
    {PR3 =35156;  // 250 ms =35156
    timer_3_Function=2;}   
    IFS0bits.T3IF = 0; // clear timer2 interrupt flag
    IEC0bits.T3IE = 1; // enable timer 3 interrupt
    T3CONbits.TON = 1; //enable timer 3
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
void CheckFault(void) {
    if (FaultValue != 0) {   
    Saftey_Relay_Set = 1;
    //TODO Need Delay
    Saftey_Relay_Set=0;
    }
    FaultValueHistory=FaultValue;
    FaultValue=0;
    while(1){
    ;}
}

