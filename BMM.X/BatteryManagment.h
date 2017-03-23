/* 
 * File:   Read_Battery_Level.h
 * Author: Andrew
 *
 * Created on March 15, 2016, 12:53 PM
 */
#ifndef READ_BATTERY_LEVEL_H
#define	READ_BATTERY_LEVEL_H

#include <stdbool.h>
#include "BatteryManagementGlobal.h"

#define Battery_Array 0
#define Temprature_Array 1

void Start_BMS(int mode); // Starts the BMS mode value is indicated by what to go into. 1=Run Mode for the car 2=Charge mode for the charger
void ChargerEN();
bool ChargerVal();
void ReadCurrentVolt();
void ReadVoltToCurrent();
float CurrentGet(bool total, char channel);
extern void CurrentCoulombCount(int tme);
int UpdateLT6804(int bank); //Updates Lt6804 configuration sends a fault if a error is detected.

void Update_Average_Array(bool Type_Of_Array,int Array_Index,double Array_Bank1[][Array_Index],double Array_Bank2[][Array_Index]);
extern int Read_Total_GPIO(int Aux_codes_Bank1[][6], int Aux_codes_Bank2[][6]);
double getbigc();
  extern int FaultValue;// TODO IS THIs THE RIGHT WAY FOR A GLOBAL VARIABLE?

  extern bool BypassConfigbank1[NUMBEROFIC][12];
  extern bool BypassConfigbank2[NUMBEROFIC][12];
  //Arrays for Aux GPIO
 

 
 double gettemp(int ic, int num,int bank);
 float VoltGet(char channel);
#endif	/* READ_BATTERY_LEVEL_H */

