/* 
 * File:   BatteryManagementTemperature.h
 * Author: Andrew
 *
 * Created on March 11, 2017, 5:58 PM
 */
#include "BatteryManagementGlobal.h"
#include "LT6804.h"
#include "Timers.h"
#ifndef BATTERYMANAGEMENTTEMPERATURE_H
#define	BATTERYMANAGEMENTTEMPERATURE_H

#ifdef	__cplusplus
extern "C" {
#endif

    

# define To 0.003361344537   //Normal Temprature in kelvin
 #define Temp_Sens_Per_IC 5
#define  Vin 3.2
#define VoltageDividerResistance  10000
#define A_Constant 8.42961857*pow(10,-4)
#define B_Constant 3380
#define Inverse_B_Constant 0.000295857988165
#define C_Constant 1.578649669*pow(10,-7)
#define Over_Temp_Value 5000 // TODO create number for this.
#define Over_Voltage_Value_LTC  0x9C4 // this constant is the highest voltage value before conversion. 
   // Compare Voltage = Over_Voltage_Value*16*100uV  
//Default Over_Voltage_Value_LTC=4.0 4.0=2500*16*100*10^-6
// 2500=0x7CF
    
int Send_Read_GPIO_Command(int Read_Option, int aux_codes[NUMBEROFIC][6]);
int Convert_To_Temp_Total(int Aux_codes_Bank1t[][6], int Aux_codes_Bank2[][6]);
void  Convert_To_Temp_Bank(int bank_num, int New_Temp_Data[][6]);
void Convert_To_Voltage_Temp(int Int_Array_Bank[][6],double Double_Array_Bank[][6]);
void CalculateTemp(double Conv_Temp[][6]);
void Update_Average_Array_Temp( int bank_num, double Array_Bank[][6]);
int Check_Array_Faults_Temp();
double Get_Extreme_Temperature(int type, int parm, int bank);
int Read_GPIO_Bank(int Aux_codes_Bank[][6]);
int Read_Total_Temperature(int Aux_codes_Bank1[][6], int Aux_codes_Bank2[][6]);
void Pack_Temperature_Sum();
double gettemp(int ic, int num,int bank);
 
extern int Aux_codes_Bank1[NUMBEROFIC][6];
extern int Aux_codes_Bank2[NUMBEROFIC][6];
   
extern double Average_Temperature_Codes_Bank1[NUMBEROFIC][6];
extern double Average_Temperature_Codes_Bank2[NUMBEROFIC][6];

extern double Min_Temp[2][3];
extern double Max_Temp[2][3];
extern double Module_Average_Temp_Value[2][3];

#ifdef	__cplusplus
}
#endif

#endif	/* BATTERYMANAGEMENTTEMPERATURE_H */

