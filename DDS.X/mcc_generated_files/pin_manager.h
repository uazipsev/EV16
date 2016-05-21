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
        Product Revision  :  MPLAB® Code Configurator - v2.25
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
#define TOGGLE  2

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set Volume aliases
#define Volume_TRIS               TRISA5
#define Volume_LAT                LATA5
#define Volume_PORT               PORTAbits.RA5
#define Volume_ANS                ANSA5
#define Volume_SetHigh()    do { LATA5 = 1; } while(0)
#define Volume_SetLow()   do { LATA5 = 0; } while(0)
#define Volume_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define Volume_GetValue()         PORTAbits.RA5
#define Volume_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define Volume_SetDigitalOutput()   do { TRISA5 = 0; } while(0)

#define Volume_SetAnalogMode()   do { ANSA5 = 1; } while(0)
#define Volume_SetDigitalMode()   do { ANSA5 = 0; } while(0)
// get/set INDICATOR aliases
#define INDICATOR_TRIS               TRISA3
#define INDICATOR_LAT                LATA3
#define INDICATOR_PORT               PORTAbits.RA3
#define INDICATOR_ANS                ANSA3
#define INDICATOR_SetHigh()    do { LATA3 = 1; } while(0)
#define INDICATOR_SetLow()   do { LATA3 = 0; } while(0)
#define INDICATOR_Toggle()   do { LATA3 = ~LATA3; } while(0)
#define INDICATOR_GetValue()         PORTAbits.RA3
#define INDICATOR_SetDigitalInput()    do { TRISA3 = 1; } while(0)
#define INDICATOR_SetDigitalOutput()   do { TRISA3 = 0; } while(0)

#define INDICATOR_SetAnalogMode()   do { ANSA3 = 1; } while(0)
#define INDICATOR_SetDigitalMode()   do { ANSA3 = 0; } while(0)
// get/set Button8 aliases
#define Button8_TRIS               TRISA2
#define Button8_LAT                LATA2
#define Button8_PORT               PORTAbits.RA2
#define Button8_ANS                ANSA2
#define Button8_SetHigh()    do { LATA2 = 1; } while(0)
#define Button8_SetLow()   do { LATA2 = 0; } while(0)
#define Button8_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define Button8_GetValue()         PORTAbits.RA2
#define Button8_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define Button8_SetDigitalOutput()   do { TRISA2 = 0; } while(0)

#define Button8_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define Button8_SetDigitalMode()   do { ANSA2 = 0; } while(0)
// get/set Button7 aliases
#define Button7_TRIS               TRISA1
#define Button7_LAT                LATA1
#define Button7_PORT               PORTAbits.RA1
#define Button7_ANS                ANSA1
#define Button7_SetHigh()    do { LATA1 = 1; } while(0)
#define Button7_SetLow()   do { LATA1 = 0; } while(0)
#define Button7_Toggle()   do { LATA1 = ~LATA1; } while(0)
#define Button7_GetValue()         PORTAbits.RA1
#define Button7_SetDigitalInput()    do { TRISA1 = 1; } while(0)
#define Button7_SetDigitalOutput()   do { TRISA1 = 0; } while(0)

#define Button7_SetAnalogMode()   do { ANSA1 = 1; } while(0)
#define Button7_SetDigitalMode()   do { ANSA1 = 0; } while(0)
// get/set Button6 aliases
#define Button6_TRIS               TRISA0
#define Button6_LAT                LATA0
#define Button6_PORT               PORTAbits.RA0
#define Button6_ANS                ANSA0
#define Button6_SetHigh()    do { LATA0 = 1; } while(0)
#define Button6_SetLow()   do { LATA0 = 0; } while(0)
#define Button6_Toggle()   do { LATA0 = ~LATA0; } while(0)
#define Button6_GetValue()         PORTAbits.RA0
#define Button6_SetDigitalInput()    do { TRISA0 = 1; } while(0)
#define Button6_SetDigitalOutput()   do { TRISA0 = 0; } while(0)

#define Button6_SetAnalogMode()   do { ANSA0 = 1; } while(0)
#define Button6_SetDigitalMode()   do { ANSA0 = 0; } while(0)
// get/set LED1 aliases
#define LED1_TRIS               TRISA6
#define LED1_LAT                LATA6
#define LED1_PORT               PORTAbits.RA6
#define LED1_WPU                WPUA6
#define LED1_ANS                ANSA6
#define LED1_SetHigh()    do { LATA6 = 1; } while(0)
#define LED1_SetLow()   do { LATA6 = 0; } while(0)
#define LED1_Toggle()   do { LATA6 = ~LATA6; } while(0)
#define LED1_GetValue()         PORTAbits.RA6
#define LED1_SetDigitalInput()    do { TRISA6 = 1; } while(0)
#define LED1_SetDigitalOutput()   do { TRISA6 = 0; } while(0)

