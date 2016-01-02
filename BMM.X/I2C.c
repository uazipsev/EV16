#include <xc.h>
#include <stdbool.h>
#include "I2C.h"
#include <i2c.h>

void i2c_wait(unsigned int cnt) {
    while (--cnt) {
        asm("nop");
        asm("nop");
    }
}

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
        while (DataSz) {
            MasterWriteI2C1(data[Index++]);
            IdleI2C1(); //Wait to complete

            DataSz--;

            //ACKSTAT is 0 when slave acknowledge,
            //if 1 then slave has not acknowledge the data.
            if (I2C1STATbits.ACKSTAT)
                break;
        }
    } else //read address
    {
        MasterWriteI2C1(((address << 1) | 1));
        IdleI2C1(); //Wait to complete
        while (DataSz) {
            data[Index++]=MasterReadI2C1();
            AckI2C1();
            IdleI2C1(); //Wait to complete

            DataSz--;

            //ACKSTAT is 0 when slave acknowledge,
            //if 1 then slave has not acknowledge the data.
//            if (I2C1STATbits.ACKSTAT)
//                break;
        }
    }



    StopI2C1(); //Send the Stop condition
    IdleI2C1(); //Wait to complete   
}

void i2c_init(void) {
    I2C1BRG = 0x0258;
    I2C1CON = 0x1200;
    I2C1RCV = 0x0000;
    I2C1TRN = 0x0000;
    //Now we can enable the peripheral
    I2C1CON = 0x9200;
}