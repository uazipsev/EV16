/*******************************************************************
 * @brief           ADC.c
 * @brief           Runs and reports back ADC vales
 * @return          N/A
 * @note            
 *******************************************************************/
#include "ADC.h"
#include <xc.h>

/*******************************************************************
 * @brief           ADC_Initialize
 * @brief           Strtup ADC
 * @return          none
 * @note            
 *******************************************************************/
void ADC_Initialize(){
    FVRCONbits.ADFVR0 = 1; //vref
    FVRCONbits.ADFVR1 = 1;
    ADCON1bits.ADFM = 1;
    ADCON1bits.ADCS0 = 0; //Selecting the clk division factor = FOSC/4
    ADCON1bits.ADCS1 = 0;
    ADCON1bits.ADCS2 = 1;
    ADCON0bits.ADON = 1; //Turns on ADC module
}

/*******************************************************************
 * @brief           ReadVoltage
 * @brief           reads ADC value
 * @return          int - ADC value
 * @note            Blocking call
 *******************************************************************/
int ReadVoltage(char ch){
    SetADCChannel(ch);
    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_nDONE);
    return ((ADRESL << 8) + ADRESL);
}

/*******************************************************************
 * @brief           SetADCChannel
 * @brief           sets channel for ADC
 * @return          N/A
 * @note            
 *******************************************************************/
void SetADCChannel(char ch){
    if(ch == BATT){
        ADCON0bits.CHS = 6;
    }
    else if(ch == TEMP){
        ADCON0bits.CHS = 29;
    }
    else if(ch == MIC){
        ADCON0bits.CHS = 3;
    }
}