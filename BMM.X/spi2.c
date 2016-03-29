

#include <xc.h>
#include "spi2.h"

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
    
    // R_nW write_noTX; P stopbit_notdetected; S startbit_notdetected; BF RCinprocess_TXcomplete; SMP Middle; UA dontupdate; CKE Idle to Active; D_nA lastbyte_address; 
    //SSP2STAT = 0x00;
    
    // SSPEN enabled; WCOL no_collision; CKP Idle:Low, Active:High; SSPM FOSC/4; SSPOV no_overflow; 
    //SSP2CON1 = 0x20;
    
    // SSPADD 1; 
    //SSP2ADD = 0x01;
}

uint8_t SPI2_Exchange8bit(uint8_t data)
{
    // Clear the Write Collision flag, to allow writing
    /*
    SSP2CON1bits.WCOL = 0;

    SSP2BUF = data;

    while(SSP2STATbits.BF == SPI_RX_IN_PROGRESS)
    {
    }

    return (SSP2BUF);
    */
    return (1);
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