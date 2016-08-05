/* 
 * File:   ADC.h
 * Author: Rick
 *
 * Created on August 4, 2016, 8:19 AM
 */

#ifndef ADC_H
#define	ADC_H

#define BATT 1
#define TEMP 2
#define MIC 3

void ADC_Initialize();
int ReadVoltage(char ch);
void SetADCChannel(char ch);

#endif	/* ADC_H */

