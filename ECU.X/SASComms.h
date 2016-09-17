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



#define GETSAST1RAW 6
#define GETSAST2RAW 7
#define GETSASB1RAW 8
#define GETSASB2RAW 9

bool CheckThrotleConsistency();
void SetBrakeValue(int val);
void SetThrottleValue(int val);

bool receiveCommSAS();
bool requestSASData();
unsigned int GetSASRaw(char request);

#endif	/* SASCOMMS_H */

