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

int GetDriverRamp(){
    return DriverConfig.Ramp;
}

char GetDriverFalt(){
    return DriverConfig.Falt;
}

bool GetDriverFW_RW_EN(){
    return DriverConfig.FW_RW_EN;
}

bool GetDriverRegenInput(){
    return DriverConfig.RegenInput;
}

bool GetDriverDebugEn(){
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

void NewDriverNameChar(char byte, unsigned char num){
    NewDriver.NAME[num] = byte;
}

void NewDriverMaxThrottle(int value){
    NewDriver.MaxThrottle = value;
}

void NewDriverMaxMaxRegen(int value){
    NewDriver.MaxRegen = value;
}

void NewDriverLowBatCutoff(int value){
    NewDriver.LowBatCutoff = value;
}

void NewDriverRamp(int value){
    NewDriver.Ramp = value;
}

void NewDriverFalt(char value){
    NewDriver.Falt = value;
}

void NewDriverFW_RW_EN(bool value){
    NewDriver.FW_RW_EN = value;
}

void NewDriverRegenInput(bool value){
    NewDriver.RegenInput = value;
}

void NewDriverDebugEn(bool value){
    NewDriver.DebugEn = value;
}

void NewDriverSave(){
    SaveDriverConfig(NewDriver.NAME, NewDriver.MaxThrottle, NewDriver.MaxRegen, NewDriver.LowBatCutoff, NewDriver.Ramp, NewDriver.Falt, NewDriver.FW_RW_EN, NewDriver.RegenInput, NewDriver.DebugEn);
}