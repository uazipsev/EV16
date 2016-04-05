/* 
 * File:   Read_Battery_Level.h
 * Author: Andrew
 *
 * Created on March 15, 2016, 12:53 PM
 */
#include"LT6804.h"
#ifndef READ_BATTERY_LEVEL_H
#define	READ_BATTERY_LEVEL_H

#define NUMBEROFIC 12
#define NUMBEROFCH 2
#define NUMBEROFDATA 8

char LTC6804_DATA[NUMBEROFCH][NUMBEROFIC][NUMBEROFDATA];

void Start_LTC6804_initialize();
void Read_Battery(int BatteryPlacement);

char CFGR0 = 0;
char CFGR1 = 0;
char CFGR2 = 0;
char CFGR3 = 0;
char CFGR4 = 0;
char CFGR5 = 0;

            
#endif	/* READ_BATTERY_LEVEL_H */

