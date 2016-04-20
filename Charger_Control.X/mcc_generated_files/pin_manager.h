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

// get/set LED aliases
#define LED_TRIS               TRISA3
#define LED_LAT                LATA3
#define LED_PORT               PORTAbits.RA3
#define LED_ANS                ANSA3
#define LED_SetHigh()    do { LATA3 = 1; } while(0)
#define LED_SetLow()   do { LATA3 = 0; } while(0)
#define LED_Toggle()   do { LATA3 = ~LATA3; } while(0)
#define LED_GetValue()         PORTAbits.RA3
#define LED_SetDigitalInput()    do { TRISA3 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISA3 = 0; } while(0)

#define LED_SetAnalogMode()   do { ANSA3 = 1; } while(0)
#define LED_SetDigitalMode()   do { ANSA3 = 0; } while(0)
// get/set MUX_0 aliases
#define MUX_0_TRIS               TRISA4
#define MUX_0_LAT                LATA4
#define MUX_0_PORT               PORTAbits.RA4
#define MUX_0_SetHigh()    do { LATA4 = 1; } while(0)
#define MUX_0_SetLow()   do { LATA4 = 0; } while(0)
#define MUX_0_Toggle()   do { LATA4 = ~LATA4; } while(0)
#define MUX_0_GetValue()         PORTAbits.RA4
#define MUX_0_SetDigitalInput()    do { TRISA4 = 1; } while(0)
#define MUX_0_SetDigitalOutput()   do { TRISA4 = 0; } while(0)

// get/set MUX_1 aliases
#define MUX_1_TRIS               TRISA5
#define MUX_1_LAT                LATA5
#define MUX_1_PORT               PORTAbits.RA5
#define MUX_1_ANS                ANSA5
#define MUX_1_SetHigh()    do { LATA5 = 1; } while(0)
#define MUX_1_SetLow()   do { LATA5 = 0; } while(0)
#define MUX_1_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define MUX_1_GetValue()         PORTAbits.RA5
#define MUX_1_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define MUX_1_SetDigitalOutput()   do { TRISA5 = 0; } while(0)

#define MUX_1_SetAnalogMode()   do { ANSA5 = 1; } while(0)
#define MUX_1_SetDigitalMode()   do { ANSA5 = 0; } while(0)
// get/set Green aliases
#define Green_TRIS               TRISA6
#define Green_LAT                LATA6
#define Green_PORT               PORTAbits.RA6
#define Green_SetHigh()    do { LATA6 = 1; } while(0)
#define Green_SetLow()   do { LATA6 = 0; } while(0)
#define Green_Toggle()   do { LATA6 = ~LATA6; } while(0)
#define Green_GetValue()         PORTAbits.RA6
#define Green_SetDigitalInput()    do { TRISA6 = 1; } while(0)
#define Green_SetDigitalOutput()   do { TRISA6 = 0; } while(0)

// get/set Horn aliases
#define Horn_TRIS               TRISA7
#define Horn_LAT                LATA7
#define Horn_PORT               PORTAbits.RA7
#define Horn_SetHigh()    do { LATA7 = 1; } while(0)
#define Horn_SetLow()   do { LATA7 = 0; } while(0)
#define Horn_Toggle()   do { LATA7 = ~LATA7; } while(0)
#define Horn_GetValue()         PORTAbits.RA7
#define Horn_SetDigitalInput()    do { TRISA7 = 1; } while(0)
#define Horn_SetDigitalOutput()   do { TRISA7 = 0; } while(0)

// get/set Main aliases
#define Main_TRIS               TRISB3
#define Main_LAT                LATB3
#define Main_PORT               PORTBbits.RB3
#define Main_WPU                WPUB3
#define Main_ANS                ANSB3
#define Main_SetHigh()    do { LATB3 = 1; } while(0)
#define Main_SetLow()   do { LATB3 = 0; } while(0)
#define Main_Toggle()   do { LATB3 = ~LATB3; } while(0)
#define Main_GetValue()         PORTBbits.RB3
#define Main_SetDigitalInput()    do { TRISB3 = 1; } while(0)
#define Main_SetDigitalOutput()   do { TRISB3 = 0; } while(0)

#define Main_SetPullup()    do { WPUB3 = 1; } while(0)
#define Main_ResetPullup()   do { WPUB3 = 0; } while(0)
#define Main_SetAnalogMode()   do { ANSB3 = 1; } while(0)
#define Main_SetDigitalMode()   do { ANSB3 = 0; } while(0)
// get/set Pre_Charge aliases
#define Pre_Charge_TRIS               TRISB4
#define Pre_Charge_LAT                LATB4
#define Pre_Charge_PORT               PORTBbits.RB4
#define Pre_Charge_WPU                WPUB4
#define Pre_Charge_ANS                ANSB4
#define Pre_Charge_SetHigh()    do { LATB4 = 1; } while(0)
#define Pre_Charge_SetLow()   do { LATB4 = 0; } while(0)
#define Pre_Charge_Toggle()   do { LATB4 = ~LATB4; } while(0)
#define Pre_Charge_GetValue()         PORTBbits.RB4
#define Pre_Charge_SetDigitalInput()    do { TRISB4 = 1; } while(0)
#define Pre_Charge_SetDigitalOutput()   do { TRISB4 = 0; } while(0)

