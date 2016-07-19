
/*******************************************************************
 * @brief           CarSense.c
 * @brief           Convert the temp sensor ADC to EU
 * @return          EU
 * @note            The lib is writen for x sensor (Link here)
 *******************************************************************/

#include "mcc_generated_files/adc.h"
#include "CarTempSens.h"

#define DATASIZE 10

char TempData[DATASIZE] = 0;
int TempOne = 0;
int TempTwo = 0;

/*******************************************************************
 * @brief           TempInit
 * @brief           Setup sensor
 * @return          none
 * @note            
 *******************************************************************/

void TempInit() {
    //StartADC 
    ADC_Initialize();
    int i = 0;
    for(;i<DATASIZE;i++){
        TempData[i]=0;
    }
}

/*******************************************************************
 * @brief           TempCalc
 * @brief           Gets ADC counts - converts
 * @return          if wrong channel selected
 * @note            Get ADC then convert
 *******************************************************************/

void TempCalc(int x){
    if(x == 1){
        TempOne = ADC_GetConversion(Temp1)/12;
    }
    if(x == 2){
        TempTwo = ADC_GetConversion(Temp2)/12;
    }
    //else
        //return 0;  
}

/*******************************************************************
 * @brief           TempGet
 * @brief           Gets Temp value
 * @return          temp value in EU 
 * @note            
 *******************************************************************/

int TempGet(int x){
    if(x == 1){
        return TempOne;
    }
    if(x == 2){
        return TempTwo;
    }
    else
        return 0;
}