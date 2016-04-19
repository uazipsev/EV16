/* 
 * File:   Communications.h
 * Author: User
 *
 * Created on June 6, 2015, 8:08 PM
 */

#ifndef COMMUNICATIONS_H
#define	COMMUNICATIONS_H

#include <xc.h>
#include <stdbool.h>
#include "PinDef.h"
#include "ADDRESSING.h"


extern bool Transmit_stall;
extern float throttle1, throttle2, brake;
extern volatile unsigned int talkTime;
void updateComms();
void prepAndSendData();
void checkCommDirection();
#endif	/* COMMUNICATIONS_H */

