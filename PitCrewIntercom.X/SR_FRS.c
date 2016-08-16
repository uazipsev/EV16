#include "SR_FRS.h"
#include "PinDef.h"
#include <xc.h>
#include <stdio.h>
#include "Function.H"

#define FrequencyHigh 140
#define FrequencyLow 050

void SR_FRSTalk(void){
    RadioPushTT ^= 1;
}

void SR_FRSPowerDown(void){
    RadioPower ^= 1;
}

void SR_FRSStart(void){
    SR_FRSPowerDown();
    Delay(500);
    SetCommandMode();
    Delay(1000);
    //Setup FRQ
    SetFrequency();
    Delay(1000);
    //Shutdown power Save
    SetPowerSave();
    Delay(1000);
    //Set SPR amp @ 5
    SetVolume(5);
    Delay(1000);
    //disable VOX
    SetVOX(0);
    Delay(1000);
    //Set MIC amp @ 5, disable scramble
    SetMIC(8,0);
}

void SetCommandMode(void){
    printf("\r\n");
    printf("AT+DMOCONNECT");
    printf("\r\n");
}

void SetFrequency(void){
    printf("\r\n");
    printf("AT+DMOSETGROUP=0,145.5500,145.5500,43,8,51,0");//,0,RXCX,SQ,TXCX,0);
    printf("\r\n");
}

void SetPowerSave(void){
    //We are controlling that directly, so turn feature off
    printf("\r\n");
    printf("AT+DMOAUTOPOWCONTR=%c",1);
    printf("\r\n");
}

void SetVolume(char volume){
    if((volume < 9) && (volume > 1)){
        printf("\r\n");
        printf("AT+DMOSETVOLUME=%c",volume);
        printf("\r\n");
    }
}

void SetVOX(int volume){
    if((volume < 8) && (volume >= 0)){
        printf("\r\n");
        printf("AT+DMOSETVOX=%c",volume);
        printf("\r\n");
    }
}

void SetMIC(char volume, char scram){
        printf("\r\n");
        printf("AT+DMOSETMIC=%c,%c,0",volume,scram);
        printf("\r\n");
}