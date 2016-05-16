/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - v3.00
        Device            :  PIC18F45K22
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20

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


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set TEMPEN aliases
#define TEMPEN_TRIS               TRISA0
#define TEMPEN_LAT                LATA0
#define TEMPEN_PORT               RA0
#define TEMPEN_ANS                ANSA0
#define TEMPEN_SetHigh()    do { LATA0 = 1; } while(0)
#define TEMPEN_SetLow()   do { LATA0 = 0; } while(0)
#define TEMPEN_Toggle()   do { LATA0 = ~LATA0; } while(0)
#define TEMPEN_GetValue()         RA0
#define TEMPEN_SetDigitalInput()    do { TRISA0 = 1; } while(0)
#define TEMPEN_SetDigitalOutput()   do { TRISA0 = 0; } while(0)

#define TEMPEN_SetAnalogMode()   do { ANSA0 = 1; } while(0)
#define TEMPEN_SetDigitalMode()   do { ANSA0 = 0; } while(0)

// get/set FlowControl aliases
#define FlowControl_TRIS               TRISC5
#define FlowControl_LAT                LATC5
#define FlowControl_PORT               RC5
#define FlowControl_ANS                ANSC5
#define FlowControl_SetHigh()    do { LATC5 = 1; } while(0)
#define FlowControl_SetLow()   do { LATC5 = 0; } while(0)
#define FlowControl_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define FlowControl_GetValue()         RC5
#define FlowControl_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define FlowControl_SetDigitalOutput()   do { TRISC5 = 0; } while(0)

#define FlowControl_SetAnalogMode()   do { ANSC5 = 1; } while(0)
#define FlowControl_SetDigitalMode()   do { ANSC5 = 0; } while(0)

// get/set LTC6804CS aliases
#define LTC6804CS_TRIS               TRISD3
#define LTC6804CS_LAT                LATD3
#define LTC6804CS_PORT               RD3
#define LTC6804CS_ANS                ANSD3
#define LTC6804CS_SetHigh()    do { LATD3 = 1; } while(0)
#define LTC6804CS_SetLow()   do { LATD3 = 0; } while(0)
#define LTC6804CS_Toggle()   do { LATD3 = ~LATD3; } while(0)
#define LTC6804CS_GetValue()         RD3
#define LTC6804CS_SetDigitalInput()    do { TRISD3 = 1; } while(0)
#define LTC6804CS_SetDigitalOutput()   do { TRISD3 = 0; } while(0)

#define LTC6804CS_SetAnalogMode()   do { ANSD3 = 1; } while(0)
#define LTC6804CS_SetDigitalMode()   do { ANSD3 = 0; } while(0)

// get/set SET aliases
#define SET_TRIS               TRISD6
#define SET_LAT                LATD6
#define SET_PORT               RD6
#define SET_ANS                ANSD6
#define SET_SetHigh()    do { LATD6 = 1; } while(0)
#define SET_SetLow()   do { LATD6 = 0; } while(0)
#define SET_Toggle()   do { LATD6 = ~LATD6; } while(0)
#define SET_GetValue()         RD6
#define SET_SetDigitalInput()    do { TRISD6 = 1; } while(0)
#define SET_SetDigitalOutput()   do { TRISD6 = 0; } while(0)

#define SET_SetAnalogMode()   do { ANSD6 = 1; } while(0)
#define SET_SetDigitalMode()   do { ANSD6 = 0; } while(0)

// get/set RESET aliases
#define RESET_TRIS               TRISD7
#define RESET_LAT                LATD7
#define RESET_PORT               RD7
#define RESET_ANS                ANSD7
#define RESET_SetHigh()    do { LATD7 = 1; } while(0)
#define RESET_SetLow()   do { LATD7 = 0; } while(0)
#define RESET_Toggle()   do { LATD7 = ~LATD7; } while(0)
#define RESET_GetValue()         RD7
#define RESET_SetDigitalInput()    do { TRISD7 = 1; } while(0)
#define RESET_SetDigitalOutput()   do { TRISD7 = 0; } while(0)

#define RESET_SetAnalogMode()   do { ANSD7 = 1; } while(0)
#define RESET_SetDigitalMode()   do { ANSD7 = 0; } while(0)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
*/