/* 
 * File:   DDSComms.h
 * Author: User
 *
 * Created on June 7, 2015, 7:35 PM
 */

#ifndef DDSCOMMS_H
#define	DDSCOMMS_H

#ifdef	__cplusplus
extern "C" {
#endif


#include "ADDRESSING.h"
#include <stdbool.h>

extern int DDS_FAULT_CONDITION;


    extern volatile unsigned int DDSTimer;

    //DDS
    extern unsigned int indicators;
    extern unsigned int buttons;
    extern unsigned int throttle1, throttle2, brake;

    extern void sendData1(unsigned char whereToSend);
    extern bool receiveData1();
    extern void ToSend1(const unsigned char where, const unsigned int what);
    extern volatile int receiveArray1[20];

    extern void RS485_Direction1(int T_L);

#ifdef	__cplusplus
}
#endif

#endif	/* DDSCOMMS_H */

