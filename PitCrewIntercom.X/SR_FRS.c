/*******************************************************************
 * @brief           SR_FRS.c
 * @brief           Controls modem
 * @return          N/A
 * @note            These fcn's where written for the SR_FRS modem
 *******************************************************************/
#include "SR_FRS.h"
#include "PinDef.h"
#include <xc.h>
#include <stdio.h>
#include "Function.H"

#define FrequencyHigh 140
#define FrequencyLow 050

/*******************************************************************
 * @brief           SR_FRSTalk
 * @brief           Setts PTT mode
 * @return          none
 * @note            toggles pin
 *******************************************************************/
void SR_FRSTalk(void){
    RadioPushTT ^= 1;  //togles radio PPT
}

/*******************************************************************
 * @brief           SR_FRSPowerDown
 * @brief           Sets power down mode
 * @return          none
 * @note            toggles pin
 *******************************************************************/
void SR_FRSPowerDown(void){
    RadioPower ^= 1;  //Toggles radio power down
}

/*******************************************************************
 * @brief           SR_FRSStart
 * @brief           Setup SR_FRS
 * @return          none
 * @note            Uses AT commands to set modem up
 *******************************************************************/
void SR_FRSStart(void){
    SR_FRSPowerDown();  //Turn on radio
    Delay(500);         //wait 1/2 sec
    SetCommandMode();   //Tell modem to get ready for AT mode
    Delay(1000);        //wait a second
    SetFrequency();     //Setup FRQ
    Delay(1000);        //wait a second
    SetPowerSave();     //Shutdown power Save
    Delay(1000);        //wait a second
    SetVolume(7);       //Set SPR amp @ 5
    Delay(1000);        //wait a second
    SetVOX(0);          //disable VOX
    Delay(1000);        //wait a second
    SetMIC(8,0);        //Set MIC amp @ 5, disable scramble
}

/*******************************************************************
 * @brief           SetCommandMode
 * @brief           Sends AT wakeup command
 * @return          none
 * @note            printf the command over UART
 *******************************************************************/
void SetCommandMode(void){
    printf("\r\n");
    printf("AT+DMOCONNECT");
    printf("\r\n");
}

/*******************************************************************
 * @brief           SetFrequency
 * @brief           Send frequncy and group id to device. 
 * @return          none
 * @note            printf the command over UART
 *******************************************************************/
void SetFrequency(void){
    printf("\r\n");
    printf("AT+DMOSETGROUP=0,145.5500,145.5500,0,1,0,0");//,0,RXCX,SQ,TXCX,0);
    printf("\r\n");
}

/*******************************************************************
 * @brief           SetPowerSave
 * @brief           Tells modem to disable power save
 * @return          none
 * @note            printf the command over UART
 *******************************************************************/
void SetPowerSave(void){
    //We are controlling that directly, so turn feature off
    printf("\r\n");
    printf("AT+DMOAUTOPOWCONTR=%c",1);
    printf("\r\n");
}

/*******************************************************************
 * @brief           SetVolume
 * @brief           passes audio volume
 * @return          none
 * @note            printf the command over UART
 *******************************************************************/
void SetVolume(char volume){
    if((volume < 9) && (volume > 1)){
        printf("\r\n");
        printf("AT+DMOSETVOLUME=%c",volume);
        printf("\r\n");
    }
}

/*******************************************************************
 * @brief           SetVOX
 * @brief           passes VOX sensitivity
 * @return          none
 * @note            printf the command over UART
 *******************************************************************/
void SetVOX(int volume){
    if((volume < 8) && (volume >= 0)){
        printf("\r\n");
        printf("AT+DMOSETVOX=%c",volume);
        printf("\r\n");
    }
}

/*******************************************************************
 * @brief           SetMIC
 * @brief           passes MIC amp and scram level
 * @return          none
 * @note            printf the command over UART
 *******************************************************************/
void SetMIC(char volume, char scram){
        printf("\r\n");
        printf("AT+DMOSETMIC=%c,%c,0",volume,scram);
        printf("\r\n");
}