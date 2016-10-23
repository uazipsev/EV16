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

    extern volatile int receiveArray[100];
    extern void RS485_Direction2(int T_L);
    bool requestBMMData();
    bool receiveCommBMM();
    int GetTemp(unsigned char num);
    int GetVolt(unsigned char num);
    int GetCurrent(unsigned char num);
    void ClearBMMTalk();
    
#endif	/* BMMCOMMS_H */

