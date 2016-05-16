/* 
 * File:   Current.h
 * Author: Rick
 *
 * Created on March 27, 2015, 3:06 AM
 */

#ifndef CURRENT_H
#define	CURRENT_H

#define NUMFALTS 6

extern float Current_Get();
void Current_Convert();
void Current_Filter();
void Current_Read();
extern char Current_Fault();




#endif	/* CURRENT_H */

