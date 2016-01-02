/* 
 * File:   DDS_Interface.h
 * Author: User
 *
 * Created on June 2, 2015, 6:56 PM
 */

#ifndef DDS_INTERFACE_H
#define	DDS_INTERFACE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>



#define START_BUTTON 0
#define START_LED  0
#define DASH_LED2  1

int buttonArray[8];
unsigned int buttons=0;
unsigned int indicators=0;
int seekButtonChange();
void changeLEDState(int LED,int state);


#ifdef	__cplusplus
}
#endif

#endif	/* DDS_INTERFACE_H */

