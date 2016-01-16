/* 
 * File:   ADC.h
 * Author: Rick
 *
 * Created on May 19, 2015, 2:11 AM
 */

#ifndef ADC_H
#define	ADC_H
#include <stdbool.h>
void initADC(void);
void GetADC(void);
void SetADC(void);

void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void);
volatile unsigned int ADCTime = 0;
volatile bool ADCSamp = true;
volatile unsigned int ADCbuffer[6];
volatile bool ADCDataReady = false;
void handleADCValues();
extern volatile unsigned int ADCbuffer[6];
float throttle1, throttle2, brake;
#endif	/* ADC_H */

