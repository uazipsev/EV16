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



struct Names {
       char data;
       struct Names* next;
};

struct node* head = NULL;

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
    //SaveCarDriverCount(0);
//    char RCJ[3] = {'R','C','J'};
//    SaveDriverConfig(RCJ,100,0,100,0,0, 1, 0, 1);
//    char BKB[3] = {'B','K','B'};
//    SaveDriverConfig(BKB,100,0,100,0,0, 1, 0, 1);
//    char TYH[3] = {'T','Y','H'};
//    SaveDriverConfig(TYH,100,0,100,0,0, 1, 0, 1);
    insert('0');
    DriverCountNum = ReadCarDriverCount();
    int i = 0;
    for(i = 0;i<DriverCountNum;i++){
        ReadDriverNames(i+1);
    }
    //SaveCarDriver(1);
    SetDriver(ReadCarDriver());
    
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
    SaveCarDriver(num);
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
char DriverCount(){
    return DriverCountNum;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
char *CurrentDriverName(){
    return DriverConfig.NAME;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
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
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
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
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
char DriverActive(){
    return CurentDriver;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
int GetDriverMaxThrottle(){
    return DriverConfig.MaxThrottle;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
int GetDriverMaxMaxRegen(){
    return DriverConfig.MaxRegen;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
int GetDriverLowBatCutoff(){
    return DriverConfig.LowBatCutoff;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
int GetDriverRamp(){
    return DriverConfig.Ramp;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
char GetDriverFalt(){
    return DriverConfig.Falt;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
bool GetDriverFW_RW_EN(){
    return DriverConfig.FW_RW_EN;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
bool GetDriverRegenInput(){
    return DriverConfig.RegenInput;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
bool GetDriverDebugEn(){
    return DriverConfig.DebugEn;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void DriverNameChar(char byte, unsigned char num){
    DriverConfig.NAME[num] = byte;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void DriverMaxThrottle(int value){
    DriverConfig.MaxThrottle = value;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void DriverMaxMaxRegen(int value){
    DriverConfig.MaxRegen = value;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void DriverLowBatCutoff(int value){
    DriverConfig.LowBatCutoff = value;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void DriverRamp(int value){
    DriverConfig.Ramp = value;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void DriverFalt(char value){
    DriverConfig.Falt = value;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void DriverFW_RW_EN(bool value){
    DriverConfig.FW_RW_EN = value;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void DriverRegenInput(bool value){
    DriverConfig.RegenInput = value;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void DriverDebugEn(bool value){
    DriverConfig.DebugEn = value;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverNameChar(char byte, unsigned char num){
    NewDriver.NAME[num] = byte;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverMaxThrottle(int value){
    NewDriver.MaxThrottle = value;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverMaxMaxRegen(int value){
    NewDriver.MaxRegen = value;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverLowBatCutoff(int value){
    NewDriver.LowBatCutoff = value;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverRamp(int value){
    NewDriver.Ramp = value;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverFalt(char value){
    NewDriver.Falt = value;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverFW_RW_EN(bool value){
    NewDriver.FW_RW_EN = value;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverRegenInput(bool value){
    NewDriver.RegenInput = value;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverDebugEn(bool value){
    NewDriver.DebugEn = value;
}

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/
void NewDriverSave(){
    SaveDriverConfig(NewDriver.NAME, NewDriver.MaxThrottle, NewDriver.MaxRegen, NewDriver.LowBatCutoff, NewDriver.Ramp, NewDriver.Falt, NewDriver.FW_RW_EN, NewDriver.RegenInput, NewDriver.DebugEn);
}