#define Pre_Charge_SetPullup()    do { WPUB4 = 1; } while(0)
#define Pre_Charge_ResetPullup()   do { WPUB4 = 0; } while(0)
#define Pre_Charge_SetAnalogMode()   do { ANSB4 = 1; } while(0)
#define Pre_Charge_SetDigitalMode()   do { ANSB4 = 0; } while(0)
// get/set Blue aliases
#define Blue_TRIS               TRISC0
#define Blue_LAT                LATC0
#define Blue_PORT               PORTCbits.RC0
#define Blue_SetHigh()    do { LATC0 = 1; } while(0)
#define Blue_SetLow()   do { LATC0 = 0; } while(0)
#define Blue_Toggle()   do { LATC0 = ~LATC0; } while(0)
#define Blue_GetValue()         PORTCbits.RC0
#define Blue_SetDigitalInput()    do { TRISC0 = 1; } while(0)
#define Blue_SetDigitalOutput()   do { TRISC0 = 0; } while(0)

// get/set Yellow aliases
#define Yellow_TRIS               TRISC1
#define Yellow_LAT                LATC1
#define Yellow_PORT               PORTCbits.RC1
#define Yellow_SetHigh()    do { LATC1 = 1; } while(0)
#define Yellow_SetLow()   do { LATC1 = 0; } while(0)
#define Yellow_Toggle()   do { LATC1 = ~LATC1; } while(0)
#define Yellow_GetValue()         PORTCbits.RC1
#define Yellow_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define Yellow_SetDigitalOutput()   do { TRISC1 = 0; } while(0)

// get/set Start aliases
#define Start_TRIS               TRISC3
#define Start_LAT                LATC3
#define Start_PORT               PORTCbits.RC3
#define Start_ANS                ANSC3
#define Start_SetHigh()    do { LATC3 = 1; } while(0)
#define Start_SetLow()   do { LATC3 = 0; } while(0)
#define Start_Toggle()   do { LATC3 = ~LATC3; } while(0)
#define Start_GetValue()         PORTCbits.RC3
#define Start_SetDigitalInput()    do { TRISC3 = 1; } while(0)
#define Start_SetDigitalOutput()   do { TRISC3 = 0; } while(0)

#define Start_SetAnalogMode()   do { ANSC3 = 1; } while(0)
#define Start_SetDigitalMode()   do { ANSC3 = 0; } while(0)
// get/set Power aliases
#define Power_TRIS               TRISC5
#define Power_LAT                LATC5
#define Power_PORT               PORTCbits.RC5
#define Power_ANS                ANSC5
#define Power_SetHigh()    do { LATC5 = 1; } while(0)
#define Power_SetLow()   do { LATC5 = 0; } while(0)
#define Power_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define Power_GetValue()         PORTCbits.RC5
#define Power_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define Power_SetDigitalOutput()   do { TRISC5 = 0; } while(0)

#define Power_SetAnalogMode()   do { ANSC5 = 1; } while(0)
#define Power_SetDigitalMode()   do { ANSC5 = 0; } while(0)
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
// get/set TX2 aliases
#define TX2_TRIS               TRISD6
#define TX2_LAT                LATD6
#define TX2_PORT               PORTDbits.RD6
#define TX2_ANS                ANSD6
#define TX2_SetHigh()    do { LATD6 = 1; } while(0)
#define TX2_SetLow()   do { LATD6 = 0; } while(0)
#define TX2_Toggle()   do { LATD6 = ~LATD6; } while(0)
#define TX2_GetValue()         PORTDbits.RD6
#define TX2_SetDigitalInput()    do { TRISD6 = 1; } while(0)
#define TX2_SetDigitalOutput()   do { TRISD6 = 0; } while(0)

#define TX2_SetAnalogMode()   do { ANSD6 = 1; } while(0)
#define TX2_SetDigitalMode()   do { ANSD6 = 0; } while(0)
// get/set RX2 aliases
#define RX2_TRIS               TRISD7
#define RX2_LAT                LATD7
#define RX2_PORT               PORTDbits.RD7
#define RX2_ANS                ANSD7
#define RX2_SetHigh()    do { LATD7 = 1; } while(0)
#define RX2_SetLow()   do { LATD7 = 0; } while(0)
#define RX2_Toggle()   do { LATD7 = ~LATD7; } while(0)
#define RX2_GetValue()         PORTDbits.RD7
#define RX2_SetDigitalInput()    do { TRISD7 = 1; } while(0)
#define RX2_SetDigitalOutput()   do { TRISD7 = 0; } while(0)

#define RX2_SetAnalogMode()   do { ANSD7 = 1; } while(0)
#define RX2_SetDigitalMode()   do { ANSD7 = 0; } while(0)

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