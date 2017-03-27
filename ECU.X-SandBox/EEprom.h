/* 
 * File:   EEprom.h
 * Author: Rick
 *
 * Created on July 18, 2016, 1:32 AM
 */

#ifndef EEPROM_H
#define	EEPROM_H

#include <stdbool.h>

#define DRIVER_ACTIVE_EEPROM_LOCATION 1
#define DRIVER_SAVED_EEPROM_LOCATION 2
#define THROTTLE_ERROR_EEPROM_LOCATION 3
#define THROTTLE_MAX_EEPROM_LOCATION 4
#define BRAKE_MAX_EEPROM_LOCATION 5
#define BRAKE_LIGHT_THRESHOLDS_EEPROM_LOCATION 6
#define PIN_HIGH_EEPROM_LOCATION 7
#define PIN_LOW_EEPROM_LOCATION 8
#define CAR_LOCK_EEPROM_LOCATION 9
#define CAR_SW_START_EEPROM_LOCATION 10
#define CAR_SW_TEST_EEPROM_LOCATION 11
#define CAR_LT_BMM_EEPROM_LOCATION 12
#define CAR_LT_IMD_EEPROM_LOCATION 13
#define CAR_LT_ACT_EEPROM_LOCATION 14

#define DRIVERCONFIGSTART 31

void EEpromInit();
void DataWrite(char address, char data);
char DataRead(char address);
char readRegister(char i2cAddress, int reg);
void writeRegister(char i2cAddress, int reg, char value);
char ReadCarDriver();
void SaveCarDriver(char value);
void SaveCarDriverCount(char value);
char ReadCarDriverCount();
int ReadThrottlePrecent();
void SaveThrottlePrecent(int value);
int ReadThrottleTrigger();
void SaveThrottleTrigger(int value);
int ReadBrakeTrigger();
void SaveBrakeTrigger(int value);
int ReadBrakeLightTrigger();
void SaveBrakeLightTrigger(int value);
void SaveDriverConfig(char NAME[3], int MaxThrottle, int MaxRegen, int LowBatCutoff, int Ramp, char Fault, bool Fw_Rv, bool RegenInput, bool DebugEn);
void ReadDriverConfig(char dvr);
void ReadDriverNames(char dvr);
int ReadPinCode();
void SavePinCode(int value);
bool ReadCarLock();
void SaveCarLock(bool value);
char ReadCarStartSwitch();
void SaveCarStartSwitch(char value);
char ReadCarTestSwitch();
void SaveCarTestSwitch(char value);
char ReadCarBMMLight();
void SaveCarBMMLight(char value);
char ReadCarIMDLight();
void SaveCarIMDLight(char value);
char ReadCarACTLight();
void SaveCarACTLight(char value);

#endif	/* EEPROM_H */

