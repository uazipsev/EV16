/* 
 * File:   interrupt_handler.h
 * Author: Igor
 *
 * Created on March 28, 2015, 11:36 AM
 */

#ifndef INTERRUPT_HANDLER_H
#define	INTERRUPT_HANDLER_H
bool PrepSend;
volatile unsigned int LEDtime = 0, talkTime = 0;
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void);
#endif	/* INTERRUPT_HANDLER_H */

