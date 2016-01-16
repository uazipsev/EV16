/*
 * File:   I2C.c
 * Author: Rick
 *
 * Created on May 20, 2015, 1:12 AM
 *
 * This controls the I2C for the dsPIC family
 * As of right now It needs code added to read in I2C data
 *
 */

#include <xc.h>
#include <stdbool.h>
#include "I2C.h"
#include <i2c.h>

char * i2cBuffer;

enum i2cState {
    startWrite = 0,
    sendAddress = 1,
    waitI2CIdle = 2,
    writeByte = 3,
    stopBus = 4,
    haltBus = 5
} writeState;

bool writeInProgress = false;

//I2C init code - startup I2C

void i2c_init(void) {
    I2C1BRG = 0x0258; //baud
    I2C1CON = 0x1200;
    I2C1RCV = 0x0000;
    I2C1TRN = 0x0000;
    //Now we can enable the peripheral
    I2C1CON = 0x9200;
}

// Wait code for I2C code
// Unused ATM

void i2c_wait(unsigned int cnt) {
    while (--cnt) {
        asm("nop");
        asm("nop");
    }
}

//This fcn writes dat to the I@C bus

void i2c_Write(char address, bool read_write, char *data, int numofbytes) {
    int DataSz;
    int Index = 0;
    DataSz = numofbytes;

    StartI2C1(); //Send the Start Bit
    IdleI2C1(); //Wait to complete
    if (read_write == 1) //write address
    {
        MasterWriteI2C1(((address << 1) | 0));
        IdleI2C1(); //Wait to complete
    } else //read address
    {
        MasterWriteI2C1(((address << 1) | 1));
        IdleI2C1(); //Wait to complete
    }

    while (DataSz) {
        MasterWriteI2C1(data[Index++]);
        IdleI2C1(); //Wait to complete

        DataSz--;

        //ACKSTAT is 0 when slave acknowledge,
        //if 1 then slave has not acknowledge the data.
        if (I2C1STATbits.ACKSTAT)
            break;
    }
//    //WHAT IS THIS?
//    status = MasterputsI2C1(pWrite);
//
//    if (status == -3)
//        while (1);

    StopI2C1(); //Send the Stop condition
    IdleI2C1(); //Wait to complete

    //    // wait for device to complete write process. poll the ack status
    //    while (1) {
    //        i2c_wait(10);
    //
    //        StartI2C1(); //Send the Start Bit
    //        IdleI2C1(); //Wait to complete
    //
    //        MasterWriteI2C1(i2cData[0]);
    //        IdleI2C1(); //Wait to complete
    //
    //        if (I2C1STATbits.ACKSTAT == 0) //eeprom has acknowledged
    //        {
    //            StopI2C1(); //Send the Stop condition
    //            IdleI2C1(); //Wait to complete
    //            break;
    //        }
    //
    //        StopI2C1(); //Send the Stop condition
    //        IdleI2C1(); //Wait to complete
    //    }
}

bool i2c_startCommand() {
    return true;
}

bool i2c_idle() {
    return true;
}

bool i2c_writeByte(char c) {
    return true;
}

bool i2c_addressSend(char addr) {
    return true;
}

bool i2c_stopCommand() {
    return true;
}

bool i2c_haltBus() {
    return true;
}

void writeStateUpdate() {
    static int byteNum;
    if (writeInProgress) {
        switch (writeState) {
            case startWrite:
                if (i2c_startCommand()) {
                    writeState++;
                }
                break;
            case sendAddress:
                if (i2c_addressSend(0x60)) {
                    writeState++;
                }
                break;
            case waitI2CIdle:
                if (i2c_idle()) {
                    writeState++;
                }
                break;
            case writeByte:
                if (i2c_writeByte(i2cBuffer[byteNum])) {
                    writeState++;
                }
                break;
            case stopBus:
                if (i2c_stopCommand()) {
                    writeState++;
                }
                break;
            case haltBus:
                if (i2c_haltBus()) {
                    writeState++;
                }
                break;
        }
    }
}

void readStateUpdate() {

}

void i2cUpdate() {
    writeStateUpdate();
    readStateUpdate();
}
