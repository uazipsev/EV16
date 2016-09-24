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
    
#define COMM_TIMER_MAX_TIME 100

#define SASTIMER 1
#define DDSTIMER 2
#define MCSTIMER 3
#define PDUTIMER 4
#define BMMTIMER 5
#define DEBUGTIME 6
#define SSTIMER 8
#define TIME 7

#define TALKTIME 9
#define TALKTIME1 10
#define DELTATIMER 11

#endif	/* TIMERS_H */

