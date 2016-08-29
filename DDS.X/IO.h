/* 
 * File:   LED.h
 * Author: Rick
 *
 * Created on May 18, 2015, 11:54 PM
 */

#ifndef LED_H
#define	LED_H

void SetLEDOut(int lednum, int state);
void ReadButtonState(int btnnum);
bool GetButtonState(int btnnum);

#endif	/* LED_H */

