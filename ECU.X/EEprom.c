/*******************************************************************
 * @brief           EEprom.c
 * @brief           gives access to the EEPROM to set and store data
 * @return          N/A
 * @note            The lib is written for FT24C64A-ULR-T IC (http://www.fremontmicrousa.com/pdf/EN-24C32_64-300-V1p8.pdf)
 *******************************************************************/

#include "I2C.h"
#include "EEprom.h"
#include "Function.h"
#include <stdio.h>
#include <string.h>

#define ADDRESS 0x50

char data[8];

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

/*******************************************************************
 * @brief           EEpromInit
 * @brief           Setup EEprom
 * @return          none
 * @note            Sets up the I2C here
 *******************************************************************/

void EEpromInit(){
    
    InitI2C();
}

/*******************************************************************
 * @brief           writeRegister
 * @brief           Writes data to I2C device
 * @return          none
 * @note            uses commands from the I2C lib to construct packets to send out on the bus 
 *******************************************************************/
void writeRegister(char i2cAddress, int reg, char value)
{
    IdleI2C();
	StartI2C();						//Initiate start condition
	WriteI2C(i2cAddress << 1);	    //write 1 byte
	AckI2C();                       //Wait for ACK
    IdleI2C();                      //Ensure module is Idle
    WriteI2C(reg >> 8);			    //Write High word address
    AckI2C();   					//Wait for ACK
	IdleI2C();					    //Ensure module is Idle
    WriteI2C(reg & 0xff);			//Write Low word address
	AckI2C();						//Wait for ACK
    IdleI2C();                      //Ensure module is idle
    WriteI2C(value);				//Write Low word address
	AckI2C();					    //Wait for ACK
    IdleI2C();                      //Ensure module is idle
	StopI2C();				        //Send stop condition
}

/*******************************************************************
 * @brief           readRegister
 * @brief           reads data from the I2C device
 * @return          none
 * @note            uses commands from the I2C lib to construct packets to send out on the bus 
 *******************************************************************/
char readRegister(char i2cAddress, int reg)
{
    IdleI2C();
    StartI2C();						    //Initiate start condition
	WriteI2C(i2cAddress << 1);	        //write 1 byte
    AckI2C();   					    //Wait for ACK
	IdleI2C();						    //Ensure module is Idle
    WriteI2C(reg >> 8);			    	//Write High word address
    AckI2C();   					    //Wait for ACK
	IdleI2C();						    //Ensure module is Idle
    WriteI2C(reg & 0xff);			    //Write Low word address
    AckI2C();   					    //Wait for ACK
	IdleI2C();						    //Ensure module is Idle
	StopI2C();				            //Send stop condition
    IdleI2C();
	StartI2C();					     	//Initiate start condition
	WriteI2C((i2cAddress << 1) | 0x01);	//Write 1 byte - R/W bit should be 1 for read
    AckI2C();   					    //Wait for ACK
	IdleI2C();						    //Ensure bus is idle
	getsI2C(data, 1);		     	    //Read in multiple bytes
	//AckI2C();				     	    //Send Not Ack
    IdleI2C();						    //Ensure bus is idle
	StopI2C();						    //Send stop condition
    
    return data[0];
}

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
     char z = 0;
    for(z=0;z<50;z++){
        writeRegister(ADDRESS, z, z);
        Delay(2);
    }
    Delay(10);
    for(z=0;z<50;z++){
        readRegister(ADDRESS, z);
        Delay(5);
    }
}

