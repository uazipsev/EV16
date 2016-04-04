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

LTC6804_DATA[NUMBEROFCH][NUMBEROFIC][NUMBEROFDATA];

void Start_LTC6804_initialize();
void Read_Battery(int BatteryPlacement);

int CFGR0 = 0;
int CFGR1 = 0;
int CFGR2 = 0;
int CFGR3 = 0;
int CFGR4 = 0;
int CFGR5 = 0;

            
#endif	/* READ_BATTERY_LEVEL_H */

