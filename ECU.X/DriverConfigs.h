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
char *DriverNames(int num);
char DriverActive();
void DriverNameChar(char byte, char num);
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
int GetDriverRamp(int value);
char GetDriverFalt(char value);
bool GetDriverFW_RW_EN();
bool GetDriverRegenInput(bool value);
bool GetDriverDebugEn(bool value);

#endif	/* DRIVERCONFIGS_H */

