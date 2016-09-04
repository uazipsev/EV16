/* 
 * File:   Timers.h
 * Author: User
 *
 * Created on June 7, 2015, 5:52 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H

void TimerOneInit(void);
int GetTime(char number);
void ClearTime(char number);

#define LEDTIME 1
#define SAFETYTIME 2
#define TALKTIME 3
#define BOOTTIME 4

#endif	/* TIMERS_H */

