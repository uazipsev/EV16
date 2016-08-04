/* 
 * File:   Timer.h
 * Author: Rick
 *
 * Created on May 26, 2016, 12:37 AM
 */

#ifndef TIMER_H
#define	TIMER_H

void TMR2_Initialize(void);
void TMR2_StartTimer(void);
void TMR2_StopTimer(void);
void TMR2_ISR(void);
void TMR2_CallBack(void);
void TMR2_CallBack(void); 

void setLED(int); //Custom Function to set which LEDs are blinking.
void Off_Led(int); //Custom Function to turn off which LEDs that were blinking.
void Change_Blink_Rate(char time); //Custom Function to change time of clock.
void Change_LED(char lit);
//void TMR2_SetInterruptHandler(void *InterruptHandler);
//
//void (*TMR2_InterruptHandler)(void);
//void TMR2_DefaultInterruptHandler(void);

#endif	/* TIMER_H */

