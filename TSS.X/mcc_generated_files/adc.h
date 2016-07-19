/**
  ADC Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    adc.h

  @Summary
    This is the generated header file for the ADC driver using MPLAB® Code Configurator

  @Description
    This header file provides APIs for driver for ADC.
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

#ifndef _ADC_H
#define _ADC_H

/**
  Section: Included Files
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

    /**
      Section: Data Types Definitions
     */

    /**
     *  result size of an A/D conversion
     */

    typedef uint16_t adc_result_t;

    /** ADC Channel Definition

     @Summary
       Defines the channels available for conversion.

     @Description
       This routine defines the channels that are available for the module to use.

     Remarks:
       None
     */

    typedef enum {
        channel_CTMU = 0x1D,
        channel_DAC = 0x1E,
        channel_FVRBuf2 = 0x1F,
        Temp1 = 0x00,
        Temp2 = 0x01
    } adc_channel_t;

    /**
      Section: ADC Module APIs
     */

    /**
      @Summary
        Initializes the ADC

      @Description
        This routine initializes the Initializes the ADC.
        This routine must be called before any other ADC routine is called.
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
        uint16_t convertedValue;

        ADC_Initialize();
        convertedValue = ADC_GetConversionResult();
        </code>
     */
    void ADC_Initialize(void);

    /**
      @Summary
        Allows selection of a channel for conversion

      @Description
        This routine is used to select desired channel for conversion.
        available

      @Preconditions
        ADC_Initialize() function should have been called before calling this function.

      @Returns
        None

      @Param
        Pass in required channel number
        "For available channel refer to enum under adc.h file"

      @Example
        <code>
        uint16_t convertedValue;

        ADC_Initialize();
        ADC_StartConversion(AN1_Channel);
        convertedValue = ADC_GetConversionResult();
        </code>
     */
    void ADC_StartConversion(adc_channel_t channel);

    /**
      @Summary
        Returns true when the conversion is completed otherwise false.

      @Description
        This routine is used to determine if conversion is completed.
        When conversion is complete routine returns true. It returns false otherwise.

      @Preconditions
        ADC_Initialize() and ADC_StartConversion(adc_channel_t channel)
        function should have been called before calling this function.

      @Returns
        true  - If conversion is complete
        false - If conversion is not completed

      @Param
        None

      @Example
        <code>
        uint16_t convertedValue;

        ADC_Initialize();
        ADC_StartConversion(AN1_Channel);

        while(!ADC_IsConversionDone());
        convertedValue = ADC_GetConversionResult();
        </code>
     */
    bool ADC_IsConversionDone();

    /**
      @Summary
        Returns the ADC conversion value.

      @Description
        This routine is used to get the analog to digital converted value. This
        routine gets converted values from the channel specified.

      @Preconditions
        This routine returns the conversion value only after the conversion is complete.
        Completion status can be checked using
        ADC_IsConversionDone() routine.

      @Returns
        Returns the converted value.

      @Param
        None

      @Example
        <code>
        uint16_t convertedValue;

        ADC_Initialize();
        ADC_StartConversion(AN1_Channel);

        while(ADC_IsConversionDone());

        convertedValue = ADC_GetConversionResult();
        </code>
     */
    adc_result_t ADC_GetConversionResult(void);

    /**
      @Summary
        Returns the ADC conversion value
        also allows selection of a channel for conversion.

      @Description
        This routine is used to select desired channel for conversion
        and to get the analog to digital converted value.

      @Preconditions
        ADC_Initialize() function should have been called before calling this function.

      @Returns
        Returns the converted value.

      @Param
        Pass in required channel number.
        "For available channel refer to enum under adc.h file"

      @Example
        <code>
        uint16_t convertedValue;

        ADC_Initialize();

        conversion = ADC_GetConversion(AN1_Channel);
        </code>
     */
    adc_result_t ADC_GetConversion(adc_channel_t channel);

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
    void ADC_ISR(void);

#ifdef __cplusplus  // Provide C++ Compatibility

}

#endif

#endif	//_ADC_H
/**
 End of File
 */

