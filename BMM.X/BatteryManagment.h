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
void ReadCurrentVolt();
void ReadVoltToCurrent();
int CurrentGet(bool total, char channel);
int Read_Battery(int BatteryPlacement,int cell_codes[][12] );// Amount of IC's, amount of cells per IC
extern void CurrentCoulombCount(int tme);
int UpdateLT6804(int bank); //Updates Lt6804 configuration sends a fault if a error is detected.
  extern int FaultValue;// TODO IS THIs THE RIGHT WAY FOR A GLOBAL VARIABLE?
#endif	/* READ_BATTERY_LEVEL_H */

