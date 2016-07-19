/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB® Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC18F45K22
        Version           :  1.01
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

// get/set Temp1 aliases
#define Temp1_TRIS               TRISA0
#define Temp1_LAT                LATA0
#define Temp1_PORT               PORTAbits.RA0
#define Temp1_ANS                ANSA0
#define Temp1_SetHigh()    do { LATA0 = 1; } while(0)
#define Temp1_SetLow()   do { LATA0 = 0; } while(0)
#define Temp1_Toggle()   do { LATA0 = ~LATA0; } while(0)
#define Temp1_GetValue()         PORTAbits.RA0
#define Temp1_SetDigitalInput()    do { TRISA0 = 1; } while(0)
#define Temp1_SetDigitalOutput()   do { TRISA0 = 0; } while(0)

#define Temp1_SetAnalogMode()   do { ANSA0 = 1; } while(0)
#define Temp1_SetDigitalMode()   do { ANSA0 = 0; } while(0)
// get/set Temp2 aliases
#define Temp2_TRIS               TRISA1
#define Temp2_LAT                LATA1
#define Temp2_PORT               PORTAbits.RA1
#define Temp2_ANS                ANSA1
#define Temp2_SetHigh()    do { LATA1 = 1; } while(0)
#define Temp2_SetLow()   do { LATA1 = 0; } while(0)
#define Temp2_Toggle()   do { LATA1 = ~LATA1; } while(0)
#define Temp2_GetValue()         PORTAbits.RA1
#define Temp2_SetDigitalInput()    do { TRISA1 = 1; } while(0)
#define Temp2_SetDigitalOutput()   do { TRISA1 = 0; } while(0)

#define Temp2_SetAnalogMode()   do { ANSA1 = 1; } while(0)
#define Temp2_SetDigitalMode()   do { ANSA1 = 0; } while(0)
// get/set CCP2 aliases
#define CCP2_TRIS               TRISC1
#define CCP2_LAT                LATC1
#define CCP2_PORT               PORTCbits.RC1
#define CCP2_SetHigh()    do { LATC1 = 1; } while(0)
#define CCP2_SetLow()   do { LATC1 = 0; } while(0)
#define CCP2_Toggle()   do { LATC1 = ~LATC1; } while(0)
#define CCP2_GetValue()         PORTCbits.RC1
#define CCP2_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define CCP2_SetDigitalOutput()   do { TRISC1 = 0; } while(0)

// get/set CCP1 aliases
#define CCP1_TRIS               TRISC2
#define CCP1_LAT                LATC2
#define CCP1_PORT               PORTCbits.RC2
#define CCP1_ANS                ANSC2
#define CCP1_SetHigh()    do { LATC2 = 1; } while(0)
#define CCP1_SetLow()   do { LATC2 = 0; } while(0)
#define CCP1_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define CCP1_GetValue()         PORTCbits.RC2
#define CCP1_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define CCP1_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define CCP1_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define CCP1_SetDigitalMode()   do { ANSC2 = 0; } while(0)
// get/set SCL1 aliases
#define SCL1_TRIS               TRISC3
#define SCL1_LAT                LATC3
#define SCL1_PORT               PORTCbits.RC3
#define SCL1_ANS                ANSC3
#define SCL1_SetHigh()    do { LATC3 = 1; } while(0)
#define SCL1_SetLow()   do { LATC3 = 0; } while(0)
#define SCL1_Toggle()   do { LATC3 = ~LATC3; } while(0)
#define SCL1_GetValue()         PORTCbits.RC3
#define SCL1_SetDigitalInput()    do { TRISC3 = 1; } while(0)
#define SCL1_SetDigitalOutput()   do { TRISC3 = 0; } while(0)

#define SCL1_SetAnalogMode()   do { ANSC3 = 1; } while(0)
#define SCL1_SetDigitalMode()   do { ANSC3 = 0; } while(0)
// get/set SDA1 aliases
#define SDA1_TRIS               TRISC4
#define SDA1_LAT                LATC4
#define SDA1_PORT               PORTCbits.RC4
#define SDA1_ANS                ANSC4
#define SDA1_SetHigh()    do { LATC4 = 1; } while(0)
#define SDA1_SetLow()   do { LATC4 = 0; } while(0)
#define SDA1_Toggle()   do { LATC4 = ~LATC4; } while(0)
#define SDA1_GetValue()         PORTCbits.RC4
#define SDA1_SetDigitalInput()    do { TRISC4 = 1; } while(0)
#define SDA1_SetDigitalOutput()   do { TRISC4 = 0; } while(0)

#define SDA1_SetAnalogMode()   do { ANSC4 = 1; } while(0)
#define SDA1_SetDigitalMode()   do { ANSC4 = 0; } while(0)
// get/set TX1 aliases
#define TX1_TRIS               TRISC6
#define TX1_LAT                LATC6
#define TX1_PORT               PORTCbits.RC6
#define TX1_ANS                ANSC6
#define TX1_SetHigh()    do { LATC6 = 1; } while(0)
#define TX1_SetLow()   do { LATC6 = 0; } while(0)
#define TX1_Toggle()   do { LATC6 = ~LATC6; } while(0)
#define TX1_GetValue()         PORTCbits.RC6
#define TX1_SetDigitalInput()    do { TRISC6 = 1; } while(0)
#define TX1_SetDigitalOutput()   do { TRISC6 = 0; } while(0)

#define TX1_SetAnalogMode()   do { ANSC6 = 1; } while(0)
#define TX1_SetDigitalMode()   do { ANSC6 = 0; } while(0)
// get/set RX1 aliases
#define RX1_TRIS               TRISC7
#define RX1_LAT                LATC7
#define RX1_PORT               PORTCbits.RC7
#define RX1_ANS                ANSC7
#define RX1_SetHigh()    do { LATC7 = 1; } while(0)
#define RX1_SetLow()   do { LATC7 = 0; } while(0)
#define RX1_Toggle()   do { LATC7 = ~LATC7; } while(0)
#define RX1_GetValue()         PORTCbits.RC7
#define RX1_SetDigitalInput()    do { TRISC7 = 1; } while(0)
#define RX1_SetDigitalOutput()   do { TRISC7 = 0; } while(0)

#define RX1_SetAnalogMode()   do { ANSC7 = 1; } while(0)
#define RX1_SetDigitalMode()   do { ANSC7 = 0; } while(0)

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
void PIN_MANAGER_Initialize(void);

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