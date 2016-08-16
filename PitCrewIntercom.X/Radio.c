#include "Radio.h"
#include "SR_FRS.h"
#include "PinDef.h"
#include <xc.h>
#include <stdbool.h>
#include "Timer.h"
#include "ADC.h"
#include "Function.H"

#define TALKBUTTONWAIT 5
#define LISTENBUTTONWAIT 5
#define POWERDOWNTIME 100000

int time = 0;
int count = 0;
float Battery = 0;
char Mode = 0;
bool Talking = false;
bool Shutdown = false;

void RadioBegin(){
    SR_FRSStart();
}

void RadioOperation(){
    if(!PushToTalk && !Talking){
        count++;
    }
    if((count > TALKBUTTONWAIT) && !Talking){
        SR_FRSTalk();
        LED_Red = 1;
        Talking = true;
        //TMR2_StopTimer();
        ClearTicker();
    }
    if(Talking && PushToTalk){
        count--;
        if(count < LISTENBUTTONWAIT){
            LED_Red = 0;
            SR_FRSTalk();
            //TMR2_StartTimer();
            count = 0;
            Talking = false;
        }
    }
    if(Talking && !PushToTalk){
        count = TALKBUTTONWAIT;
    }
    if(GetTicker() > POWERDOWNTIME){
        //SHUT DOWN DEVICE 
        SR_FRSPowerDown();
        LED_Blue = 1;
    }
    if(time > 15){
        LED_Green = 1;
        Battery = ReadVoltage(BATT);
        Battery = (Battery*5.0)/1023.0;
        time = 0;
        Mode = ReadCharger();
    }
    if((time > 1) && (LED_Green == 1)){
        LED_Green = 0;
    }
    if(Battery < 6.2){
        //SR_FRSPowerDown();
        //LED_Red = 0;
    }
    if(ReadCharger() == CHARGING){
        //LED_Green = 1;
        LED_Blue = 1;
    }
    if(ReadCharger() == DONE){
        LED_Blue = 0;
        LED_Green = 1;
    }
    time++;
}
