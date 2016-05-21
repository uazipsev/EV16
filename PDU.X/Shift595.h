/* 
 * File:   Shift595.h
 * Author: Rick
 *
 * Created on May 11, 2015, 1:44 AM
 */

#ifndef SHIFT595_H
#define	SHIFT595_H

#define num_of_595s 3
#define RegPins num_of_595s * 8

char registers[RegPins];

extern void StartUp595(void);
extern void SetPin595(char Reg, char pin, char value);
extern void Clear595(void);
extern void writeRegisters(void);


#endif	/* SHIFT595_H */

