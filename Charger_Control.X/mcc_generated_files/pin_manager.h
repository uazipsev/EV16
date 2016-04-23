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

// get/set LED aliases
#define LED_TRIS               TRISA3
#define LED_LAT                LATA3
#define LED_PORT               RA3
#define LED_ANS                ANSA3
#define LED_SetHigh()    do { LATA3 = 1; } while(0)
#define LED_SetLow()   do { LATA3 = 0; } while(0)
#define LED_Toggle()   do { LATA3 = ~LATA3; } while(0)
#define LED_GetValue()         RA3
#define LED_SetDigitalInput()    do { TRISA3 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISA3 = 0; } while(0)

#define LED_SetAnalogMode()   do { ANSA3 = 1; } while(0)
#define LED_SetDigitalMode()   do { ANSA3 = 0; } while(0)


// get/set GREEN aliases
#define GREEN_TRIS               TRISA6
#define GREEN_LAT                LATA6
#define GREEN_PORT               RA6
#define GREEN_SetHigh()    do { LATA6 = 1; } while(0)
#define GREEN_SetLow()   do { LATA6 = 0; } while(0)
#define GREEN_Toggle()   do { LATA6 = ~LATA6; } while(0)
#define GREEN_GetValue()         RA6
#define GREEN_SetDigitalInput()    do { TRISA6 = 1; } while(0)
#define GREEN_SetDigitalOutput()   do { TRISA6 = 0; } while(0)



// get/set HORN aliases
#define HORN_TRIS               TRISA7
#define HORN_LAT                LATA7
#define HORN_PORT               RA7
#define HORN_SetHigh()    do { LATA7 = 1; } while(0)
#define HORN_SetLow()   do { LATA7 = 0; } while(0)
#define HORN_Toggle()   do { LATA7 = ~LATA7; } while(0)
#define HORN_GetValue()         RA7
#define HORN_SetDigitalInput()    do { TRISA7 = 1; } while(0)
#define HORN_SetDigitalOutput()   do { TRISA7 = 0; } while(0)



// get/set MUX_S0 aliases
#define MUX_S0_TRIS               TRISB0
#define MUX_S0_LAT                LATB0
#define MUX_S0_PORT               RB0
#define MUX_S0_WPU                WPUB0
#define MUX_S0_ANS                ANSB0
#define MUX_S0_SetHigh()    do { LATB0 = 1; } while(0)
#define MUX_S0_SetLow()   do { LATB0 = 0; } while(0)
#define MUX_S0_Toggle()   do { LATB0 = ~LATB0; } while(0)
#define MUX_S0_GetValue()         RB0
#define MUX_S0_SetDigitalInput()    do { TRISB0 = 1; } while(0)
#define MUX_S0_SetDigitalOutput()   do { TRISB0 = 0; } while(0)

#define MUX_S0_SetPullup()    do { WPUB0 = 1; } while(0)
#define MUX_S0_ResetPullup()   do { WPUB0 = 0; } while(0)
#define MUX_S0_SetAnalogMode()   do { ANSB0 = 1; } while(0)
#define MUX_S0_SetDigitalMode()   do { ANSB0 = 0; } while(0)


// get/set MUX_S1 aliases
#define MUX_S1_TRIS               TRISB1
#define MUX_S1_LAT                LATB1
#define MUX_S1_PORT               RB1
#define MUX_S1_WPU                WPUB1
#define MUX_S1_ANS                ANSB1
#define MUX_S1_SetHigh()    do { LATB1 = 1; } while(0)
#define MUX_S1_SetLow()   do { LATB1 = 0; } while(0)
#define MUX_S1_Toggle()   do { LATB1 = ~LATB1; } while(0)
#define MUX_S1_GetValue()         RB1
#define MUX_S1_SetDigitalInput()    do { TRISB1 = 1; } while(0)
#define MUX_S1_SetDigitalOutput()   do { TRISB1 = 0; } while(0)

#define MUX_S1_SetPullup()    do { WPUB1 = 1; } while(0)
#define MUX_S1_ResetPullup()   do { WPUB1 = 0; } while(0)
#define MUX_S1_SetAnalogMode()   do { ANSB1 = 1; } while(0)
#define MUX_S1_SetDigitalMode()   do { ANSB1 = 0; } while(0)


