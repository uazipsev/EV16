/*
 * File:   MCP4725.c
 * Author: Rick
 *
 * Created on May 20, 2015, 1:12 AM
 *
 * Datasheet: http://ww1.microchip.com/downloads/en/DeviceDoc/22039d.pdf
 *
 * This controls the DACs for the motor controller
 * It uses the a I2C library to control them
 *
 */

#include "MCP4725.h"
#include "I2C.h"
#include "PinDef.h"

char i2cdata[20];

//loads data to DAC 1

void SetDAC1(unsigned int value) {
    if ((value >= 0) && (value < 4096)) {
        i2cdata[0] = value >> 8;
        i2cdata[1] = value & 0x00ff;
        i2c_Write(DAC1Address, true, i2cdata, 2);
    }
}

//loads data to DAC 2

void SetDAC2(unsigned int value) {
    if ((value >= 0) && (value < 4096)) {
        i2cdata[0] = value >> 8;
        i2cdata[1] = value & 0x00ff;
        i2c_Write(DAC2Address, true, i2cdata, 2);
    }
}


//Set up DAC to save start up set point
//NOTE: this fcn needs revised. see pg 25 of Data sheet

void ConfigDAC(char address, unsigned int setpoint) {
    i2cdata[0] = setpoint >> 8;
    i2cdata[1] = setpoint & 0x00ff;
    i2cdata[0] = i2cdata[0] | 0x70; //program mode
    i2c_Write(address, true, i2cdata, 2);
}