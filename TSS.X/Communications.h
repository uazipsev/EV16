/* 
 * File:   Communications.h
 * Author: User
 *
 * Created on May 31, 2015, 8:32 PM
 */

#ifndef COMMUNICATIONS_H
#define	COMMUNICATIONS_H

unsigned int throttle, brake;
void updateComms();
unsigned int buttonsCollector();
extern void Delay(int wait);
void respondTM();
void handleIndicators(int receivedIndicators);
void TBbarGraphs(int t, int b);

#endif	/* COMMUNICATIONS_H */

