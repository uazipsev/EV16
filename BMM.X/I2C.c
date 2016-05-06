#include "I2C.h"
#include <i2c.h>


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
unsigned int InitI2C(void)
{	
	//This function will initialize the I2C(1) peripheral.
	//First set the I2C(1) BRG Baud Rate.

	//Consult the dSPIC Data Sheet for information on how to calculate the
	//Baud Rate.

	I2C1BRG = 0x002F; 

	//Now we will initialise the I2C peripheral for Master Mode, No Slew Rate
	//Control, and leave the peripheral switched off.
	
	I2C1CON = 0x1200;
	
	I2C1RCV = 0x0000;
	I2C1TRN = 0x0000;
	//Now we can enable the peripheral
	
	I2C1CON = 0x9200;
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
unsigned int StartI2C(void)
{
	//This function generates an I2C start condition and returns status 
	//of the Start.

	I2C1CONbits.SEN = 1;		//Generate Start COndition
	while (I2C1CONbits.SEN);	//Wait for Start COndition
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
unsigned int RestartI2C(void)
{
	//This function generates an I2C Restart condition and returns status 
	//of the Restart.

	I2C1CONbits.RSEN = 1;		//Generate Restart		
	while (I2C1CONbits.RSEN);	//Wait for restart	
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
unsigned int StopI2C(void)
{
	//This function generates an I2C stop condition and returns status 
	//of the Stop.

	I2C1CONbits.PEN = 1;		//Generate Stop Condition
	while (I2C1CONbits.PEN);	//Wait for Stop
	return(I2C1STATbits.P);	//Optional - return status
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
unsigned int WriteI2C(unsigned char byte)
{
	//This function transmits the byte passed to the function
	//while (I2C1STATbits.TRSTAT);	//Wait for bus to be idle
	I2C1TRN = byte;					//Load byte to I2C1 Transmit buffer
	while (I2C1STATbits.TBF);		//wait for data transmission

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
unsigned int IdleI2C(void)
{
	while (I2C1STATbits.TRSTAT);		//Wait for bus Idle
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
unsigned int ACKStatus(void)
{
	return (!I2C1STATbits.ACKSTAT);		//Return Ack Status
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
unsigned int NotAckI2C(void)
{
	I2C1CONbits.ACKDT = 1;			//Set for NotACk
	I2C1CONbits.ACKEN = 1;
	while(I2C1CONbits.ACKEN);		//wait for ACK to complete
	I2C1CONbits.ACKDT = 0;			//Set for NotACk
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
	I2C1CONbits.ACKDT = 0;			//Set for ACk
	I2C1CONbits.ACKEN = 1;
	while(I2C1CONbits.ACKEN);		//wait for ACK to complete
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
unsigned int getsI2C(unsigned char *rdptr, unsigned char Length)
{
	while (Length --)
	{
		*rdptr++ = getI2C();		//get a single byte
		
		if(I2C1STATbits.BCL)		//Test for Bus collision
		{
			return(-1);
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
unsigned int getI2C(void)
{
	I2C1CONbits.RCEN = 1;			//Enable Master receive
	Nop();
	while(!I2C1STATbits.RBF);		//Wait for receive bufer to be full
	return(I2C1RCV);				//Return data in buffer
}


/*********************************************************************
* Function:        EEAckPolling()
*
* Input:		Control byte.
*
* Output:		error state.
*
* Overview:		polls the bus for an Acknowledge from device
*
* Note:			None
********************************************************************/
unsigned int EEAckPolling(unsigned char control)
{
	IdleI2C();				//wait for bus Idle
	StartI2C();				//Generate Start condition
	
	if(I2C1STATbits.BCL)
	{
		return(-1);			//Bus collision, return
	}

	else
	{
		if(WriteI2C(control))
		{
			return(-3);		//error return
		}

		IdleI2C();			//wait for bus idle
		if(I2C1STATbits.BCL)
		{
			return(-1);		//error return
		}

		while(ACKStatus())
		{
			RestartI2C();	//generate restart
			if(I2C1STATbits.BCL)
			{
				return(-1);	//error return
			}

			if(WriteI2C(control))
			{
				return(-3);
			}

			IdleI2C();
		}
	}
	StopI2C();				//send stop condition
	if(I2C1STATbits.BCL)
	{
		return(-1);
	}
	return(0);
}