/* 
 * File:   DriverConfigs.h
 * Author: Rick
 *
 * Created on July 17, 2016, 8:08 PM
 */

#ifndef DRIVERCONFIGS_H
#define	DRIVERCONFIGS_H

void SetDriver(char num);
void SetUpDataSets();
char DriverCount();
char *CurrentDriverName();
void DriverNamePrint(char num);
void insert(char str);
char DriverActive();
void DriverNameChar(char byte, unsigned char num);
void DriverMaxThrottle(int value);
void DriverMaxMaxRegen(int value);
void DriverLowBatCutoff(int value);
void DriverRamp(int value);
void DriverFalt(char value);
void DriverFW_RW_EN(bool value);
void DriverRegenInput(bool value);
void DriverDebugEn(bool value);
int GetDriverMaxThrottle();
int GetDriverMaxMaxRegen();
int GetDriverLowBatCutoff();
int GetDriverRamp();
char GetDriverFalt();
bool GetDriverFW_RW_EN();
bool GetDriverRegenInput();
bool GetDriverDebugEn();
void NewDriverNameChar(char byte, unsigned char num);
void NewDriverMaxThrottle(int value);
void NewDriverMaxMaxRegen(int value);
void NewDriverLowBatCutoff(int value);
void NewDriverRamp(int value);
void NewDriverFalt(char value);
void NewDriverFW_RW_EN(bool value);
void NewDriverRegenInput(bool value);
void NewDriverDebugEn(bool value);
void NewDriverSave();
bool GetDriverEnabled();

#endif	/* DRIVERCONFIGS_H */

