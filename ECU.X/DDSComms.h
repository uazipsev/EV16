/* 
 * File:   DDSComms.h
 * Author: User
 *
 * Created on June 7, 2015, 7:35 PM
 */

#ifndef DDSCOMMS_H
#define	DDSCOMMS_H

#include "ADDRESSING.h"
#include <stdbool.h>

////#define START_BUTTON 0
//#define START_LED  1
//#define DASH_LED2  0

int seekButtonChange();
void changeLEDState(int LED, int state);
int GetDDSerrorCounter();
bool receiveCommDDS();
bool requestDDSData();
void SetUpDDSIO();
void ClearDDSTalk();

#endif	/* DDSCOMMS_H */

