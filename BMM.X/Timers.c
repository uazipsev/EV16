/*******************************************************************
 * @brief           Timers.c
 * @brief           Handels Times   
 * @return          N/A
 * @note            This file contains code to handel time for system
 *******************************************************************/

#include "Timers.h"
#include "BatteryManagment.h"
#include "Function.h" //TODO get rid of
int timer_3_Function=0;
int *Sample_Number=0; //Need to figure what the fuck was this for.
int Sample_Numbers=0;
unsigned long int slaveTime = 0,ADCTime = 0,LEDtime = 0,talkTime = 0;
unsigned long int DebugTime,lastDebugTime;
volatile unsigned long int time =0;
static unsigned long int lastLEDTime=0, lastTalkTime=0, lastSlaveTime=0,lastADCTime=0;// TODO could be issue with timer was intilized in update timers with not decleration. 
int FaultValueHistory=0;
   unsigned long count=0;
   
/*******************************************************************
 * @brief           _T1Interrupt
 * @brief           Handels T1 Interrupt
 * @return          N/A
 * @note            Used for time keeping
 *******************************************************************/
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    time++;
    IFS0bits.T1IF = 0; // clear interrupt flag
    
}

/*******************************************************************
 * @brief           _T2Interrupt
 * @brief           Handels T2 Interrupt
 * @return          N/A
 * @note            Used for BMS coms and CC
 *******************************************************************/
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {
   INDICATOR = !INDICATOR;
        //Read_Total_Voltage(cell_codes_Bank1, cell_codes_Bank2,Sample_Number);               
                       
   //FaultValue=Read_Total_Voltage(cell_codes_Bank1, cell_codes_Bank2,Sample_Number);
  // if (FaultValue==0){
   //Delay(100);
   
           
//    readc();
   if (Sample_Numbers<=10)
     {
           Sample_Numbers++;
    }
     else if (Sample_Numbers>10){
     Starting_Samples=false;}
   
   //}
   // CurrentCoulombCount(time);
    
    IFS0bits.T2IF = 0; // clear timer interrupt flag
}

/*******************************************************************
 * @brief           _T3Interrupt
 * @brief           Handels T3 Interrupt
 * @return          N/A
 * @note            Used for LED?
 *******************************************************************/
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

/*******************************************************************
 * @brief           initTimerOne
 * @brief           Handels T1 setup
 * @return          N/A
 * @note            N/A
 *******************************************************************/
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

/*******************************************************************
 * @brief           initTimerTwo
 * @brief           Handels T1 setup
 * @return          N/A
 * @note            N/A
 *******************************************************************/
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

/*******************************************************************
 * @brief           initTimerThree
 * @brief           Handels T1 setup
 * @return          N/A
 * @note            N/A
 *******************************************************************/
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

/*******************************************************************
 * @brief           updateTimers
 * @brief           Handels time counting 
 * @return          N/A
 * @note            The fcn is Async of timer 1 and augments counters
 *******************************************************************/
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
        
        DebugTime += (time - lastDebugTime);
        lastDebugTime = time;
}

/*******************************************************************
 * @brief           time_get
 * @brief           Handels time getter 
 * @return          (int) time
 * @note            The fcn returns requested time
 *******************************************************************/
int time_get(char WhatTime){
    if(WhatTime == LEDTM){
        return LEDtime;
    }
    else if(WhatTime == SLVTM){
        return slaveTime;
    }
    else if(WhatTime == TLKTM){
        return talkTime;
    }
    else if(WhatTime == ADCTM){
        return ADCTime;
    }
    else if(WhatTime == DEBUGTIME){
        return DebugTime;
    }
    return -1;
}

/*******************************************************************
 * @brief           time_set
 * @brief           Handels time setter 
 * @return          N/A
 * @note            The fcn modifies time counters 
 *******************************************************************/
void time_Set(char WhatTime, int value){
    if(WhatTime == LEDTM){
        LEDtime = value;
    }
    else if(WhatTime == SLVTM){
        slaveTime = value;
    }
    else if(WhatTime == TLKTM){
        talkTime = value;
    }
    else if(WhatTime == ADCTM){
        ADCTime = value;
    }
    else if(WhatTime == DEBUGTIME){
        DebugTime = value;
    }
}

/*******************************************************************
 * @brief           TalkTimeSet
 * @brief           
 * @return          N/A
 * @note            
 *******************************************************************/
void TalkTimeSet(int value){
    talkTime = value;
}

/*******************************************************************
 * @brief           CheckFault
 * @brief           
 * @return          N/A
 * @note            
 *******************************************************************/
void CheckFault(void) {
    if (FaultValue != 0) {   ;
    Saftey_Relay_Set = 1;
    //TODO Need Delay
    Saftey_Relay_Set=0;
    }
    FaultValueHistory=FaultValue;
    FaultValue=0;
    while(1){
    ;}
}
int Get_Sample_Num()
{
return Sample_Numbers;
}

void readc(){

}
