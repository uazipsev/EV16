/*******************************************************************
 * @brief           DriverConfigs.c
 * @brief           gives access to driver configs and allows storage for new driver config
 * @return          N/A
 * @note            
 *******************************************************************/
#include <stdio.h>
#include "EEprom.h"
#include <stdbool.h>
#include "DriverConfigs.h"
#include <string.h>
#include <stdlib.h>
#include "Functions.h"
#include "ThrottleBrakeControl.h"

char DriverNamesList[40];

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
struct DriverData NewDriver;

bool RunCarEnable = 0;

int PIN = 0;

struct Names {
       char data;
       struct Names* next;
};

struct node* head = NULL;

char CurentDriver;
char DriverCountNum;

char StartSwitch = 0;
char testSwitch = 0;

char BMMLight = 0;
char IMDLight = 0;
char ACTLight = 0;

/*******************************************************************
 * @brief           SetUpDataSets
 * @brief           Runs a bunch of getters to set up dynamics for car
 * @return          none
 * @note            uses getters to set up the cars settings 
 *******************************************************************/
void SetUpDataSets(){
    //printf("EEPROM\n");
    EEpromInit();  //Set up I2C and eeprom
    //SavePinCode(3117);
    //SetCarLock(1);
    SetThrotteMax(ReadThrottlePrecent()); //Grab throttle from eeprom and save it into struct.
    ReadThrottleTrigger();
    SetBrakeLightValue(ReadBrakeLightTrigger());
    insert('0');  //Set start in 
    DriverCountNum = ReadCarDriverCount();
    //printf("Driver number saved = %d\n",DriverCountNum);
    if(ReadCarLock()){
        RunCarEnable = 1;
    }
    PIN = ReadPinCode();
    //printf("Pin = %d\n",PIN);
    int i = 0;
    for(i = 0;i<DriverCountNum;i++){
        ReadDriverNames(i+1);
    }
    
    //SaveCarDriver(1);
    SetDriver(ReadCarDriver());
//    //Switch input save
//    SaveCarStartSwitch(3);
//    SaveCarTestSwitch(4);
//    //Light switch save
//    SaveCarBMMLight(3);
//    SaveCarIMDLight(2);
//    SaveCarACTLight(1);
}

/*******************************************************************
 * @brief           SetDriver
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void SetDriver(char num){
    CurentDriver = num;
    ReadDriverConfig(CurentDriver);
    SaveCarDriver(CurentDriver);
}

/*******************************************************************
 * @brief           DriverCount
 * @brief           Reads how many Drivers saved 
 * @return          none
 * @note            gets data from location 
 *******************************************************************/
char DriverCount(){
    return DriverCountNum;
}

/*******************************************************************
 * @brief           CurrentDriverName
 * @brief           
 * @return          driver name from current driver 
 * @note            reads driver name from struct
 *******************************************************************/
char *CurrentDriverName(){
    return DriverConfig.NAME;
}

/*******************************************************************
 * @brief           DriverNamePrint
 * @brief           Prints driver names 
 * @return          none
 * @note            reads drivers initals from a struct created at boot from driver configs
 *******************************************************************/
void DriverNamePrint(char num){
    struct Names *temp = head;
    int k = 0;
    int offset  = num*4-3;
    for(k = 0;k<offset;k++){
        temp = temp->next;
    }
    printf("%c",temp->data);
    temp = temp->next;
    printf("%c",temp->data);
    temp = temp->next;
    printf("%c\n",temp->data);  
}

/*******************************************************************
 * @brief           insert
 * @brief           Puts string in a list
 * @return          none
 * @note            Stores 3 chars based by the eeprom reading 
 *******************************************************************/
void insert(char str){
    struct Names* temp = (struct Names*)malloc(sizeof(struct Names));
    temp->data = str;
    temp->next = NULL;

    if(head){//head != NULL
        struct Names* temp1 = head;
        while(temp1->next != NULL) {//search last element
            temp1 = temp1->next;
        }
        temp1->next = temp;//insert new node
    } else {
        head = temp;//if head == NULL then replace with new node
    }
}

