/* 
 * File:   Function.H
 * Author: Rick
 *
 * Created on August 3, 2016, 10:53 AM
 */

#ifndef FUNCTION_H
#define	FUNCTION_H

#define _XTAL_FREQ 4000000 

#define CHARGING 1
#define DONE 2
#define OFF 0

void Start();
void INTERRUPT_Initialize();
void Delay(int wait);

#endif	/* FUNCTION_H */

