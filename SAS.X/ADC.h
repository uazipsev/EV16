/* 
 * File:   ADC.h
 * Author: Rick
 *
 * Created on May 19, 2015, 2:11 AM
 */

#ifndef ADC_H
#define	ADC_H

typedef enum{
    Throttle1,
    Throttle2,
    Brake1,
    Brake2
}value;



void initADC(void);
void FilterADC();
float GetADC(value RequestValue);


#endif	/* ADC_H */

