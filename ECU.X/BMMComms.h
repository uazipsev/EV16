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
    bool requestBMMData(char state);
    bool receiveCommBMM(char state);
    int GetTemp(char num);
    int GetVolt(char num);
    int GetCurrent(char num);
    
#endif	/* BMMCOMMS_H */