// get/set PRE_BOTTOM_AIR aliases
#define PRE_BOTTOM_AIR_TRIS               TRISB3
#define PRE_BOTTOM_AIR_LAT                LATB3
#define PRE_BOTTOM_AIR_PORT               RB3
#define PRE_BOTTOM_AIR_WPU                WPUB3
#define PRE_BOTTOM_AIR_ANS                ANSB3
#define PRE_BOTTOM_AIR_SetHigh()    do { LATB3 = 1; } while(0)
#define PRE_BOTTOM_AIR_SetLow()   do { LATB3 = 0; } while(0)
#define PRE_BOTTOM_AIR_Toggle()   do { LATB3 = ~LATB3; } while(0)
#define PRE_BOTTOM_AIR_GetValue()         RB3
#define PRE_BOTTOM_AIR_SetDigitalInput()    do { TRISB3 = 1; } while(0)
#define PRE_BOTTOM_AIR_SetDigitalOutput()   do { TRISB3 = 0; } while(0)

#define PRE_BOTTOM_AIR_SetPullup()    do { WPUB3 = 1; } while(0)
#define PRE_BOTTOM_AIR_ResetPullup()   do { WPUB3 = 0; } while(0)
#define PRE_BOTTOM_AIR_SetAnalogMode()   do { ANSB3 = 1; } while(0)
#define PRE_BOTTOM_AIR_SetDigitalMode()   do { ANSB3 = 0; } while(0)


// get/set TOP_AIR aliases
#define TOP_AIR_TRIS               TRISB4
#define TOP_AIR_LAT                LATB4
#define TOP_AIR_PORT               RB4
#define TOP_AIR_WPU                WPUB4
#define TOP_AIR_ANS                ANSB4
#define TOP_AIR_SetHigh()    do { LATB4 = 1; } while(0)
#define TOP_AIR_SetLow()   do { LATB4 = 0; } while(0)
#define TOP_AIR_Toggle()   do { LATB4 = ~LATB4; } while(0)
#define TOP_AIR_GetValue()         RB4
#define TOP_AIR_SetDigitalInput()    do { TRISB4 = 1; } while(0)
#define TOP_AIR_SetDigitalOutput()   do { TRISB4 = 0; } while(0)

#define TOP_AIR_SetPullup()    do { WPUB4 = 1; } while(0)
#define TOP_AIR_ResetPullup()   do { WPUB4 = 0; } while(0)
#define TOP_AIR_SetAnalogMode()   do { ANSB4 = 1; } while(0)
#define TOP_AIR_SetDigitalMode()   do { ANSB4 = 0; } while(0)


// get/set CHARGER_POWER aliases
#define CHARGER_POWER_TRIS               TRISB5
#define CHARGER_POWER_LAT                LATB5
#define CHARGER_POWER_PORT               RB5
#define CHARGER_POWER_WPU                WPUB5
#define CHARGER_POWER_ANS                ANSB5
#define CHARGER_POWER_SetHigh()    do { LATB5 = 1; } while(0)
#define CHARGER_POWER_SetLow()   do { LATB5 = 0; } while(0)
#define CHARGER_POWER_Toggle()   do { LATB5 = ~LATB5; } while(0)
#define CHARGER_POWER_GetValue()         RB5
#define CHARGER_POWER_SetDigitalInput()    do { TRISB5 = 1; } while(0)
#define CHARGER_POWER_SetDigitalOutput()   do { TRISB5 = 0; } while(0)

#define CHARGER_POWER_SetPullup()    do { WPUB5 = 1; } while(0)
#define CHARGER_POWER_ResetPullup()   do { WPUB5 = 0; } while(0)
#define CHARGER_POWER_SetAnalogMode()   do { ANSB5 = 1; } while(0)
#define CHARGER_POWER_SetDigitalMode()   do { ANSB5 = 0; } while(0)


// get/set BLUE aliases
#define BLUE_TRIS               TRISC0
#define BLUE_LAT                LATC0
#define BLUE_PORT               RC0
#define BLUE_SetHigh()    do { LATC0 = 1; } while(0)
#define BLUE_SetLow()   do { LATC0 = 0; } while(0)
#define BLUE_Toggle()   do { LATC0 = ~LATC0; } while(0)
#define BLUE_GetValue()         RC0
#define BLUE_SetDigitalInput()    do { TRISC0 = 1; } while(0)
#define BLUE_SetDigitalOutput()   do { TRISC0 = 0; } while(0)



// get/set YELLOW aliases
#define YELLOW_TRIS               TRISC1
#define YELLOW_LAT                LATC1
#define YELLOW_PORT               RC1
#define YELLOW_SetHigh()    do { LATC1 = 1; } while(0)
#define YELLOW_SetLow()   do { LATC1 = 0; } while(0)
#define YELLOW_Toggle()   do { LATC1 = ~LATC1; } while(0)
#define YELLOW_GetValue()         RC1
#define YELLOW_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define YELLOW_SetDigitalOutput()   do { TRISC1 = 0; } while(0)



