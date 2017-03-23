/* 
 * File:   BatteryManagementGlobal.h
 * Author: Andrew
 *
 * Created on March 11, 2017, 7:36 PM
 */

#ifndef BATTERYMANAGEMENTGLOBAL_H
#define	BATTERYMANAGEMENTGLOBAL_H

#ifdef	__cplusplus
extern "C" {
#endif


#define NUMBEROFIC 12
#define NUMBEROFCH 2
#define bank_1 1
#define bank_2 2
#define module_0 0
#define module_1 1
#define module_2 2
#define min_select 0
#define max_select 1
    
    //For Max and Min Values to be sent to the ECU
#define Data_Value 0 //This is for the max and min array to indicated which element is where in the array.
#define IC_LOCATION 1 //This is for the max and min array to indicated which element is where in the array.
#define SENSOR_LOCATION 2 //This is for the max and min array to indicated which element is where in the array.

#define Bank1_Array_Indicator 0
#define Bank2_Array_Indicator 1
  #define Num_TempSense_Per_Module 15
    
    
    //Fault Control Number
#define UnderVoltageFault 1
#define OverVoltageFault 2
#define OverTempratureThreshold 3 
#define WatchdogTimerFault 4 //Indicates if watchdog timer expired
#define OverCurrentFault 5
#define SumofCellsMeasurement 6 
#define InternalDieTemp 7 
#define AnalogPowerSupplyFault 8 
#define DigitalPowerSupplyFault 9
#define SecondRefrenceFualt 10
#define Muxfailfault 11
#define OpenWireFault 12 //The Wire that is fault will be indicated in the algorithim. 
#define ThermalShutdownFault 13
#define CommuncationFault 14
#define ReadstatRegFault 15
#define ReadVoltRegFault 16
#define ReadAuxRegFault 17
#define NoBankselected 18
#define Loose_Slave_Fault 19
#define Invalid_Test_Cond 20


#define Voltage_Charge 294
#define Amps_Charge 5

#ifdef	__cplusplus
}
#endif

#endif	/* BATTERYMANAGEMENTGLOBAL_H */

