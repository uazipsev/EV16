/* 
 * File:   LED.h
 * Author: Rick
 *
 * Created on May 18, 2015, 11:54 PM
 */

#ifndef LED_H
#define	LED_H

extern void SetLEDOut(int lednum, int state);
extern void ReadButtonState(int btnnum);
extern bool GetButtonState(int btnnum);

#endif	/* LED_H */

