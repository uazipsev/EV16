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
    //SAS

#define GETSAST1 1
#define GETSAST2 2
#define GETSASB1 3
#define GETSASB2 4
#define GETSASBP 5

#define GETSAST1RAW 6
#define GETSAST2RAW 7
#define GETSASB1RAW 8
#define GETSASB2RAW 9

bool checkSASInputs(unsigned int t1, unsigned int t2, unsigned int b);
void SetBrakeValue(int val);
void SetThrottleValue(int val);
char GetSASFalts();
unsigned int GetSASValue(char request);
unsigned int GetSASRaw(char request);

#endif	/* SASCOMMS_H */

