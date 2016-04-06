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

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
char i2cread(void)
{
  //return Wire.receive();
  return 1;
}

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
void i2cwrite(char x)
{
  //Wire.send(x);
}

/**************************************************************************/
/*!
    @brief  Writes 16-bits to the specified destination register
*/
/**************************************************************************/
static void writeRegister(char i2cAddress, char reg, int value)
{
  //Wire.beginTransmission(i2cAddress);
  i2cwrite(reg);
  i2cwrite((value>>8));
  i2cwrite((value & 0xFF));
  //Wire.endTransmission();
}

/**************************************************************************/
/*!
    @brief  Writes 16-bits to the specified destination register
*/
/**************************************************************************/
int readRegister(char i2cAddress, char reg)
{
  //Wire.beginTransmission(i2cAddress);
  i2cwrite(ADS1015_REG_POINTER_CONVERT);
  //Wire.endTransmission();
  //Wire.requestFrom(i2cAddress, (uint8_t)2);
  return ((i2cread() << 8) | i2cread());  
}

/**************************************************************************/
/*!
    @brief  Sets up the HW (reads coefficients values, etc.)
*/
/**************************************************************************/
void ADS1015Begin() {
  //Wire.begin();
  // Initialise I2C Data object for Write operation   
    wData.buff=wBuff;
    wData.n=10;
    wData.addr=0x00; 
    wData.csel=0x00;
                  

// Initialise I2C Data Object for Read operation            
    rData.buff=rBuff;
    rData.n=10;
    rData.addr=0x00; 
    rData.csel=0x00;
    
  i2cmem.init(&i2cmem); 
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
int ADS1015readADC_SingleEnded(char channel){
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