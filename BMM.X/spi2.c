

#include <xc.h>
#include "spi2.h"
#include <stdio.h>

/**
  Section: Macro Declarations
*/

#define SPI_RX_IN_PROGRESS 0x0

/**
  Section: Module APIs
*/

void SPI2_Initialize(void)
{
    // Set the SPI2 module to the options selected in the User Interface
    SPI1CON1 = 0x0063;   //23  //This ets SPRE and PPRE to a 1:64 prescale   
    SPI1CON2 = 0x0000;
    SPI1STAT = 0x8000;    //Enables the module

}

uint8_t SPI2_Exchange8bit(uint8_t data)
{
    SPI1BUF = data & 0xff;    /*  byte write  */
    while(SPI1STATbits.SPITBF);
    data = SPI1BUF;               //Avoiding overflow when reading
    SPI1STATbits.SPIROV = 0;
    //SPI1BUF = 0x00;                  // initiate bus cycle 
    while(!SPI1STATbits.SPIRBF);
     /* Check for Receive buffer full status bit of status register*/
    if (SPI1STATbits.SPIRBF)
    { 
        SPI1STATbits.SPIROV = 0;
        return (SPI1BUF & 0xff);    /* return byte read */
    }
    return -1;                  		/* RBF bit is not set return error*/
}

uint8_t SPI2_Exchange8bitBuffer(uint8_t *dataIn, uint8_t bufLen, uint8_t *dataOut)
{
    uint8_t bytesWritten = 0;

    if(bufLen != 0)
    {
        if(dataIn != NULL)
        {
            while(bytesWritten < bufLen)
            {
                if(dataOut == NULL)
                {
                    SPI2_Exchange8bit(dataIn[bytesWritten]);
                }
                else
                {
                    dataOut[bytesWritten] = SPI2_Exchange8bit(dataIn[bytesWritten]);
                }

                bytesWritten++;
            }
        }
        else
        {
            if(dataOut != NULL)
            {
                while(bytesWritten < bufLen )
                {
                    dataOut[bytesWritten] = SPI2_Exchange8bit(DUMMY_DATA);

                    bytesWritten++;
                }
            }
        }
    }

    return bytesWritten;
}

bool SPI2_IsBufferFull(void)
{
    //return (SSP2STATbits.BF);
    return (1);
}

bool SPI2_HasWriteCollisionOccured(void)
{
    //return (SSP2CON1bits.WCOL);
    return (1);
}

void SPI2_ClearWriteCollisionStatus(void)
{
    //SSP2CON1bits.WCOL = 0;
}
/**
 End of File
*/