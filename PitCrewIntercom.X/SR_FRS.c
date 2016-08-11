#include "SR_FRS.h"
#include "PinDef.h"
#include <xc.h>
#include <stdio.h>
#include "Function.H"

void SR_FRSTalk(void){
    RadioPushTT ^= 1;
}

void SR_FRSPowerDown(void){
    RadioPower ^= 1;
}

void SR_FRSStart(void){
    SetCommandMode();
    Delay(100);
    //Setup FRQ
    SetFrequency();
    Delay(100);
    //Shutdown power Save
    SetPowerSave();
    Delay(100);
    //Set SPR amp @ 5
    SetVolume(5);
    Delay(100);
    //disable VOX
    SetVOX(0);
    Delay(100);
    //Set MIC amp @ 5, disable scramble
    SetMIC(5,0);
}

void SetCommandMode(void){
    printf("AT+DMOCONNECT");
}

void SetFrequency(void){
    printf("AT+DMOSETGROUP=%d,%f,%f,%d,%d,%d,%d",0,TXFrequency,RXFrequency,RXCX,SQ,TXCX,0);
}

void SetPowerSave(void){
    //We are controlling that directly, so turn feature off
    printf("AT+DMOAUTOPOWCONTR=%c",1);
}

void SetVolume(char volume){
    if((volume < 9) && (volume > 1)){
        printf("AT+DMOSETVOLUME=%c",volume);
    }
}

void SetVOX(int volume){
    if((volume < 8) && (volume >= 0)){
        printf("AT+DMOSETVOLUME=%c",volume);
    }
}

void SetMIC(char volume, char scram){
    if((volume < 8) && (volume > 0)){
        printf("AT+DMOSETMIC=%c,%c,%c",volume,scram,0);
    }
}