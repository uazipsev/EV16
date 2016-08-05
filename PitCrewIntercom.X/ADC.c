#include "ADC.h"
#include <xc.h>

void ADC_Initialize(){
    FVRCONbits.ADFVR0 = 1; //vref
    FVRCONbits.ADFVR1 = 1;
    ADCON1bits.ADFM = 1;
    ADCON1bits.ADCS0 = 0; //Selecting the clk division factor = FOSC/4
    ADCON1bits.ADCS1 = 0;
    ADCON1bits.ADCS2 = 1;
    ADCON0bits.ADON = 1; //Turns on ADC module
}

int ReadVoltage(char ch){
    SetADCChannel(ch);
    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_nDONE);
    return ((ADRESL << 8) + ADRESL);
}

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

