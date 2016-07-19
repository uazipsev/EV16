#include "I2C.h"
#include "EEprom.h"

#define ADDRESS 0xA0

void EEpromInit(){
    InitI2C();
}

/**************************************************************************/
/*!
    @brief  Writes 8-bits to the specified destination register
*/
/**************************************************************************/
void writeRegister(char i2cAddress, char reg, int value)
{
	IdleI2C();						//Ensure Module is Idle
	StartI2C();						//Initiate start condition
	WriteI2C(i2cAddress << 1);	    //write 1 byte
	IdleI2C();						//Ensure module is Idle
	WriteI2C(reg);			    	//Write High word address
	IdleI2C();						//Ensure module is idle
    WriteI2C(value);				//Write Low word address
	NotAckI2C();					//Send Not Ack
	StopI2C();				        //Send stop condition
    
}

/**************************************************************************/
/*!
    @brief  Writes 8-bits to the specified destination register
*/
/**************************************************************************/
int readRegister(char i2cAddress, char reg)
{
    char data[3];
    IdleI2C();						    //Ensure Module is Idle
	StartI2C();						    //Initiate start condition
	WriteI2C(i2cAddress << 1);	        //write 1 byte
	IdleI2C();						    //Ensure module is Idle
    WriteI2C(reg);			    	    //Write Low word address
	IdleI2C();						    //Ensure module is idle
	RestartI2C();					    //Generate I2C Restart Condition
	WriteI2C((i2cAddress << 1) | 0x01);	//Write 1 byte - R/W bit should be 1 for read
	IdleI2C();						    //Ensure bus is idle
	getsI2C(data, 1);		     	    //Read in multiple bytes
	NotAckI2C();					    //Send Not Ack
	StopI2C();						    //Send stop condition
    
    return data[0];
}


char ReadCarDriver(){
    return readRegister(ADDRESS, 0);
}

void SaveCarDriver(char value){
    writeRegister(ADDRESS, 0,value);
}

int ReadThrottlePrecent(){
    
    return 0;
}

void SaveThrottlePrecent(int value){
    
}

int ReadThrottleTrigger(){
    
    return 0;
}

void SaveThrottleTrigger(int value){
    
}

int ReadBrakeTrigger(){
    
    return 0;
}

void SaveBrakeTrigger(int value){
    
}

int ReadBrakeLightTrigger(){
    
    return 0;
}

void SaveBrakeLightTrigger(int value){
    
}