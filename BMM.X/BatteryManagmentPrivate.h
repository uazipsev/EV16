/* 
 * File:   BatteryManagmentPrivate.h
 * Author: Rick
 *
 * Created on April 11, 2016, 6:30 PM
 */

#ifndef BATTERYMANAGMENTPRIVATE_H
#define	BATTERYMANAGMENTPRIVATE_H

#include <stdbool.h>

bool CarOn = 1;
bool CurrentDir = 1; //Discharge by default


int k = 0;
int j =0;

float CurrentOffset[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
int Current[6];
float CVolt[6];
float Volt1 = 0;
float Volt2 = 0;
float CC1;
float CC2;
float CC3;

char CFGR0 = 0;
char CFGR1 = 0;
char CFGR2 = 0;
char CFGR3 = 0;
char CFGR4 = 0;
char CFGR5 = 0;

#define NUMBEROFIC 12
#define NUMBEROFCH 2
#define NUMBEROFDATA 8

//Discharge time out value 
#define DCTO 0 

#define CURRENTGAIN 40
#define VOLTAGERATIO 158.18
#define SHUNTOHMS 0.0001
#define ADCBIT 4095

int LTC6804_DATA[NUMBEROFCH][NUMBEROFDATA*NUMBEROFIC];

#endif	/* BATTERYMANAGMENTPRIVATE_H */

