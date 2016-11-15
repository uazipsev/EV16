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
#define Battery_Array 0
#define Temprature_Array 1
#define bank_1 1
#define bank_2 2
#define module_0 0
#define module_1 1
#define module_2 2
#define min_select 0
#define max_select 1
extern float CVolt[6];
void Start_BMS(int mode); // Starts the BMS mode value is indicated by what to go into. 1=Run Mode for the car 2=Charge mode for the charger
void ChargerEN();
bool ChargerVal();
void ReadCurrentVolt();
void ReadVoltToCurrent();
int CurrentGet(bool total, char channel);
int Read_Battery(int BatteryPlacement,int cell_codes[][12] );// Amount of IC's, amount of cells per IC
extern void CurrentCoulombCount(int tme);
int UpdateLT6804(int bank); //Updates Lt6804 configuration sends a fault if a error is detected.
extern int Read_Total_Voltage(int cell_codesBank1[][12], int cell_codesBank2[][12]);
void Update_Average_Array(bool Type_Of_Array,int Array_Index,double Array_Bank1[][Array_Index],double Array_Bank2[][Array_Index]);
extern int Read_Total_GPIO(int Aux_codes_Bank1[][6], int Aux_codes_Bank2[][6]);
double getbigc();
double Get_Extreme_Voltage(int type, int parm, int bank);
  extern int FaultValue;// TODO IS THIs THE RIGHT WAY FOR A GLOBAL VARIABLE?
  
  //Arrays for Cell Voltages
  extern int cell_codes_Bank1[NUMBEROFIC][12];
  extern int cell_codes_Bank2[NUMBEROFIC][12];
  extern double Converted_Cell_Codes_Bank1[NUMBEROFIC][12];
  extern double Converted_Cell_Codes_Bank2[NUMBEROFIC][12];
  extern double Average_cell_codes_Bank1[NUMBEROFIC][12];
  extern double Average_cell_codes_Bank2[NUMBEROFIC][12];
  
  //Arrays for Aux GPIO
  extern int Aux_codes_Bank1[NUMBEROFIC][6];
  extern int Aux_codes_Bank2[NUMBEROFIC][6];
  extern double Converted_Temprature_Bank1[NUMBEROFIC][6];
  extern double Converted_Temprature_Bank2[NUMBEROFIC][6];
  extern double Average_Temprature_Codes_Bank1[NUMBEROFIC][6];
  extern double Average_Temprature_Codes_Bank2[NUMBEROFIC][6];
 extern double Min_Temp[2][3];
   extern double Max_Temp[2][3];
 extern  double Min_Cell_Voltage[2][3];
 extern  double Max_Cell_Voltage[2][3];
 
 double gettemp(int ic, int num,int bank);
#endif	/* READ_BATTERY_LEVEL_H */

