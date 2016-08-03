#include "Functions.h"
#include "xc.h"
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include "mcc_generated_files/tmr0.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "Communications.h"
//Function used to make a varable delay
//We use this because the provided fcn dosn't accept large bounds

char ChargerData[40];

bool PowerOn = 0;

void Delay(int wait) {
    int i = 0;
    for (; wait > i; i++) {
        __delay_ms(1); // function provided by xc compiler
    }
}

/*******************************************************************
 * @brief           AIR control
 * @brief           Set's AIR in the Precharge / discharge control 
 * @return          N/A
 * @note            Blocking calls
 *******************************************************************/

void Precharge(bool OnOff){
    if(OnOff){
        //YELLOW_SetHigh();
        PRE_BOTTOM_AIR_SetHigh();
        for(int i = 0;i<5;i++){
            Delay(1000);
        }
        TOP_AIR_SetHigh();
        BLUE_SetHigh();
        CHARGER_POWER_SetHigh();
        PowerOn = 0;
    }
        
    else{
        TOP_AIR_SetLow();
        PRE_BOTTOM_AIR_SetLow();
        BLUE_SetLow();
        for(int i = 0;i<5;i++){
            Delay(1000);
        }
        //YELLOW_SetLow();
        CHARGER_POWER_SetLow();
        PowerOn = 1;
    }
}

/*******************************************************************
 * @brief           Charger Control
 * @brief           Updates the charger to control
 * @return          N/A
 * @note            Uses the USART to send out data to configure charger
 *******************************************************************/

//19200bps, 8N1 comunication for the charger

void SetCharger(char mode, int Current, int Voltage){
    char str[10];
    if(mode == 1){
        //Set MUX in Charger Direction
        SetMux(1);
        //set charger to off
        //'M,001,000,001,E'
        sprintf(str, "M,");
        strcpy(ChargerData, str);
        printf("%s",ChargerData);
        sprintf(str, "%03d,", 001);
        strcpy(ChargerData, str);
        printf("%s",ChargerData);
        sprintf(str, "%03d,", 000);
        strcpy(ChargerData, str);
        printf("%s",ChargerData);
        //calculate "CRC"
        sprintf(str, "%03d,E\n", (001 + 000)%1000);
        strcpy(ChargerData, str);
        //Send data to device
        printf("%s",ChargerData);
    }
    if(mode == 2){
        //Set MUX in Charger Direction
        SetMux(1);
        //Load values
        sprintf(str, "M,");
        strcpy(ChargerData, str);
        printf("%s",ChargerData);
        sprintf(str, "%03d,", Current);
        strcpy(ChargerData, str);
        printf("%s",ChargerData);
        sprintf(str, "%03d,", Voltage);
        strcpy(ChargerData, str);
        printf("%s",ChargerData);
        //calculate "CRC"
        sprintf(str, "%03d,E\n", (Current + Voltage)%1000);
        strcpy(ChargerData, str);
        //Send data to device
        printf("%s",ChargerData);
    }
}

/*******************************************************************
 * @brief           MUX Control
 * @brief           Controls serial mux
 * @return          N/A
 * @note            Sets Serial channel the pic is talking to on the back end.
 *******************************************************************/

void SetMux(char channel){
    switch (channel){
        case 1:
            MUX_S0_SetLow();
            MUX_S1_SetLow();
            break;
        case 2:
            MUX_S0_SetHigh();
            MUX_S1_SetLow();
            break;
        case 3:
            MUX_S0_SetLow();
            MUX_S1_SetHigh();
            break;
        case 4:
            MUX_S0_SetHigh();
            MUX_S1_SetHigh();
            break;
        default:
            //do nothing
            break;
    }
}

/*******************************************************************
 * @brief           Active LED control
 * @brief           Controls LED and watch dog
 * @return          N/A
 * @note            We are going to use this to toggle LED and watchdog
 *******************************************************************/

 void ledDebug() {
        if (time_get(LEDTM) > 4) {
            //LED_Toggle();
            updateComms();
            time_Set(LEDTM, 0);
            respondChargerAsECU();
        }
    }
 
 bool GetPowerState(){
     return PowerOn;
 }
 
 /*******************************************************************
 * @brief           Horn
 * @brief           Turns the horn on for a time lenth
 * @return          N/A
 * @note            buzzer ation
 *******************************************************************/
 
 void Horn(int time){
     HORN_SetHigh();
     Delay(time);
     HORN_SetLow();
 }