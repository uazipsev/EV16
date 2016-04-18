/* 
 * File:   Read_Battery_Level.h
 * Author: Andrew
 *
 * Created on March 15, 2016, 12:53 PM
 */
#ifndef READ_BATTERY_LEVEL_H
#define	READ_BATTERY_LEVEL_H

#include <stdbool.h>

void Start_BMS();
void ChargerEN();
void ReadVoltToCurrent();
int CurrentGet(bool total, char channel);
void Read_Battery(int BatteryPlacement);
extern void CurrentCoulombCount(int tme);

            
#endif	/* READ_BATTERY_LEVEL_H */

