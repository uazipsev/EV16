/* 
 * File:   Functions.h
 * Author: Rick
 *
 * Created on May 11, 2015, 2:42 AM
 */

#include <stdbool.h>

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

void Delay(int wait);
void Precharge(bool OnOff);
void SetCharger(char mode, int Current, int Voltage);
void SetMux(char channel);
void ledDebug();
bool GetPowerState();
void Horn(int time);

#endif	/* FUNCTIONS_H */