/*******************************************************************
 * @brief           DriverActive
 * @brief           what driver is active
 * @return          char CurentDriver
 * @note            the number that represents what driver is active 
 *******************************************************************/
char DriverActive(){
    return CurentDriver;
}

/*******************************************************************
 * @brief           GetDriverMaxThrottle
 * @brief           Get data from struct 
 * @return          int max throttle
 * @note            data is from eeprom stored  at boot
 *******************************************************************/
int GetDriverMaxThrottle(){
    return DriverConfig.MaxThrottle;
}

/*******************************************************************
 * @brief           GetDriverMaxMaxRegen
 * @brief           Get data from struct
 * @return          int Max Regen
 * @note            data is from eeprom stored  at boot
 *******************************************************************/
int GetDriverMaxMaxRegen(){
    return DriverConfig.MaxRegen;
}

/*******************************************************************
 * @brief           GetDriverLowBatCutoff
 * @brief           Get data from struct
 * @return          int LowBatCutoff
 * @note            data is from eeprom stored  at boot
 *******************************************************************/
int GetDriverLowBatCutoff(){
    return DriverConfig.LowBatCutoff;
}

/*******************************************************************
 * @brief           GetDriverRamp
 * @brief           Get data from struct
 * @return          int Ramp
 * @note            data is from eeprom stored  at boot
 *******************************************************************/
int GetDriverRamp(){
    return DriverConfig.Ramp;
}

/*******************************************************************
 * @brief           GetDriverFalt
 * @brief           Get data from struct
 * @return          char Falt
 * @note            data is from eeprom stored  at boot
 *******************************************************************/
char GetDriverFalt(){
    return DriverConfig.Falt;
}

/*******************************************************************
 * @brief           GetDriverFW_RW_EN
 * @brief           Get data from struct
 * @return          bool FW_RW_EN
 * @note            data is from eeprom stored  at boot
 *******************************************************************/
bool GetDriverFW_RW_EN(){
    return DriverConfig.FW_RW_EN;
}

/*******************************************************************
 * @brief           GetDriverRegenInput
 * @brief           Get data from struct
 * @return          bool RegenInput
 * @note            data is from eeprom stored  at boot
 *******************************************************************/
bool GetDriverRegenInput(){
    return DriverConfig.RegenInput;
}

/*******************************************************************
 * @brief           GetDriverDebugEn
 * @brief           Get data from struct
 * @return          bool DebugEn
 * @note            data is from eeprom stored  at boot
 *******************************************************************/
bool GetDriverDebugEn(){
    return DriverConfig.DebugEn;
}

/*******************************************************************
 * @brief           DriverNameChar
 * @brief           
 * @return          none
 * @note            
 *******************************************************************/
void DriverNameChar(char byte, unsigned char num){
    DriverConfig.NAME[num] = byte;
}

