/**
  MSSP1 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    mssp1.h

  @Summary
    This is the generated header file for the MSSP1 driver using MPLAB(c) Code Configurator

  @Description
    This header file provides APIs for MSSP1.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - v3.00
        Device            :  PIC18F45K22
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20
*******************************************************************************/

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#ifndef _SPI1_H
#define _SPI1_H

/**
  Section: Included Files
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: Macro Declarations
*/

#define DUMMY_DATA 0x0

/**
  Section: SPI1 Module APIs
*/

/**
  @Summary
    Initializes the SPI1

  @Description
    This routine initializes the SPI1.
    This routine must be called before any other MSSP1 routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    

  @Example
    <code>
    uint8_t     myWriteBuffer[MY_BUFFER_SIZE];
    uint8_t     myReadBuffer[MY_BUFFER_SIZE];
    uint8_t     writeData;
    uint8_t     readData;
    uint8_t     total;

    SPI1_Initialize();

    total = 0;
    do
    {
        total = SPI1_Exchange8bitBuffer(&myWriteBuffer[total], MY_BUFFER_SIZE - total, &myWriteBuffer[total]);

        // Do something else...

    } while(total < MY_BUFFER_SIZE);

    readData = SPI1_Exchange8bit(writeData);
    </code>
 */
void SPI1_Initialize(void);

/**
  @Summary
    Exchanges a data byte over SPI1

  @Description
    This routine exchanges a data byte over SPI1 bus.
    This is a blocking routine.

  @Preconditions
    The SPI1_Initialize() routine should be called
    prior to use this routine.

  @Param
    data - data byte to be transmitted over SPI1 bus

  @Returns
    The received byte over SPI1 bus

  @Example
    <code>
    uint8_t     writeData;
    uint8_t     readData;
    uint8_t     readDummy;

    SPI1_Initialize();

    // for transmission over SPI bus
    readDummy = SPI1_Exchange8bit(writeData);

    // for reception over SPI bus
    readData = SPI1_Exchange8bit(DUMMY_DATA);
    </code>
 */
uint8_t SPI1_Exchange8bit(uint8_t data);

 /**
  @Summary
    Exchanges buffer of data over SPI1

  @Description
    This routine exchanges buffer of data (of size one byte) over SPI1 bus.
    This is a blocking routine.

  @Preconditions
    The SPI1_Initialize() routine should be called
    prior to use this routine.

  @Param
    dataIn  - Buffer of data to be transmitted over SPI1.
    bufLen  - Number of bytes to be exchanged.
    dataOut - Buffer of data to be received over SPI1.

  @Returns
    Number of bytes exchanged over SPI1.

  @Example
    <code>
    uint8_t     myWriteBuffer[MY_BUFFER_SIZE];
    uint8_t     myReadBuffer[MY_BUFFER_SIZE];
    uint8_t     total;

    SPI1_Initialize();

    total = 0;
    do
    {
        total = SPI1_Exchange8bitBuffer(&myWriteBuffer[total], MY_BUFFER_SIZE - total, &myWriteBuffer[total]);

        // Do something else...

    } while(total < MY_BUFFER_SIZE);
    </code>
 */
uint8_t SPI1_Exchange8bitBuffer(uint8_t *dataIn, uint8_t bufLen, uint8_t *dataOut);

/**
  @Summary
    Gets the SPI1 buffer full status

  @Description
    This routine gets the SPI1 buffer full status

  @Preconditions
    The SPI1_Initialize() routine should be called
    prior to use this routine.

  @Param
    None

  @Returns
    true  - if the buffer is full
    false - if the buffer is not full.

  @Example
    Refer to SPI1_Initialize() for an example
 */
bool SPI1_IsBufferFull(void);

/**
  @Summary
    Gets the status of write collision.

  @Description
    This routine gets the status of write collision.

  @Preconditions
    The SPI1_Initialize() routine must have been called prior to use this routine.

  @Param
    None

  @Returns
    true  - if the write collision has occurred.
    false - if the write collision has not occurred.

  @Example
    if(SPI1_HasWriteCollisionOccured())
    {
        SPI1_ClearWriteCollisionStatus();
    }
*/
bool SPI1_HasWriteCollisionOccured(void);

/**
  @Summary
    Clears the status of write collision.

  @Description
    This routine clears the status of write collision.

  @Preconditions
    The SPI1_Initialize() routine must have been called prior to use this routine.

  @Param
    None

  @Returns
    None

  @Example
    if(SPI1_HasWriteCollisionOccured())
    {
        SPI1_ClearWriteCollisionStatus();
    }
*/
void SPI1_ClearWriteCollisionStatus(void);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif // _SPI1_H
/**
 End of File
*/
