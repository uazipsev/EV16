#include "Radio.h"
#include "SR_FRS.h"
#include "PinDef1.h"
#include <xc.h>
#include <stdbool.h>

#define BUTTONWAIT 100
int count = 0;
bool Talking;

void RadioBegin(){
    SR_FRSStart();
}

void RadioOperation(){
    if(PushToTalk){
        count++;
    }
    else{
        count = 0;
        if(Talking){
            LED_Red = 1;
            SR_FRSTalk();
        }
    }
    if(count > BUTTONWAIT){
        SR_FRSTalk();
        LED_Red = 0;
        Talking = true;
    }
}