// get/set POWER_EN aliases
#define POWER_EN_TRIS               TRISC4
#define POWER_EN_LAT                LATC4
#define POWER_EN_PORT               RC4
#define POWER_EN_ANS                ANSC4
#define POWER_EN_SetHigh()    do { LATC4 = 1; } while(0)
#define POWER_EN_SetLow()   do { LATC4 = 0; } while(0)
#define POWER_EN_Toggle()   do { LATC4 = ~LATC4; } while(0)
#define POWER_EN_GetValue()         RC4
#define POWER_EN_SetDigitalInput()    do { TRISC4 = 1; } while(0)
#define POWER_EN_SetDigitalOutput()   do { TRISC4 = 0; } while(0)

#define POWER_EN_SetAnalogMode()   do { ANSC4 = 1; } while(0)
#define POWER_EN_SetDigitalMode()   do { ANSC4 = 0; } while(0)


// get/set POWER_EN aliases
#define POWER_EN_TRIS               TRISC4
#define POWER_EN_LAT                LATC4
#define POWER_EN_PORT               RC4
#define POWER_EN_ANS                ANSC4
#define POWER_EN_SetHigh()    do { LATC4 = 1; } while(0)
#define POWER_EN_SetLow()   do { LATC4 = 0; } while(0)
#define POWER_EN_Toggle()   do { LATC4 = ~LATC4; } while(0)
#define POWER_EN_GetValue()         RC4
#define POWER_EN_SetDigitalInput()    do { TRISC4 = 1; } while(0)
#define POWER_EN_SetDigitalOutput()   do { TRISC4 = 0; } while(0)

#define POWER_EN_SetAnalogMode()   do { ANSC4 = 1; } while(0)
#define POWER_EN_SetDigitalMode()   do { ANSC4 = 0; } while(0)


// get/set POWER_EN aliases
#define POWER_EN_TRIS               TRISC4
#define POWER_EN_LAT                LATC4
#define POWER_EN_PORT               RC4
#define POWER_EN_ANS                ANSC4
#define POWER_EN_SetHigh()    do { LATC4 = 1; } while(0)
#define POWER_EN_SetLow()   do { LATC4 = 0; } while(0)
#define POWER_EN_Toggle()   do { LATC4 = ~LATC4; } while(0)
#define POWER_EN_GetValue()         RC4
#define POWER_EN_SetDigitalInput()    do { TRISC4 = 1; } while(0)
#define POWER_EN_SetDigitalOutput()   do { TRISC4 = 0; } while(0)

#define POWER_EN_SetAnalogMode()   do { ANSC4 = 1; } while(0)
#define POWER_EN_SetDigitalMode()   do { ANSC4 = 0; } while(0)


// get/set LCD_CS aliases
#define LCD_CS_TRIS               TRISD0
#define LCD_CS_LAT                LATD0
#define LCD_CS_PORT               RD0
#define LCD_CS_ANS                ANSD0
#define LCD_CS_SetHigh()    do { LATD0 = 1; } while(0)
#define LCD_CS_SetLow()   do { LATD0 = 0; } while(0)
#define LCD_CS_Toggle()   do { LATD0 = ~LATD0; } while(0)
#define LCD_CS_GetValue()         RD0
#define LCD_CS_SetDigitalInput()    do { TRISD0 = 1; } while(0)
#define LCD_CS_SetDigitalOutput()   do { TRISD0 = 0; } while(0)

#define LCD_CS_SetAnalogMode()   do { ANSD0 = 1; } while(0)
#define LCD_CS_SetDigitalMode()   do { ANSD0 = 0; } while(0)

#define LCD_RES_SetDigitalOutput()   do { TRISD2 = 0; } while(0)
#define LCD_RES_SetHigh()    do { LATD2 = 1; } while(0)
#define LCD_RES_SetLow()   do { LATD2 = 0; } while(0)

// get/set LCD_DC aliases
#define LCD_DC_TRIS               TRISD3
#define LCD_DC_LAT                LATD3
#define LCD_DC_PORT               RD3
#define LCD_DC_ANS                ANSD3
#define LCD_DC_SetHigh()    do { LATD3 = 1; } while(0)
#define LCD_DC_SetLow()   do { LATD3 = 0; } while(0)
#define LCD_DC_Toggle()   do { LATD3 = ~LATD3; } while(0)
#define LCD_DC_GetValue()         RD3
#define LCD_DC_SetDigitalInput()    do { TRISD3 = 1; } while(0)
#define LCD_DC_SetDigitalOutput()   do { TRISD3 = 0; } while(0)

#define LCD_DC_SetAnalogMode()   do { ANSD3 = 1; } while(0)
#define LCD_DC_SetDigitalMode()   do { ANSD3 = 0; } while(0)



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