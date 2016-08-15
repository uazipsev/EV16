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

//#define START_BUTTON 0
#define START_LED  0
#define DASH_LED2  1

int seekButtonChange();
void changeLEDState(int LED, int state);
int GetDDSerrorCounter();
bool receiveCommDDS();
bool requestDDSData();

#endif	/* DDSCOMMS_H */