#define LED1_SetPullup()    do { WPUA6 = 1; } while(0)
#define LED1_ResetPullup()   do { WPUA6 = 0; } while(0)
#define LED1_SetAnalogMode()   do { ANSA6 = 1; } while(0)
#define LED1_SetDigitalMode()   do { ANSA6 = 0; } while(0)
// get/set Button5 aliases
#define Button5_TRIS               TRISB4
#define Button5_LAT                LATB4
#define Button5_PORT               PORTBbits.RB4
#define Button5_WPU                WPUB4
#define Button5_ANS                ANSB4
#define Button5_SetHigh()    do { LATB4 = 1; } while(0)
#define Button5_SetLow()   do { LATB4 = 0; } while(0)
#define Button5_Toggle()   do { LATB4 = ~LATB4; } while(0)
#define Button5_GetValue()         PORTBbits.RB4
#define Button5_SetDigitalInput()    do { TRISB4 = 1; } while(0)
#define Button5_SetDigitalOutput()   do { TRISB4 = 0; } while(0)

#define Button5_SetPullup()    do { WPUB4 = 1; } while(0)
#define Button5_ResetPullup()   do { WPUB4 = 0; } while(0)
#define Button5_SetAnalogMode()   do { ANSB4 = 1; } while(0)
#define Button5_SetDigitalMode()   do { ANSB4 = 0; } while(0)
// get/set LED0 aliases
#define LED0_TRIS               TRISC1
#define LED0_LAT                LATC1
#define LED0_PORT               PORTCbits.RC1
#define LED0_WPU                WPUC1
#define LED0_ANS                ANSC1
#define LED0_SetHigh()    do { LATC1 = 1; } while(0)
#define LED0_SetLow()   do { LATC1 = 0; } while(0)
#define LED0_Toggle()   do { LATC1 = ~LATC1; } while(0)
#define LED0_GetValue()         PORTCbits.RC1
#define LED0_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define LED0_SetDigitalOutput()   do { TRISC1 = 0; } while(0)

#define LED0_SetPullup()    do { WPUC1 = 1; } while(0)
#define LED0_ResetPullup()   do { WPUC1 = 0; } while(0)
#define LED0_SetAnalogMode()   do { ANSC1 = 1; } while(0)
#define LED0_SetDigitalMode()   do { ANSC1 = 0; } while(0)
// get/set Button4 aliases
#define Button4_TRIS               TRISB2
#define Button4_LAT                LATB2
#define Button4_PORT               PORTBbits.RB2
#define Button4_WPU                WPUB2
#define Button4_ANS                ANSB2
#define Button4_SetHigh()    do { LATB2 = 1; } while(0)
#define Button4_SetLow()   do { LATB2 = 0; } while(0)
#define Button4_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define Button4_GetValue()         PORTBbits.RB2
#define Button4_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define Button4_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define Button4_SetPullup()    do { WPUB2 = 1; } while(0)
#define Button4_ResetPullup()   do { WPUB2 = 0; } while(0)
#define Button4_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define Button4_SetDigitalMode()   do { ANSB2 = 0; } while(0)
// get/set Button3 aliases
#define Button3_TRIS               TRISB1
#define Button3_LAT                LATB1
#define Button3_PORT               PORTBbits.RB1
#define Button3_WPU                WPUB1
#define Button3_ANS                ANSB1
#define Button3_SetHigh()    do { LATB1 = 1; } while(0)
#define Button3_SetLow()   do { LATB1 = 0; } while(0)
#define Button3_Toggle()   do { LATB1 = ~LATB1; } while(0)
#define Button3_GetValue()         PORTBbits.RB1
#define Button3_SetDigitalInput()    do { TRISB1 = 1; } while(0)
#define Button3_SetDigitalOutput()   do { TRISB1 = 0; } while(0)

#define Button3_SetPullup()    do { WPUB1 = 1; } while(0)
#define Button3_ResetPullup()   do { WPUB1 = 0; } while(0)
#define Button3_SetAnalogMode()   do { ANSB1 = 1; } while(0)
#define Button3_SetDigitalMode()   do { ANSB1 = 0; } while(0)
// get/set Button2 aliases
#define Button2_TRIS               TRISB0
#define Button2_LAT                LATB0
#define Button2_PORT               PORTBbits.RB0
#define Button2_WPU                WPUB0
#define Button2_ANS                ANSB0
#define Button2_SetHigh()    do { LATB0 = 1; } while(0)
#define Button2_SetLow()   do { LATB0 = 0; } while(0)
#define Button2_Toggle()   do { LATB0 = ~LATB0; } while(0)
#define Button2_GetValue()         PORTBbits.RB0
#define Button2_SetDigitalInput()    do { TRISB0 = 1; } while(0)
#define Button2_SetDigitalOutput()   do { TRISB0 = 0; } while(0)

