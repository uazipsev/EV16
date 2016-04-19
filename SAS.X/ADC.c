#include "ADC.h"
#include <xc.h>
#include <math.h>

void initADC(void) {
    AD1CON1 = AD1CON1 & 0X0000;
    AD1CON2 = AD1CON1 & 0X0000;
    AD1CON3 = AD1CON1 & 0X0000;
    AD1CON4 = AD1CON1 & 0X0000;
    AD1CON1bits.ADSIDL = 0; //ADC on during idle
    AD1CON1bits.FORM = 0; // Data Output Format: unsigned Integer
    AD1CON1bits.SSRC = 7; // Sample Clock Source: Internal Timer
    AD1CON1bits.AD12B = 1; // 12-bit ADC operation
    AD1CON1bits.SIMSAM = 0; // Samples multiple channels individually in sequence
    AD1CON2bits.VCFG = 7; //Voltage Reference is AVss AVdd
    AD1CON2bits.BUFM = 0; //Buffer Indicator (ping pong)
    //AD1CON2bits.CSCNA = 1;    // Scan Input Selections for CH0+ during Sample A bit
    AD1CON2bits.CHPS = 0; // Converts CH0
    AD1CON3bits.ADRC = 0; // ADC Clock is derived from Systems Clock = 0 /Internal RC =1
    AD1CON3bits.ADCS = 63; // ADC Conversion Clock
    //AD1CON3bits.SAMC = 31;      // ADC Sample Time Internal RC
    //AD1CHS0: A/D Input Select Register
    AD1CHS0bits.CH0SA = 0; // MUXA +ve input selection (AIN0) for CH0
    AD1CHS0bits.CH0NA = 0; // MUXA -ve input selection (Vref-) for CH0


    AD1CON2bits.SMPI = 0; /*  The SMPI bits select the number of acquisition/conversion sequences that would be
                                 *  performed before an interrupt occurs. This can vary from 1 sample per interrupt
                                 *  to 16 samples per interrupt.*/

    AD1PCFGL = 0XFFC0; //'ANALOG INPUT SELECT       0000 0000 0011 1111
    AD1CHS0 = 0X0000; //'SH CHANNEL 0                          0000 0000 0000 0000

    AD1CSSL = 0x003F;

    //AD1CON1bits.ASAM = 1;

    IFS0bits.AD1IF = 0;
    IEC0bits.AD1IE = 1;

    AD1CON1bits.ADON = 1;
    AD1CON1bits.DONE = 0;
    AD1CON1bits.SAMP = 1;
}

int ADC = 0;
int ADCPorts[3] = {0, 1, 4};

void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void) {
    if (!ADCDataReady) {
        ADCbuffer[ADC] = ADC1BUF0;
        ADC++;
        //IEC0bits.AD1IE = 0;
    }
    if (ADC > 2) {
        ADCTime = 0;
        ADCDataReady = 1;
        ADC = 0;
        IEC0bits.AD1IE = 0;
    }
    AD1CHS0bits.CH0SA = ADCPorts[ADC];
    AD1CON1bits.SAMP = 1;
    IFS0bits.AD1IF = 0; // clear ADC interrupt flag
}

void GetADC(void) {

}

void SetADC(void) {

}

void handleADCValues() {
    throttle1 = ((throttle1 * 3) + (1-ADCbuffer[0]) * throttle1);
    throttle2 = ((throttle2 * 3) + (1-ADCbuffer[1]) * throttle2);
    brake = ((brake * 3) + (1-ADCbuffer[2]) * brake);
    throttle1 = throttle1 * 0.02;
    throttle1 = throttle2 * 0.02;
    brake = brake * 0.02;
}
