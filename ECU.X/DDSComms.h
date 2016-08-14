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

extern unsigned int throttle1, throttle2, brake;

extern void RS485_Direction1(int T_L);
int seekButtonChange();
void changeLEDState(int LED, int state);
int GetDDSerrorCounter();

#endif	/* DDSCOMMS_H */