#define Button2_SetPullup()    do { WPUB0 = 1; } while(0)
#define Button2_ResetPullup()   do { WPUB0 = 0; } while(0)
#define Button2_SetAnalogMode()   do { ANSB0 = 1; } while(0)
#define Button2_SetDigitalMode()   do { ANSB0 = 0; } while(0)
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
// get/set Talk aliases
#define Talk_TRIS               TRISC5
#define Talk_LAT                LATC5
#define Talk_PORT               PORTCbits.RC5
#define Talk_ANS                ANSC5
#define Talk_SetHigh()    do { LATC5 = 1; } while(0)
#define Talk_SetLow()   do { LATC5 = 0; } while(0)
#define Talk_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define Talk_GetValue()         PORTCbits.RC5
#define Talk_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define Talk_SetDigitalOutput()   do { TRISC5 = 0; } while(0)

#define Talk_SetAnalogMode()   do { ANSC5 = 1; } while(0)
#define Talk_SetDigitalMode()   do { ANSC5 = 0; } while(0)
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
// get/set Button1 aliases
#define Button1_TRIS               TRISD5
#define Button1_LAT                LATD5
#define Button1_PORT               PORTDbits.RD5
#define Button1_ANS                ANSD5
#define Button1_SetHigh()    do { LATD5 = 1; } while(0)
#define Button1_SetLow()   do { LATD5 = 0; } while(0)
#define Button1_Toggle()   do { LATD5 = ~LATD5; } while(0)
#define Button1_GetValue()         PORTDbits.RD5
#define Button1_SetDigitalInput()    do { TRISD5 = 1; } while(0)
#define Button1_SetDigitalOutput()   do { TRISD5 = 0; } while(0)

#define Button1_SetAnalogMode()   do { ANSD5 = 1; } while(0)
#define Button1_SetDigitalMode()   do { ANSD5 = 0; } while(0)
// get/set LED2 aliases
#define LED2_TRIS               TRISA7
#define LED2_LAT                LATA7
#define LED2_PORT               PORTAbits.RA7
#define LED2_ANS                ANSA7
#define LED2_SetHigh()    do { LATA7 = 1; } while(0)
#define LED2_SetLow()   do { LATA7 = 0; } while(0)
#define LED2_Toggle()   do { LATA7 = ~LATA7; } while(0)
#define LED2_GetValue()         PORTAbits.RA7
#define LED2_SetDigitalInput()    do { TRISA7 = 1; } while(0)
#define LED2_SetDigitalOutput()   do { TRISA7 = 0; } while(0)

#define LED2_SetAnalogMode()   do { ANSA7 = 1; } while(0)
#define LED2_SetDigitalMode()   do { ANSA7 = 0; } while(0)
// get/set LED3 aliases
#define LED3_TRIS               TRISE2
#define LED3_LAT                LATE2
#define LED3_PORT               PORTEbits.RE2
#define LED3_ANS                ANSE2
#define LED3_SetHigh()    do { LATE2 = 1; } while(0)
#define LED3_SetLow()   do { LATE2 = 0; } while(0)
#define LED3_Toggle()   do { LATE2 = ~LATE2; } while(0)
#define LED3_GetValue()         PORTEbits.RE2
#define LED3_SetDigitalInput()    do { TRISE2 = 1; } while(0)
#define LED3_SetDigitalOutput()   do { TRISE2 = 0; } while(0)

#define LED3_SetAnalogMode()   do { ANSE2 = 1; } while(0)
#define LED3_SetDigitalMode()   do { ANSE2 = 0; } while(0)
// get/set LED4 aliases
#define LED4_TRIS               TRISE1
#define LED4_LAT                LATE1
#define LED4_PORT               PORTEbits.RE1
#define LED4_ANS                ANSE1
#define LED4_SetHigh()    do { LATE1 = 1; } while(0)
#define LED4_SetLow()   do { LATE1 = 0; } while(0)
#define LED4_Toggle()   do { LATE1 = ~LATE1; } while(0)
#define LED4_GetValue()         PORTEbits.RE1
#define LED4_SetDigitalInput()    do { TRISE1 = 1; } while(0)
#define LED4_SetDigitalOutput()   do { TRISE1 = 0; } while(0)

#define LED4_SetAnalogMode()   do { ANSE1 = 1; } while(0)
#define LED4_SetDigitalMode()   do { ANSE1 = 0; } while(0)
// get/set LED5 aliases
#define LED5_TRIS               TRISE0
#define LED5_LAT                LATE0
#define LED5_PORT               PORTEbits.RE0
#define LED5_ANS                ANSE0
#define LED5_SetHigh()    do { LATE0 = 1; } while(0)
#define LED5_SetLow()   do { LATE0 = 0; } while(0)
#define LED5_Toggle()   do { LATE0 = ~LATE0; } while(0)
#define LED5_GetValue()         PORTEbits.RE0
#define LED5_SetDigitalInput()    do { TRISE0 = 1; } while(0)
#define LED5_SetDigitalOutput()   do { TRISE0 = 0; } while(0)

#define LED5_SetAnalogMode()   do { ANSE0 = 1; } while(0)
#define LED5_SetDigitalMode()   do { ANSE0 = 0; } while(0)

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