/*
 * File:   ADS1015.c
 * Author: Rick
 *
 * Created on May 20, 2015, 1:12 AM
 *
 * Datasheet: http://www.ti.com/lit/ds/symlink/ads1015-q1.pdf
 *
 * This controls the ADC's for the Current Board!
 * It uses the a I2C library to control them
 *
 */

#include "ADS1015.h"
#include "Function.h"
#include "I2C.h"

// Instance-specific properties
char i2cAddress;
char conversionDelay = ADS1015_CONVERSIONDELAY;
char bitShift = 4;
int  IC_gain = GAIN_ONE;

/**************************************************************************/
/*!
    @brief  Writes 16-bits to the specified destination register
*/
/**************************************************************************/
void writeRegister(char i2cAddress, char reg, int value)
{
//	IdleI2C();						//Ensure Module is Idle
//	StartI2C();						//Initiate start condition
//	WriteI2C(i2cAddress);			//write 1 byte
//	IdleI2C();						//Ensure module is Idle
//	WriteI2C(reg);			    	//Write High word address
//	IdleI2C();						//Ensure module is idle
//	WriteI2C(value);				//Write Low word address
//	NotAckI2C();					//Send Not Ack
//	//StopI2C();						//Send stop condition
    
    char data[2];
    data[0] = reg;
    data[1] = value;
    i2c_Write(i2cAddress, 1, data, 2);
}

/**************************************************************************/
/*!
    @brief  Writes 16-bits to the specified destination register
*/
/**************************************************************************/
int readRegister(char i2cAddress, char reg)
{
//    int data;
//    IdleI2C();						//Ensure Module is Idle
//	StartI2C();						//Initiate start condition
//	WriteI2C(i2cAddress);			//write 1 byte
//	IdleI2C();						//Ensure module is Idle
//    WriteI2C(reg);				//Write Low word address
//	IdleI2C();						//Ensure module is idle
//	RestartI2C();					//Generate I2C Restart Condition
//	WriteI2C(i2cAddress | 0x01);	//Write 1 byte - R/W bit should be 1 for read
//	IdleI2C();						//Ensure bus is idle
//	getsI2C(data, 2);			//Read in multiple bytes
//	NotAckI2C();					//Send Not Ack
//	//StopI2C();						//Send stop condition
    
    char data[2];
    data[0] = reg;
    i2c_Write(i2cAddress, 1, data, 1);
    i2c_Write(i2cAddress, 0, data, 0);
    return data[0] | data[1] << 8;;
}

/**************************************************************************/
/*!
    @brief  Sets up the HW (reads coefficients values, etc.)
*/
/**************************************************************************/
void ADS1015Begin() {
    InitI2C();
}

/**************************************************************************/
/*!
    @brief  Sets the gain and input voltage range
*/
/**************************************************************************/
void ADS1015SetGain(gain_enum gain)
{
  IC_gain = gain;
}

/**************************************************************************/
/*!
    @brief  Gets a single-ended ADC reading from the specified channel
*/
/**************************************************************************/
int ADS1015readADC_SingleEnded(char channel, char i2cAddress){
  if (channel > 3)
  {
    return 0;
  }
  
  // Start with default values
  int config =  ADS1015_REG_CONFIG_CQUE_NONE    | // Disable the comparator (default val)
                ADS1015_REG_CONFIG_CLAT_NONLAT  | // Non-latching (default val)
                ADS1015_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   (default val)
                ADS1015_REG_CONFIG_CMODE_TRAD   | // Traditional comparator (default val)
                ADS1015_REG_CONFIG_DR_1600SPS   | // 1600 samples per second (default)
                ADS1015_REG_CONFIG_MODE_SINGLE;   // Single-shot mode (default)

  // Set PGA/voltage range
  config |= IC_gain;

  // Set single-ended input channel
  switch (channel)
  {
    case (0):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_0;
      break;
    case (1):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_1;
      break;
    case (2):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_2;
      break;
    case (3):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_3;
      break;
  }

  // Set start single-conversion bit
  config |= ADS1015_REG_CONFIG_OS_SINGLE;

  // Write config register to the ADC
  writeRegister(i2cAddress, ADS1015_REG_POINTER_CONFIG, config);

  // Wait for the conversion to complete
  Delay(conversionDelay);

  // Read the conversion results
  // Shift 12-bit results right 4 bits for the ADS1015
  return readRegister(i2cAddress, ADS1015_REG_POINTER_CONVERT) >> bitShift;  
}