#include "I2C.h"
#include <i2c.h>
#include <stdbool.h>


/*********************************************************************
* Function:        InitI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Initialises the I2C(1) peripheral
*
* Note:			Sets up Master mode, No slew rate control, 100Khz
********************************************************************/

void InitI2C(void)
{	
	//This function will initialize the I2C(1) peripheral.
	//First set the I2C(1) BRG Baud Rate.

	//Consult the dSPIC Data Sheet for information on how to calculate the
	//Baud Rate.
    
    ODCBbits.ODCB8 = 1;
    ODCBbits.ODCB9 = 1;
    
    TRISBbits.TRISB8 = 1;
    TRISBbits.TRISB9 = 1;

	I2C2BRG = 0x0258; 

	//Now we will initialise the I2C peripheral for Master Mode, No Slew Rate
	//Control, and leave the peripheral switched off.
	
	I2C2CON = 0x1200;
	
	I2C2RCV = 0x0000;
	I2C2TRN = 0x0000;
	//Now we can enable the peripheral
	
	I2C2CON = 0x9200;
}

/*********************************************************************
* Function:        StartI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates an I2C Start Condition
*
* Note:			None
********************************************************************/
void StartI2C(void)
{
	//This function generates an I2C start condition and returns status 
	//of the Start.

	I2C2CONbits.SEN = 1;		//Generate Start COndition
	while (I2C2CONbits.SEN);	//Wait for Start COndition
	//return(I2C1STATbits.S);	//Optionally return status
}


/*********************************************************************
* Function:        RestartI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates a restart condition and optionally returns status
*
* Note:			None
********************************************************************/
void RestartI2C(void)
{
	//This function generates an I2C Restart condition and returns status 
	//of the Restart.

	I2C2CONbits.RSEN = 1;		//Generate Restart		
	while (I2C2CONbits.RSEN);	//Wait for restart	
	//return(I2C1STATbits.S);	//Optional - return status
}


/*********************************************************************
* Function:        StopI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates a bus stop condition
*
* Note:			None
********************************************************************/
char StopI2C(void)
{
	//This function generates an I2C stop condition and returns status 
	//of the Stop.

	I2C2CONbits.PEN = 1;		//Generate Stop Condition
	while (I2C2CONbits.PEN);	//Wait for Stop
	return(I2C2STATbits.P);	//Optional - return status
}


/*********************************************************************
* Function:        WriteI2C()
*
* Input:		Byte to write.
*
* Output:		None.
*
* Overview:		Writes a byte out to the bus
*
* Note:			None
********************************************************************/
void WriteI2C(unsigned char byte)
{
	//This function transmits the byte passed to the function
	//while (I2C1STATbits.TRSTAT);	//Wait for bus to be idle
	I2C2TRN = byte;					//Load byte to I2C1 Transmit buffer
	while (I2C2STATbits.TBF);		//wait for data transmission

}


/*********************************************************************
* Function:        IdleI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Waits for bus to become Idle
*
* Note:			None
********************************************************************/
void IdleI2C(void)
{
	while (I2C2STATbits.TRSTAT);		//Wait for bus Idle
}


/*********************************************************************
* Function:        ACKStatus()
*
* Input:		None.
*
* Output:		Acknowledge Status.
*
* Overview:		Return the Acknowledge status on the bus
*
* Note:			None
********************************************************************/
char ACKStatus(void)
{
	return (!I2C2STATbits.ACKSTAT);		//Return Ack Status
}


/*********************************************************************
* Function:        NotAckI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates a NO Acknowledge on the Bus
*
* Note:			None
********************************************************************/
void NotAckI2C(void)
{
	I2C2CONbits.ACKDT = 1;			//Set for NotACk
	I2C2CONbits.ACKEN = 1;
	//while(I2C1CONbits.ACKEN);		//wait for ACK to complete
	I2C2CONbits.ACKDT = 0;			//Set for NotACk
}


/*********************************************************************
* Function:        AckI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates an Acknowledge.
*
* Note:			None
********************************************************************/
void AckI2C(void)
{
	I2C2CONbits.ACKDT = 0;			//Set for ACk
	I2C2CONbits.ACKEN = 1;
	while(I2C2CONbits.ACKEN);		//wait for ACK to complete
}


/*********************************************************************
* Function:       getsI2C()
*
* Input:		array pointer, Length.
*
* Output:		None.
*
* Overview:		read Length number of Bytes into array
*
* Note:			None
********************************************************************/
char getsI2C(char *rdptr, unsigned char Length)
{
	while (Length --)
	{
		*rdptr++ = getI2C();		//get a single byte
		
		if(I2C2STATbits.BCL)		//Test for Bus collision
		{
			return(1);
		}

		if(Length)
		{
			AckI2C();				//Acknowledge until all read
		}
	}
	return(0);
}


/*********************************************************************
* Function:        getI2C()
*
* Input:		None.
*
* Output:		contents of I2C1 receive buffer.
*
* Overview:		Read a single byte from Bus
*
* Note:			None
********************************************************************/
char getI2C(void)
{
	I2C2CONbits.RCEN = 1;			//Enable Master receive
	Nop();
	while(!I2C2STATbits.RBF);		//Wait for receive bufer to be full
	return(I2C2RCV);				//Return data in buffer
}


void i2c_wait(unsigned int cnt) {
    while (--cnt) {
        asm("nop");
        asm("nop");
    }
}

//void i2c_Write(char address, bool read_write, char *data, int numofbytes) {
//    int DataSz;
//    int Index = 0;
//    DataSz = numofbytes;
//
//    StartI2C1(); //Send the Start Bit
//    IdleI2C1(); //Wait to complete
//    if (read_write == 1) //write address
//    {
//        MasterWriteI2C1(((address << 1) | 0));
//        IdleI2C1(); //Wait to complete    
//        while (DataSz) {
//            MasterWriteI2C1(data[Index++]);
//            IdleI2C1(); //Wait to complete
//
//            DataSz--;
//
//            //ACKSTAT is 0 when slave acknowledge,
//            //if 1 then slave has not acknowledge the data.
//            if (I2C1STATbits.ACKSTAT)
//                break;
//        }
//    } else //read address
//    {
//        MasterWriteI2C1(((address << 1) | 1));
//        IdleI2C1(); //Wait to complete
//        while (DataSz) {
//            data[Index++]=MasterReadI2C1();
//            AckI2C1();
//            IdleI2C1(); //Wait to complete
//
//            DataSz--;
//
//            //ACKSTAT is 0 when slave acknowledge,
//            //if 1 then slave has not acknowledge the data.
////            if (I2C1STATbits.ACKSTAT)
////                break;
//        }
//    }
//
//
//
//    StopI2C1(); //Send the Stop condition
//    IdleI2C1(); //Wait to complete   
//}