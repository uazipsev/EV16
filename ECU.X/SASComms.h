/* 
 * File:   SASComms.h
 * Author: User
 *
 * Created on June 7, 2015, 7:35 PM
 */

#ifndef SASCOMMS_H
#define	SASCOMMS_H


#include "ADDRESSING.h"
#include <stdbool.h>

//#define TRIP_THROTTLE 40
//#define TRIP_BRAKE    40


extern int SAS_FAULT_CONDITION;
    //SAS

//    extern void sendData1(unsigned char whereToSend);
//    extern bool receiveData1();
//    extern void ToSend1(const unsigned char where, const unsigned int what);
    extern volatile int receiveArray1[20];

   // extern void RS485_Direction1(int T_L);
    bool checkSASInputs(unsigned int t1, unsigned int t2, unsigned int b);
    void SetBrakeValue(int val);
    void SetThrottleValue(int val);


#endif	/* SASCOMMS_H */