/*******************************************************************
 * @brief           DriverMaxThrottle
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void DriverMaxThrottle(int value){
    DriverConfig.MaxThrottle = value;
}

/*******************************************************************
 * @brief           DriverMaxMaxRegen
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void DriverMaxMaxRegen(int value){
    DriverConfig.MaxRegen = value;
}

/*******************************************************************
 * @brief           DriverLowBatCutoff
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void DriverLowBatCutoff(int value){
    DriverConfig.LowBatCutoff = value;
}

/*******************************************************************
 * @brief           DriverRamp
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void DriverRamp(int value){
    DriverConfig.Ramp = value;
}

/*******************************************************************
 * @brief           DriverFalt
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void DriverFalt(char value){
    DriverConfig.Falt = value;
}

/*******************************************************************
 * @brief           DriverFW_RW_EN
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void DriverFW_RW_EN(bool value){
    DriverConfig.FW_RW_EN = value;
}

/*******************************************************************
 * @brief           DriverRegenInput
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void DriverRegenInput(bool value){
    DriverConfig.RegenInput = value;
}

/*******************************************************************
 * @brief           DriverDebugEn
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void DriverDebugEn(bool value){
    DriverConfig.DebugEn = value;
}

/*******************************************************************
 * @brief           NewDriverNameChar
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverNameChar(char byte, unsigned char num){
    NewDriver.NAME[num] = byte;
}

/*******************************************************************
 * @brief           NewDriverMaxThrottle
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverMaxThrottle(int value){
    NewDriver.MaxThrottle = value;
}

/*******************************************************************
 * @brief           NewDriverMaxMaxRegen
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverMaxMaxRegen(int value){
    NewDriver.MaxRegen = value;
}

/*******************************************************************
 * @brief           NewDriverLowBatCutoff
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverLowBatCutoff(int value){
    NewDriver.LowBatCutoff = value;
}

/*******************************************************************
 * @brief           NewDriverRamp
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverRamp(int value){
    NewDriver.Ramp = value;
}

/*******************************************************************
 * @brief           NewDriverFalt
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverFalt(char value){
    NewDriver.Falt = value;
}

/*******************************************************************
 * @brief           NewDriverFW_RW_EN
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverFW_RW_EN(bool value){
    NewDriver.FW_RW_EN = value;
}

/*******************************************************************
 * @brief           NewDriverRegenInput
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverRegenInput(bool value){
    NewDriver.RegenInput = value;
}

/*******************************************************************
 * @brief           NewDriverDebugEn
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverDebugEn(bool value){
    NewDriver.DebugEn = value;
}

/*******************************************************************
 * @brief           NewDriverSave
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverSave(){
    SaveDriverConfig(NewDriver.NAME, NewDriver.MaxThrottle, NewDriver.MaxRegen, NewDriver.LowBatCutoff, NewDriver.Ramp, NewDriver.Falt, NewDriver.FW_RW_EN, NewDriver.RegenInput, NewDriver.DebugEn);
}

/*******************************************************************
 * @brief           GetDriverEnabled
 * @brief           gets Driver enable
 * @return          returns bool 
 * @note            
 *******************************************************************/
bool GetCarLock(){
    return RunCarEnable;
}

/*******************************************************************
 * @brief           SetDriverEnabled
 * @brief           Sets Driver enable
 * @return          returns N/A 
 * @note            
 *******************************************************************/
void SetCarLock(bool val){
    RunCarEnable = val;
    SaveCarLock(val);
}

/*******************************************************************
 * @brief           GetPIN
 * @brief           gets PIN from variable eeprom 
 * @return          returns int of the pin
 * @note            
 *******************************************************************/
int GetPIN(){
    return PIN;
}

/*******************************************************************
 * @brief           GetSwitch
 * @brief           gets switch number from saved data
 * @return          returns NA 
 * @note            
 *******************************************************************/
char GetSwitch(char val){
    if(val == START_SWITCH){
        return ReadCarStartSwitch();
    }
    if(val == TEST_SWITCH){
        return ReadCarTestSwitch();
    }
    else{
        return -1;
    }
}

/*******************************************************************
 * @brief           SaveSwitch
 * @brief           gets switch number from saved data
 * @return          returns NA 
 * @note            
 *******************************************************************/
void SaveSwitch(char val,char data){
    if(val == START_SWITCH){
        SaveCarStartSwitch(data);
    }
    else if(val == TEST_SWITCH){
        SaveCarTestSwitch(data);
    }
}

/*******************************************************************
 * @brief           GetLight
 * @brief           gets light location 
 * @return          returns NA 
 * @note            
 *******************************************************************/
char GetLight(char val){
    if(val == ACT_LIGHT){
        return ReadCarACTLight();
    }
    else if(val == BMM_LIGHT){
        return ReadCarBMMLight();
    }
    else if(val == IMD_LIGHT){
        return ReadCarIMDLight();
    }
    else{
        return -1;
    }
}

/*******************************************************************
 * @brief           SaveLight
 * @brief           sets lights to output locations
 * @return          returns NA 
 * @note            
 *******************************************************************/
void SaveLight(char val,char data){
    if(val == ACT_LIGHT){
        SaveCarACTLight(data);
    }
    else if(val == BMM_LIGHT){
        SaveCarBMMLight(data);
    }
    else if(val == IMD_LIGHT){
        SaveCarIMDLight(data);
    }
}
