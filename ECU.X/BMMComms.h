/* 
 * File:   BMMComms.h
 * Author: User
 *
 * Created on June 7, 2015, 7:38 PM
 */

#ifndef BMMCOMMS_H
#define	BMMCOMMS_H

#include "ADDRESSING.h"
#include <stdbool.h>


    extern volatile unsigned int BMMTimer;
    extern void sendData(unsigned char whereToSend);
    extern bool receiveData();
    extern void ToSend(const unsigned char where, const unsigned int what);
    extern volatile int receiveArray[100];
    extern void RS485_Direction2(int T_L);

#endif	/* BMMCOMMS_H */

