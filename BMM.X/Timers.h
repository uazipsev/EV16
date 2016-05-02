/* 
 * File:   Timers.h
 * Author: User
 *
 * Created on June 3, 2015, 8:03 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H

#include <stdbool.h>
#include <xc.h>
#include "PinDef.h"

#define LEDTM 1
#define SLVTM 2
#define TLKTM 3
#define ADCTM 4

    void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void);
    void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);

    void initTimerTwo(void);
    void initTimerOne(void);
    int time_get(char WhatTime);
    void updateTimers();
    void TalkTimeSet(int value);

#endif	/* TIMERS_H */

