/* 
 * File:   Timer.h
 * Author: Rick
 *
 * Created on May 26, 2016, 12:37 AM
 */

#ifndef TIMER_H
#define	TIMER_H

unsigned int GetTicker(void);
void ClearTicker(void);

void TMR2_Initialize(void);
void TMR2_StartTimer(void);
void TMR2_StopTimer(void);
void TMR2_ISR(void);

#endif	/* TIMER_H */

