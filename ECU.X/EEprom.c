/*******************************************************************
 * @brief           EEprom.c
 * @brief           gives access to the EEPROM to set and store data
 * @return          N/A
 * @note            The lib is written for 24LC00 IC ( http://ww1.microchip.com/downloads/en/DeviceDoc/21178G.pdf)
 *******************************************************************/

#include "I2C.h"
#include "EEprom.h"
#include "Function.h"

#define ADDRESS 0x50

char data[8];

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
void writeRegister(char i2cAddress, char reg, int value)
{
    IdleI2C();
	StartI2C();						//Initiate start condition
	WriteI2C(i2cAddress << 1);	    //write 1 byte
	IdleI2C();						//Ensure module is Idle
	WriteI2C(reg);			    	//Write High word address
	IdleI2C();						//Ensure module is idle
    WriteI2C(value);				//Write Low word address
	NotAckI2C();					//Send Not Ack
	StopI2C();				        //Send stop condition
}

/*******************************************************************
 * @brief           readRegister
 * @brief           reads data from the I2C device
 * @return          none
 * @note            uses commands from the I2C lib to construct packets to send out on the bus 
 *******************************************************************/
char readRegister(char i2cAddress, char reg)
{
    IdleI2C();
    StartI2C();						    //Initiate start condition
	WriteI2C(i2cAddress << 1);	        //write 1 byte
	IdleI2C();						    //Ensure module is Idle
    WriteI2C(reg);			    	    //Write Low word address
    //IdleI2C();				             //Send stop condition
    NotAckI2C();					     //Send Not Ack
    //NotAckI2C();					//Send Not Ack
	StopI2C();				        //Send stop condition
    Delay(5);
    IdleI2C();
	StartI2C();						//Initiate start condition
	WriteI2C((i2cAddress << 1) | 0x01);	//Write 1 byte - R/W bit should be 1 for read
	IdleI2C();						    //Ensure bus is idle
	getsI2C(data, 1);		     	    //Read in multiple bytes
    IdleI2C();						    //Ensure bus is idle
	NotAckI2C();					    //Send Not Ack
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
    char z = 0;
//    ReadCarDriver();
//    ReadThrottlePrecent();
//    ReadThrottleTrigger();
//    ReadBrakeTrigger();
//    ReadBrakeLightTrigger();
    for(z=0;z<16;z++){
        writeRegister(ADDRESS, z, z);
        Delay(5);
    }
    Delay(10);
    for(z=0;z<16;z++){
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
}

/*******************************************************************
 * @brief           ReadThrottlePrecent
 * @brief           Reading data location for car throttle mismatch %
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
int ReadThrottlePrecent(){
    
    return 0;
}

/*******************************************************************
 * @brief           SaveThrottlePrecent
 * @brief           Saving data location for car throttle mismatch %
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
void SaveThrottlePrecent(int value){
    
}

/*******************************************************************
 * @brief           ReadThrottleTrigger
 * @brief           Reading data location for throttle max value for software safety system
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
int ReadThrottleTrigger(){
    
    return 0;
}

/*******************************************************************
 * @brief           SaveThrottleTrigger
 * @brief           Saving data location for throttle max value for software safety system
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
void SaveThrottleTrigger(int value){
    
}

/*******************************************************************
 * @brief           ReadBrakeTrigger
 * @brief           Reading data location for brake max value for software safety system
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
int ReadBrakeTrigger(){
    
    return 0;
}

/*******************************************************************
 * @brief           SaveBrakeTrigger
 * @brief           Saving data location for brake max value for software safety system
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
void SaveBrakeTrigger(int value){
    
}

/*******************************************************************
 * @brief           ReadBrakeLightTrigger
 * @brief           Reading data location for brake light threshold
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
int ReadBrakeLightTrigger(){
    
    return 0;
}

/*******************************************************************
 * @brief           SaveBrakeLightTrigger
 * @brief           Saving data location for brake light threshold
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
void SaveBrakeLightTrigger(int value){
    
}