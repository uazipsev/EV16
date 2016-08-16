/* 
 * File:   Communications.h
 * Author: User
 *
 * Created on June 7, 2015, 5:50 PM
 */

#ifndef COMMUNICATIONS_H
#define	COMMUNICATIONS_H

#include <xc.h>
#include <stdbool.h>
#include "PinDef.h"
#include "ADDRESSING.h"


    extern void sendData(unsigned char whereToSend);
    extern bool receiveData();
    extern void ToSend(const unsigned char where, const unsigned int what);
    extern volatile int receiveArray[20];
    extern bool Transmit_stall;
    extern volatile unsigned int talkTime, safetyTime;
    void updateComms();
    void checkCommDirection();
    void respondECU();

#endif	/* COMMUNICATIONS_H */

