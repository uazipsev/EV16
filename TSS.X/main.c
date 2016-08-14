
/**
 *********************************************************************************************************
 *
 * @brief        TS - This device reads in sensors and converts them to EU 
 * @file         main.c
 * @author       Richard Johnson - Joey
 * @moduleID
 * @ingroup
 *
 *********************************************************************************************************
 * @note  The Firmware shall:
 *               -Read in IMU and convert to EU
 *               -Read in roter temp 
 *               -Wheel speed
 *               -Read RS485 BUS for data and reply with expectied data (set requested LED states and rely with button states)
 *********************************************************************************************************

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <stdlib.h>
#include "Communications.h"
#include "CarTempSens.h"
#include "mcc_generated_files/eusart1.h"
#include "bno055.h"
#include "mcc_generated_files/i2c1.h"

/*******************************************************************
 * @brief           Main
 * @brief           The main fcn of the code
 * @return          None
 * @note            The main loop is here
 *******************************************************************/
char I2CreadByte(char address, char subAddress);
char I2CwriteByte(char address, char subAddress);

void main(void) {
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowEnable();

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    EUSART1_Initialize();
    I2C1_Initialize();
    #define SLAVE_I2C_GENERIC_RETRY_MAX     2
    char address = 0;
    Setup();
    while (1) {
        //updateComms(); // This is for the RS485 communication. 
        //TempCalc(1);   //Gets ADC vales and convert them
        //TempCalc(2);
        //TempGet(1);    // Gets EU
        //TempGet(2);
        loop();
        Delay(1000);
        //char data = 0;
        //I2CwriteByte(0x29, data);
        //I2CreadByte(0x29, 1);
    }
}

char I2CreadByte(char address, char count)
{
	char data; // `data` will store the register data	 
//	Wire.beginTransmission(address);         // Initialize the Tx buffer
//	Wire.write(subAddress);	                 // Put slave register address in Tx buffer
//	Wire.endTransmission(I2C_NOSTOP);        // Send the Tx buffer, but send a restart to keep connection alive
////	Wire.endTransmission(false);             // Send the Tx buffer, but send a restart to keep connection alive
////	Wire.requestFrom(address, 1);  // Read one char from slave register address 
//	Wire.requestFrom(address, (size_t) 1);   // Read one char from slave register address 
//	data = Wire.read();                      // Fill Rx buffer with result
    I2C1_MESSAGE_STATUS status;
    char timeOut = 0;
    char data;
    while(status != I2C1_MESSAGE_FAIL)
    {
        // write one byte to EEPROM (3 is the number of bytes to write)
        I2C1_MasterRead( data,
                                count,
                                address,
                                &status);

        // wait for the message to be sent or status has changed.
        while(status == I2C1_MESSAGE_PENDING);

        if (status == I2C1_MESSAGE_COMPLETE)
            break;
        
        if (status == I2C1_MESSAGE_ADDRESS_NO_ACK)
            break;

        // if status is  I2C1_MESSAGE_ADDRESS_NO_ACK,
        //               or I2C1_DATA_NO_ACK,
        // The device may be busy and needs more time for the last
        // write so we can retry writing the data, this is why we
        // use a while loop here

        // check for max retry and skip this byte
//        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
//            break;
//        else
//            timeOut++;
    }
	return 0;                             // Return data read from slave register
}

char I2CwriteByte(char address, char subAddress)
{
//	Wire.beginTransmission(address);  // Initialize the Tx buffer
//	Wire.write(subAddress);           // Put slave register address in Tx buffer
//	Wire.write(data);                 // Put data in Tx buffer
//	Wire.endTransmission();           // Send the Tx buffer
    I2C1_MESSAGE_STATUS status;
    char timeOut = 0;
    char Data[3];
    Data[0] = 0;
    while(status != I2C1_MESSAGE_FAIL)
    {
        // write one byte to EEPROM (3 is the number of bytes to write)
        I2C1_MasterWrite( Data,1,address,&status);

        // wait for the message to be sent or status has changed.
        while(status == I2C1_MESSAGE_PENDING);

        if (status == I2C1_MESSAGE_COMPLETE)
            break;

        // if status is  I2C1_MESSAGE_ADDRESS_NO_ACK,
        //               or I2C1_DATA_NO_ACK,
        // The device may be busy and needs more time for the last
        // write so we can retry writing the data, this is why we
        // use a while loop here

        // check for max retry and skip this byte
        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
            break;
        else
            timeOut++;
    }
    timeOut = 0;
//    while(status != I2C1_MESSAGE_FAIL)
//    {
//        // write one byte to EEPROM (3 is the number of bytes to write)
//        I2C1_MasterWrite(  data,1,address,&status);
//
//        // wait for the message to be sent or status has changed.
//        while(status == I2C1_MESSAGE_PENDING);
//
//        if (status == I2C1_MESSAGE_COMPLETE)
//            break;
//
//        // if status is  I2C1_MESSAGE_ADDRESS_NO_ACK,
//        //               or I2C1_DATA_NO_ACK,
//        // The device may be busy and needs more time for the last
//        // write so we can retry writing the data, this is why we
//        // use a while loop here
//
//        // check for max retry and skip this byte
//        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
//            break;
//        else
//            timeOut++;
//    }   

}


/**
 End of File 
 
 */