/* 
 * File:   Read_Battery_Level.h
 * Author: Andrew
 *
 * Created on March 15, 2016, 12:53 PM
 */
#ifndef READ_BATTERY_LEVEL_H
#define	READ_BATTERY_LEVEL_H

#include <stdbool.h>
#define NUMBEROFIC 1
#define NUMBEROFCH 2
#define NUMBEROFDATA 6
void Start_BMS();
void ChargerEN();
void ReadCurrentVolt();
void ReadVoltToCurrent();
int CurrentGet();
int Read_Battery(int BatteryPlacement,int cell_codes[][12] );// Amount of IC's, amount of cells per IC
extern void CurrentCoulombCount(int tme);
void UpdateLT6804(); //Updates Lt6804 configuration.
            
#endif	/* READ_BATTERY_LEVEL_H */

