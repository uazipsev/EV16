#include "Radio.h"
#include "SR_FRS.h"
#include "PinDef.h"
#include <xc.h>
#include <stdbool.h>
#include "Timer.h"
#include "ADC.h"
#include "Function.H"

#define TALKBUTTONWAIT 100
#define LISTENBUTTONWAIT 50
#define POWERDOWN 100

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
    if(Talking && PushToTalk){
        count--;
        if(count < LISTENBUTTONWAIT){
            LED_Red = 1;
            SR_FRSTalk();
            TMR2_StartTimer();
            count = 0;
        }
    }
    if((count > TALKBUTTONWAIT) && !Talking){
        SR_FRSTalk();
        LED_Red = 0;
        Talking = true;
        TMR2_StopTimer();
        ClearTicker();
    }
    if(GetTicker() > POWERDOWN){
        //SHUT DOWN DEVICE 
        SR_FRSPowerDown();
        LED_Red = 0;
    }
    if(time > 150){
        LED_Green = 0;
        Battery = ReadVoltage(BATT);
        Battery = (Battery*5.0)/1023.0;
        time = 0;
        Mode = ReadCharger();
    }
    if((time > 2) && (LED_Green == 0)){
        LED_Green = 1;
    }
    if(Battery < 6.2){
        SR_FRSPowerDown();
        LED_Red = 0;
    }
    time++;
}
