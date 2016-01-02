/* 
 * File:   StoppedState.h
 * Author: User
 *
 * Created on June 9, 2015, 9:58 PM
 */

#ifndef STOPPEDSTATE_H
#define	STOPPEDSTATE_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h>
#include <stdbool.h>
#include "debug.h"
//#include "StateMachine.h"
bool easterEggs();

void updateStoppedState();
extern int buttonArray[8];
extern int seekButtonChange();
extern void changeLEDState(int LED, bool state);
extern volatile unsigned int BootTimer;


#ifdef	__cplusplus
}
#endif

#endif	/* STOPPEDSTATE_H */

