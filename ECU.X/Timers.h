/* 
 * File:   Timers.h
 * Author: User
 *
 * Created on May 31, 2015, 3:12 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H

void initTimerOne();
int GetTime(char data);
void SetTime(char data);
void TimeOutSet(int num);
    
#define COMM_TIMER_MAX_TIME 75

#define SASTimer 1
#define DDSTimer 2
#define MCSTimer 3
#define PDUTimer 4
#define BMMTimer 5
#define DebugTime 6

#endif	/* TIMERS_H */

