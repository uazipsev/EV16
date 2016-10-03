/* 
 * File:   EEprom.h
 * Author: Rick
 *
 * Created on July 18, 2016, 1:32 AM
 */

#ifndef EEPROM_H
#define	EEPROM_H

#include <stdbool.h>

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
void SetCarLock(bool value);

#endif	/* EEPROM_H */

