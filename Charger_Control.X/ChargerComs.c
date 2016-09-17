/*******************************************************************
 * @brief           Charger Read / Write
 * @brief           
 * @return          
 * @note            
 *******************************************************************/
#include "ChargerComs.h"
#include "UART.h"
#include "Functions.h"
#include <string.h>
#include <stdlib.h>

char ChargerData[40];

int Duty = 0;
int Current = 0;
int VoltOut = 0;
int HeatsinkTemp = 0;
int Charge = 0;

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
 * @brief           ReadCharger
 * @brief           Reads Charger Data
 * @return          N/A
 * @note            Uses the USART to read stateus 
 *******************************************************************/

//19200bps, 8N1 comunication for the charger
//Charger String back is 'M,D001,C000,V001,T000,O000,SsssE'
void ReadCharger(){
    char str[4];
    char VarCount = 0;
    //Set MUX in Charger Direction
    SetMux(1); 
    if(Receive_available() > 45){
        while(Receive_available() && (Receive_get() != 'M'));
        if((Receive_get() == ',') && (VarCount == 0)){
            Receive_get();
            str[0] = Receive_get();
            str[1] = Receive_get();
            str[2] = Receive_get();
            VarCount++;
            Duty = atoi(str);
        }
        if((Receive_get() == ',') && (VarCount == 1)){
            Receive_get();
            str[0] = Receive_get();
            str[1] = Receive_get();
            str[2] = Receive_get();
            VarCount++;
            Current = atoi(str);
        }
        if((Receive_get() == ',') && (VarCount == 2)){
            Receive_get();
            str[0] = Receive_get();
            str[1] = Receive_get();
            str[2] = Receive_get();
            VarCount++;
            VoltOut = atoi(str);
        }
        if((Receive_get() == ',') && (VarCount == 3)){
            Receive_get();
            str[0] = Receive_get();
            str[1] = Receive_get();
            str[2] = Receive_get();
            VarCount++;
            HeatsinkTemp = atoi(str);
        }
        if((Receive_get() == ',') && (VarCount == 4)){
            Receive_get();
            str[0] = Receive_get();
            str[1] = Receive_get();
            str[2] = Receive_get();
            VarCount++;
            Charge = atoi(str);
        }
        if(VarCount == 0){
            //USART flush
        }
    }
}