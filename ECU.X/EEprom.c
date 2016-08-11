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
	AckI2C();                       //Wait for ACK
    IdleI2C();                      //Ensure module is Idle
	WriteI2C(reg);			    	//Write High word address
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
char readRegister(char i2cAddress, char reg)
{
    IdleI2C();
    StartI2C();						    //Initiate start condition
	WriteI2C(i2cAddress << 1);	        //write 1 byte
    AckI2C();   					    //Wait for ACK
	IdleI2C();						    //Ensure module is Idle
    WriteI2C(reg);			    	    //Write Low word address
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
      SetBrakeLightValue(ReadBrakeLightTrigger());
      //char z = 0;
//    for(z=0;z<16;z++){
//        writeRegister(ADDRESS, z, z);
//        Delay(2);
//    }
//    Delay(10);
//    for(z=0;z<16;z++){
//        readRegister(ADDRESS, z);
//        Delay(5);
//    }
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
    return readRegister(ADDRESS, 5);
}

/*******************************************************************
 * @brief           SaveThrottlePrecent
 * @brief           Saving data location for car throttle mismatch %
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
void SaveThrottlePrecent(int value){
    writeRegister(ADDRESS, 5, value);
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
    return readRegister(ADDRESS, 2);
}

/*******************************************************************
 * @brief           SaveBrakeTrigger
 * @brief           Saving data location for brake max value for software safety system
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
void SaveBrakeTrigger(int value){
    writeRegister(ADDRESS, 2, value);
}

/*******************************************************************
 * @brief           ReadBrakeLightTrigger
 * @brief           Reading data location for brake light threshold
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
int ReadBrakeLightTrigger(){
    return readRegister(ADDRESS, 3);
}

/*******************************************************************
 * @brief           SaveBrakeLightTrigger
 * @brief           Saving data location for brake light threshold
 * @return          none
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/
void SaveBrakeLightTrigger(int value){
    writeRegister(ADDRESS, 3, value);
}