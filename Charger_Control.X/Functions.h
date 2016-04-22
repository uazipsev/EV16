/* 
 * File:   Functions.h
 * Author: Rick
 *
 * Created on May 11, 2015, 2:42 AM
 */

#include <stdbool.h>

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

extern void Delay(long int wait);
void Precharge(bool OnOff);
void SetCharger(char mode, char Current, char Voltage);
void SetMux(char channel);

#endif	/* FUNCTIONS_H */

