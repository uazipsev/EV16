#include <stdio.h>
#include "EEprom.h"
#include <stdbool.h>

char *DriverNamesList[10];

struct DriverData
{
    char NAME[3];        //Driver Name Initials 
    int MaxThrottle;    //Max Driver Throttle
    int MaxRegen;       //Max Driver Regen
    int LowBatCutoff;   //Battery Cutoff
    int Ramp;           //Throttle Ramp
    char Falt;          //Fault allowed 
    bool FW_RW_EN;      //Motor Direction control allowed 
    bool RegenInput;    //What input is used for regen control
    bool DebugEn;       //Enable debugging - overrides  
};

struct DriverData DriverConfig;

char CurentDriver;
char DriverCountNum;

/*******************************************************************
 * @brief           SetUpDataSets
 * @brief           Runs a bunch of getters to set up dynamics for car
 * @return          none
 * @note            uses getters to set up the cars settings 
 *******************************************************************/
void SetUpDataSets(){
    
//    ReadCarDriver();
//    ReadThrottlePrecent();
//    ReadThrottleTrigger();
//    ReadBrakeTrigger();
//      SetBrakeLightValue(ReadBrakeLightTrigger());
//     char z = 0;
//    for(z=0;z<50;z++){
//        writeRegister(ADDRESS, z, z);
//        Delay(2);
//    }
//    Delay(10);
//    for(z=0;z<50;z++){
//        readRegister(ADDRESS, z);
//        Delay(5);
//    }
    //This sets up the I2C to EEPROM com's to save car data. 
    EEpromInit();
    //Delay(100);
    char RCJ[3] = {'T','B','H'};
    SaveDriverConfig(RCJ,100,0,100,0,0, 1, 0, 1);
    DriverCountNum = ReadCarDriverCount();
    int i = 0;
    for(i = 0;i<DriverCountNum;i++){
        DriverNamesList[i] = ReadDriverNames(i);
    }
    //SaveCarDriver(1);
    SetDriver(ReadCarDriver());
    
}

void SetDriver(char num){
    CurentDriver = num;
    ReadDriverConfig(CurentDriver);
    SaveCarDriver(num);
}

char DriverCount(){
    return DriverCountNum;
}

char *CurrentDriverName(){
    return DriverConfig.NAME;
}

char *DriverNames(int num){
    return DriverNamesList[num];
}

char DriverActive(){
    return CurentDriver;
}

int GetDriverMaxThrottle(){
    return DriverConfig.MaxThrottle;
}

int GetDriverMaxMaxRegen(){
    return DriverConfig.MaxRegen;
}

int GetDriverLowBatCutoff(){
    return DriverConfig.LowBatCutoff;
}

int GetDriverRamp(int value){
    return DriverConfig.Ramp;
}

char GetDriverFalt(char value){
    return DriverConfig.Falt;
}

bool GetDriverFW_RW_EN(){
    return DriverConfig.FW_RW_EN;
}

bool GetDriverRegenInput(bool value){
    return DriverConfig.RegenInput;
}

bool GetDriverDebugEn(bool value){
    return DriverConfig.DebugEn;
}

void DriverNameChar(char byte, unsigned char num){
    DriverConfig.NAME[num] = byte;
}

void DriverMaxThrottle(int value){
    DriverConfig.MaxThrottle = value;
}

void DriverMaxMaxRegen(int value){
    DriverConfig.MaxRegen = value;
}

void DriverLowBatCutoff(int value){
    DriverConfig.LowBatCutoff = value;
}

void DriverRamp(int value){
    DriverConfig.Ramp = value;
}

void DriverFalt(char value){
    DriverConfig.Falt = value;
}

void DriverFW_RW_EN(bool value){
    DriverConfig.FW_RW_EN = value;
}

void DriverRegenInput(bool value){
    DriverConfig.RegenInput = value;
}

void DriverDebugEn(bool value){
    DriverConfig.DebugEn = value;
}