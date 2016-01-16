/* 
 * File:   Timers.h
 * Author: User
 *
 * Created on June 7, 2015, 5:52 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H

    void timerTwo(void);
    void timerOne(void);
    extern volatile unsigned int talkTime, LEDtime,safetyTime,bootTime;
    int getLEDTime(void);
    void ClearLEDTime();
    void setLEDTime(int value);

#endif	/* TIMERS_H */

