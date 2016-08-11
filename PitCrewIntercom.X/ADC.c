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

/*
 #define ACQ_US_DELAY 5


void ADC_Initialize(void)
{
    // set the ADC to the options selected in the User Interface
    
    // GO_nDONE stop; ADON enabled; CHS AN0; 
    ADCON0 = 0x01;
    
    // ADFM left; ADNREF VSS; ADPREF VDD; ADCS FOSC/4; 
    ADCON1 = 0x40;
    
    // ADRESL 0; 
    ADRESL = 0x00;
    
    // ADRESH 0; 
    ADRESH = 0x00;
    
    // Enabling ADC interrupt.
    PIE1bits.ADIE = 1;
}

void ADC_StartConversion(adc_channel_t channel)
{
    // select the A/D channel
    ADCON0bits.CHS = channel;    
    // Turn on the ADC module
    ADCON0bits.ADON = 1;

    // Acquisition time delay
    __delay_us(ACQ_US_DELAY);

    // Start the conversion
    ADCON0bits.GO_nDONE = 1;
    
}

bool ADC_IsConversionDone()
{
    // Start the conversion
    return (!ADCON0bits.GO_nDONE);
}

adc_result_t ADC_GetConversionResult(void)
{
    // Conversion finished, return the result
    return ((ADRESH << 8) + ADRESL);
}

adc_result_t ADC_GetConversion(adc_channel_t channel)
{
    // select the A/D channel
    ADCON0bits.CHS = channel;    

    // Turn on the ADC module
    ADCON0bits.ADON = 1;

    // Acquisition time delay
    __delay_us(ACQ_US_DELAY);

    // Start the conversion
    ADCON0bits.GO_nDONE = 1;

    // Wait for the conversion to finish
    while (ADCON0bits.GO_nDONE)
    {
    }
    
    // Conversion finished, return the result
    return ((ADRESH << 8) + ADRESL);
}

void ADC_ISR(void)
{
    // Clear the ADC interrupt flag
    PIR1bits.ADIF = 0;
}
 
 */