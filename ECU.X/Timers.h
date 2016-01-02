/* 
 * File:   Timers.h
 * Author: User
 *
 * Created on May 31, 2015, 3:12 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H

#ifdef	__cplusplus
extern "C" {
#endif
    void initTimerOne();
#define COMM_TIMER_MAX_TIME 200
    volatile unsigned int SASTimer, DDSTimer, MCSTimer, PDUTimer, BMMTimer, BootTimer,DebugTimer;
    volatile unsigned int time;

    volatile unsigned int talkTime;
    volatile unsigned int talkTime1;
    volatile unsigned int talkTime2;
    volatile unsigned int talkTime3;


#ifdef	__cplusplus
}
#endif

#endif	/* TIMERS_H */

