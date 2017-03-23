/* 
 * File:   BatteryManagementCells.h
 * Author: Andrew
 *
 * Created on March 11, 2017, 8:18 PM
 */
#include "BatteryManagementGlobal.h"
#ifndef BATTERYMANAGEMENTCELLS_H
#define	BATTERYMANAGEMENTCELLS_H
#include <stdbool.h>
#include "LT6804.h"
#include "timers.h"
#define Cell_Per_Bank 12

  
#define Over_Voltage_Value 4
#define Under_Voltage_Value 3.2

#ifdef	__cplusplus
extern "C" {
#endif    
    
int Read_Total_Voltage(int cell_codesBank1[][12], int cell_codesBank2[][12]);
int Insert_Cell_Data_Total(int New_Cell_Data_Bank1[][12], int New_Cell_Data_Bank2[][12]);
void Insert_Cell_Data_Bank(int bank_num, int New_Cell_Data_Bank[][12]);
int Read_Cell_Voltage_Bank(int Cell_Voltage_codes[][12]);
int Send_Read_CellV_Command(int ReadOption, int cell_codes[][12]);// Amount of IC's, amount of cells per IC
void Convert_To_Voltage_Cell(int I_Array_Bank[][12],double D_Array_Bank[][12]);  //Converts A to D readings from the LTC6804 to voltages to determine the voltage.
void Update_Average_Array_Cell(int bank, double Array_Bank[][12]);
int Check_Array_Faults_Cells();
int Check_Cell_Thresholds_Bank(int bank, double cell_codes_bank[][12]) ; // Checks the voltage of a bank if one cell has a error it will break out and present the error.  
int Check_Thresholds_Cell( double data);// Checks each cell to see if the data is over the threshold.
int TestThreshold(int test, double data); 
void Pack_Cell_Voltage_Sum();
double Get_Cell_Voltages(int ic, int num, int bank);
double Get_Pack_Voltages(int module, int bank);
double Get_Extreme_Voltage(int type, int parm, int bank);


    //Arrays for Cell Voltages
extern int cell_codes_Bank1[NUMBEROFIC][12];
extern int cell_codes_Bank2[NUMBEROFIC][12];
extern double Average_cell_codes_Bank1[NUMBEROFIC][12];
extern double Average_cell_codes_Bank2[NUMBEROFIC][12];
extern  double Min_Cell_Voltage[2][3];
extern  double Max_Cell_Voltage[2][3];
extern double Module_Voltage_Value[2][3];
 
#ifdef	__cplusplus
}
#endif

#endif	/* BATTERYMANAGEMENTCELLS_H */

