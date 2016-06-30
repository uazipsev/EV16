/* 
 * File:   Read_Battery_Level.h
 * Author: Andrew
 *
 * Created on March 15, 2016, 12:53 PM
 */
#ifndef READ_BATTERY_LEVEL_H
#define	READ_BATTERY_LEVEL_H

#include <stdbool.h>
#define NUMBEROFIC 12
#define NUMBEROFCH 2
#define Amount_Of_Samples 10

void Start_BMS(int mode);
void ChargerEN();
bool ChargerVal();
void ReadCurrentVolt();
void ReadVoltToCurrent();
int CurrentGet(bool total, char channel);
int Read_Battery(int BatteryPlacement,int cell_codes[][12] );// Amount of IC's, amount of cells per IC
extern void CurrentCoulombCount(int tme);
int UpdateLT6804(int bank); //Updates Lt6804 configuration sends a fault if a error is detected.
extern int Read_Total_Voltage(int cell_codesBank1[][12], int cell_codesBank2[][12],int *Number_Of_Samples);
void Updated_Cell_Array(int cell_codesBank1[][12],int cell_codesBank2[][12], int FirstSample);
extern int Read_Total_GPIO(int Aux_codes_Bank1[][6], int Aux_codes_Bank2[][6]);
  extern int FaultValue;// TODO IS THIs THE RIGHT WAY FOR A GLOBAL VARIABLE?
  extern int cell_codes_Bank1[NUMBEROFIC][12];
 extern int cell_codes_Bank2[NUMBEROFIC][12];
// extern int cell_codes_Bank1_Filtered[Amount_Of_Samples][NUMBEROFIC][12];
// extern int cell_codes_Bank2_Filtered[Amount_Of_Samples][NUMBEROFIC][12];
  extern int Aux_codes_Bank1[NUMBEROFIC][6];
  extern int Aux_codes_Bank2[NUMBEROFIC][6];
 extern int Average_cell_codes_Bank1[NUMBEROFIC][12];
 extern int Average_cell_codes_Bank2[NUMBEROFIC][12];
#endif	/* READ_BATTERY_LEVEL_H */

