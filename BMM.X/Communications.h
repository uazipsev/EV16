/* 
 * File:   Communications.h
 * Author: User
 *
 * Created on June 3, 2015, 9:14 PM
 */

#ifndef COMMUNICATIONS_H
#define	COMMUNICATIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <xc.h>
#include "ADDRESSING.h"

#define RS485_Port LATBbits.LATB13
#define TALK 1
#define LISTEN 0
    extern volatile unsigned int talkTime;
    extern void sendData(unsigned char whereToSend);
    extern bool receiveData();
    extern void ToSend(const unsigned char where, const unsigned int what);
    extern volatile int receiveArray[100];
    void updateComms();
    void checkCommDirection();
    extern bool Transmit_stall;
    bool pendingSend = false;
    void populateBatteryT(int slave);
    void populateBatteryV(int slave);


#ifdef	__cplusplus
}
#endif

#endif	/* COMMUNICATIONS_H */