/*******************************************************************
 * @brief           ReadCarDriver
 * @brief           Reading data location for car driver
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
char ReadCarDriver(){
    return readRegister(ADDRESS, 1);
}

/*******************************************************************
 * @brief           SaveCarDriver
 * @brief           Saving data location for car driver
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
void SaveCarDriver(char value){
    writeRegister(ADDRESS, 1,value);
    Delay(5);
}

/*******************************************************************
 * @brief           ReadCarDriverCount
 * @brief           Reading car driver count
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
char ReadCarDriverCount(){
    return readRegister(ADDRESS, 2);
}

/*******************************************************************
 * @brief           SaveCarDriverCount
 * @brief           Saving car driver count
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
void SaveCarDriverCount(char value){
    writeRegister(ADDRESS, 2,value);
}

/*******************************************************************
 * @brief           ReadThrottlePrecent
 * @brief           Reading data location for car throttle mismatch %
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
int ReadThrottlePrecent(){
    return readRegister(ADDRESS, 3);
}

/*******************************************************************
 * @brief           SaveThrottlePrecent
 * @brief           Saving data location for car throttle mismatch %
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
void SaveThrottlePrecent(int value){
    writeRegister(ADDRESS, 3, value);
}

/*******************************************************************
 * @brief           ReadThrottleTrigger
 * @brief           Reading data location for throttle max value for software safety system
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
int ReadThrottleTrigger(){
    return readRegister(ADDRESS, 4);
}

/*******************************************************************
 * @brief           SaveThrottleTrigger
 * @brief           Saving data location for throttle max value for software safety system
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
void SaveThrottleTrigger(int value){
    writeRegister(ADDRESS, 4, value);
}

/*******************************************************************
 * @brief           ReadBrakeTrigger
 * @brief           Reading data location for brake max value for software safety system
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
int ReadBrakeTrigger(){
    return readRegister(ADDRESS, 5);
}

/*******************************************************************
 * @brief           SaveBrakeTrigger
 * @brief           Saving data location for brake max value for software safety system
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
void SaveBrakeTrigger(int value){
    writeRegister(ADDRESS, 5, value);
}

/*******************************************************************
 * @brief           ReadBrakeLightTrigger
 * @brief           Reading data location for brake light threshold
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
int ReadBrakeLightTrigger(){
    return readRegister(ADDRESS, 6);
}

/*******************************************************************
 * @brief           SaveBrakeLightTrigger
 * @brief           Saving data location for brake light threshold
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
void SaveBrakeLightTrigger(int value){
    writeRegister(ADDRESS, 6, value);
}

/*******************************************************************
 * @brief           ReadDriverConfig
 * @brief           Reading driver config and save it in struct for getters 
 * @return          N/A
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
void ReadDriverConfig(char dvr){
    char data[2];
    DriverConfig.NAME[0] = readRegister(ADDRESS, (dvr+DRIVERCONFIGSTART));
    DriverConfig.NAME[1] = readRegister(ADDRESS, (dvr+DRIVERCONFIGSTART+1));
    DriverConfig.NAME[2] = readRegister(ADDRESS, (dvr+DRIVERCONFIGSTART+2));
    data[0] = readRegister(ADDRESS, dvr+DRIVERCONFIGSTART+3);
    data[1] = readRegister(ADDRESS, dvr+DRIVERCONFIGSTART+4);
    DriverConfig.MaxThrottle = (data[0] << 8) + data[1];
    data[0] = readRegister(ADDRESS, dvr+DRIVERCONFIGSTART+5);
    data[1] = readRegister(ADDRESS, dvr+DRIVERCONFIGSTART+6);
    DriverConfig.MaxRegen = (data[0] << 8) + data[1];
    data[0] = readRegister(ADDRESS, dvr+DRIVERCONFIGSTART+7);
    data[1] = readRegister(ADDRESS, dvr+DRIVERCONFIGSTART+8);
    DriverConfig.LowBatCutoff = (data[0] << 8) + data[1];
    data[0] = readRegister(ADDRESS, dvr+DRIVERCONFIGSTART+9);
    data[1] = readRegister(ADDRESS, dvr+DRIVERCONFIGSTART+10);
    DriverConfig.Ramp = (data[0] << 8) + data[1];
    DriverConfig.Falt = readRegister(ADDRESS, dvr+DRIVERCONFIGSTART+11);
    data[0] = readRegister(ADDRESS, dvr+DRIVERCONFIGSTART+12);
    DriverConfig.FW_RW_EN = ((data[0] >> 1)&(0x01));
    DriverConfig.RegenInput = ((data[0] >> 2)&(0x01));
    DriverConfig.DebugEn = ((data[0] >> 3)&(0x01));
}

/*******************************************************************
 * @brief           SaveDriverConfig
 * @brief           Saving data location for Driver Data
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
void SaveDriverConfig(char NAME[3], int MaxThrottle, int MaxRegen, int LowBatCutoff, int Ramp, char Fault, bool Fw_Rv, bool RegenInput, bool DebugEn){
    char number = ReadCarDriverCount();
    number++;
    SaveCarDriverCount(number);
    writeRegister(ADDRESS, number, NAME[0]);
    writeRegister(ADDRESS, number+1, NAME[1]);
    writeRegister(ADDRESS, number+2, NAME[2]);
    writeRegister(ADDRESS, number+3, MaxThrottle>>8);
    writeRegister(ADDRESS, number+4, MaxThrottle & 0xff);
    writeRegister(ADDRESS, number+5, MaxRegen>>8);
    writeRegister(ADDRESS, number+6, MaxRegen & 0xff);
    writeRegister(ADDRESS, number+7, LowBatCutoff>>8);
    writeRegister(ADDRESS, number+8, LowBatCutoff & 0xff);
    writeRegister(ADDRESS, number+9, Ramp>>8);
    writeRegister(ADDRESS, number+10, Ramp & 0xff);
    writeRegister(ADDRESS, number+11, Fault);
    writeRegister(ADDRESS, number+12, ((DebugEn&0x01) << 2) | ((RegenInput&0x01) << 2) | ((Fw_Rv&0x01) << 1));
}