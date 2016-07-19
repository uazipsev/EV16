/**
  ECCP2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eccp2.c

  @Summary
    This is the generated driver implementation file for the ECCP2 driver using MPLAB® Code Configurator

  @Description
    This source file provides APIs for ECCP2.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC18F45K22
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

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
#ifndef _ECCP2_H
#define _ECCP2_H

/**
  Section: Included Files
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

    /** Data Type Definition
     @Summary
       Defines the values to convert from 16bit to two 8 bit and viceversa

     @Description
       This routine used to get two 8 bit values from 16bit also
       two 8 bit value are combine to get 16bit.

     Remarks:
       None
     */

    typedef union CCPR2Reg_tag {

        struct {
            uint8_t ccpr2l;
            uint8_t ccpr2h;
        };

        struct {
            uint16_t ccpr2_16Bit;
        };
    } CCP_PERIOD_REG_T;

    /**
      Section: Capture Module APIs
     */

    /**
      @Summary
        Initializes the ECCP2

      @Description
        This routine initializes the ECCP2_Initialize.
        This routine must be called before any other ECCP2 routine is called.
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
        ECCP2_Initialize();
        </code>
     */
    void ECCP2_Initialize(void);

    /**
      @Summary
        Implements ISR

      @Description
        This routine is used to implement the ISR for the interrupt-driven
        implementations.

      @Returns
        None

      @Param
        None
     */
    void ECCP2_CaptureISR(void);

    /**
      @Summary
        CallBack function

      @Description
        This function is called from the Capture ISR. User can write there code in this function.

      @Preconditions
        Initialize the ECCP2 module with interrupt before calling this function.

      @Param
        captured value

      @Returns
        None

      @Example
        None
     */
    void ECCP2_CallBack(uint16_t capturedValue);

#ifdef __cplusplus  // Provide C++ Compatibility

}

#endif

#endif  //_ECCP2_H
/**
 End of File
 */

