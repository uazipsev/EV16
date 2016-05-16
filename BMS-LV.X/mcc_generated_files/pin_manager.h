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

// get/set AN_CELL7 aliases
#define AN_CELL7_TRIS               TRISA0
#define AN_CELL7_LAT                LATA0
#define AN_CELL7_PORT               PORTAbits.RA0
#define AN_CELL7_ANS                ANSA0
#define AN_CELL7_SetHigh()    do { LATA0 = 1; } while(0)
#define AN_CELL7_SetLow()   do { LATA0 = 0; } while(0)
#define AN_CELL7_Toggle()   do { LATA0 = ~LATA0; } while(0)
#define AN_CELL7_GetValue()         PORTAbits.RA0
#define AN_CELL7_SetDigitalInput()    do { TRISA0 = 1; } while(0)
#define AN_CELL7_SetDigitalOutput()   do { TRISA0 = 0; } while(0)

#define AN_CELL7_SetAnalogMode()   do { ANSA0 = 1; } while(0)
#define AN_CELL7_SetDigitalMode()   do { ANSA0 = 0; } while(0)
// get/set AN_CELL6 aliases
#define AN_CELL6_TRIS               TRISA1
#define AN_CELL6_LAT                LATA1
#define AN_CELL6_PORT               PORTAbits.RA1
#define AN_CELL6_ANS                ANSA1
#define AN_CELL6_SetHigh()    do { LATA1 = 1; } while(0)
#define AN_CELL6_SetLow()   do { LATA1 = 0; } while(0)
#define AN_CELL6_Toggle()   do { LATA1 = ~LATA1; } while(0)
#define AN_CELL6_GetValue()         PORTAbits.RA1
#define AN_CELL6_SetDigitalInput()    do { TRISA1 = 1; } while(0)
#define AN_CELL6_SetDigitalOutput()   do { TRISA1 = 0; } while(0)

#define AN_CELL6_SetAnalogMode()   do { ANSA1 = 1; } while(0)
#define AN_CELL6_SetDigitalMode()   do { ANSA1 = 0; } while(0)
// get/set AN_CELL5 aliases
#define AN_CELL5_TRIS               TRISA3
#define AN_CELL5_LAT                LATA3
#define AN_CELL5_PORT               PORTAbits.RA3
#define AN_CELL5_ANS                ANSA3
#define AN_CELL5_SetHigh()    do { LATA3 = 1; } while(0)
#define AN_CELL5_SetLow()   do { LATA3 = 0; } while(0)
#define AN_CELL5_Toggle()   do { LATA3 = ~LATA3; } while(0)
#define AN_CELL5_GetValue()         PORTAbits.RA3
#define AN_CELL5_SetDigitalInput()    do { TRISA3 = 1; } while(0)
#define AN_CELL5_SetDigitalOutput()   do { TRISA3 = 0; } while(0)

#define AN_CELL5_SetAnalogMode()   do { ANSA3 = 1; } while(0)
#define AN_CELL5_SetDigitalMode()   do { ANSA3 = 0; } while(0)
// get/set Indicator aliases
#define Indicator_TRIS               TRISA4
#define Indicator_LAT                LATA4
#define Indicator_PORT               PORTAbits.RA4
#define Indicator_SetHigh()    do { LATA4 = 1; } while(0)
#define Indicator_SetLow()   do { LATA4 = 0; } while(0)
#define Indicator_Toggle()   do { LATA4 = ~LATA4; } while(0)
#define Indicator_GetValue()         PORTAbits.RA4
#define Indicator_SetDigitalInput()    do { TRISA4 = 1; } while(0)
#define Indicator_SetDigitalOutput()   do { TRISA4 = 0; } while(0)

// get/set AN_CELL4 aliases
#define AN_CELL4_TRIS               TRISA5
#define AN_CELL4_LAT                LATA5
#define AN_CELL4_PORT               PORTAbits.RA5
#define AN_CELL4_ANS                ANSA5
#define AN_CELL4_SetHigh()    do { LATA5 = 1; } while(0)
#define AN_CELL4_SetLow()   do { LATA5 = 0; } while(0)
#define AN_CELL4_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define AN_CELL4_GetValue()         PORTAbits.RA5
#define AN_CELL4_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define AN_CELL4_SetDigitalOutput()   do { TRISA5 = 0; } while(0)

#define AN_CELL4_SetAnalogMode()   do { ANSA5 = 1; } while(0)
#define AN_CELL4_SetDigitalMode()   do { ANSA5 = 0; } while(0)
// get/set MUX_B aliases
#define MUX_B_TRIS               TRISA6
#define MUX_B_LAT                LATA6
#define MUX_B_PORT               PORTAbits.RA6
#define MUX_B_SetHigh()    do { LATA6 = 1; } while(0)
#define MUX_B_SetLow()   do { LATA6 = 0; } while(0)
#define MUX_B_Toggle()   do { LATA6 = ~LATA6; } while(0)
#define MUX_B_GetValue()         PORTAbits.RA6
#define MUX_B_SetDigitalInput()    do { TRISA6 = 1; } while(0)
#define MUX_B_SetDigitalOutput()   do { TRISA6 = 0; } while(0)

// get/set MUX_A aliases
#define MUX_A_TRIS               TRISA7
#define MUX_A_LAT                LATA7
#define MUX_A_PORT               PORTAbits.RA7
#define MUX_A_SetHigh()    do { LATA7 = 1; } while(0)
#define MUX_A_SetLow()   do { LATA7 = 0; } while(0)
#define MUX_A_Toggle()   do { LATA7 = ~LATA7; } while(0)
#define MUX_A_GetValue()         PORTAbits.RA7
#define MUX_A_SetDigitalInput()    do { TRISA7 = 1; } while(0)
#define MUX_A_SetDigitalOutput()   do { TRISA7 = 0; } while(0)

// get/set BP_ENBL5 aliases
#define BP_ENBL5_TRIS               TRISB0
#define BP_ENBL5_LAT                LATB0
#define BP_ENBL5_PORT               PORTBbits.RB0
#define BP_ENBL5_WPU                WPUB0
#define BP_ENBL5_ANS                ANSB0
#define BP_ENBL5_SetHigh()    do { LATB0 = 1; } while(0)
#define BP_ENBL5_SetLow()   do { LATB0 = 0; } while(0)
#define BP_ENBL5_Toggle()   do { LATB0 = ~LATB0; } while(0)
#define BP_ENBL5_GetValue()         PORTBbits.RB0
#define BP_ENBL5_SetDigitalInput()    do { TRISB0 = 1; } while(0)
#define BP_ENBL5_SetDigitalOutput()   do { TRISB0 = 0; } while(0)

#define BP_ENBL5_SetPullup()    do { WPUB0 = 1; } while(0)
#define BP_ENBL5_ResetPullup()   do { WPUB0 = 0; } while(0)
#define BP_ENBL5_SetAnalogMode()   do { ANSB0 = 1; } while(0)
#define BP_ENBL5_SetDigitalMode()   do { ANSB0 = 0; } while(0)
// get/set BP_ENBL6 aliases
#define BP_ENBL6_TRIS               TRISB1
#define BP_ENBL6_LAT                LATB1
#define BP_ENBL6_PORT               PORTBbits.RB1
#define BP_ENBL6_WPU                WPUB1
#define BP_ENBL6_ANS                ANSB1
#define BP_ENBL6_SetHigh()    do { LATB1 = 1; } while(0)
#define BP_ENBL6_SetLow()   do { LATB1 = 0; } while(0)
#define BP_ENBL6_Toggle()   do { LATB1 = ~LATB1; } while(0)
#define BP_ENBL6_GetValue()         PORTBbits.RB1
#define BP_ENBL6_SetDigitalInput()    do { TRISB1 = 1; } while(0)
#define BP_ENBL6_SetDigitalOutput()   do { TRISB1 = 0; } while(0)

#define BP_ENBL6_SetPullup()    do { WPUB1 = 1; } while(0)
#define BP_ENBL6_ResetPullup()   do { WPUB1 = 0; } while(0)
#define BP_ENBL6_SetAnalogMode()   do { ANSB1 = 1; } while(0)
#define BP_ENBL6_SetDigitalMode()   do { ANSB1 = 0; } while(0)
// get/set BP_ENBL7 aliases
#define BP_ENBL7_TRIS               TRISB2
#define BP_ENBL7_LAT                LATB2
#define BP_ENBL7_PORT               PORTBbits.RB2
#define BP_ENBL7_WPU                WPUB2
#define BP_ENBL7_ANS                ANSB2
#define BP_ENBL7_SetHigh()    do { LATB2 = 1; } while(0)
#define BP_ENBL7_SetLow()   do { LATB2 = 0; } while(0)
#define BP_ENBL7_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define BP_ENBL7_GetValue()         PORTBbits.RB2
#define BP_ENBL7_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define BP_ENBL7_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define BP_ENBL7_SetPullup()    do { WPUB2 = 1; } while(0)
#define BP_ENBL7_ResetPullup()   do { WPUB2 = 0; } while(0)
#define BP_ENBL7_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define BP_ENBL7_SetDigitalMode()   do { ANSB2 = 0; } while(0)
// get/set Vexternal aliases
#define Vexternal_TRIS               TRISB3
#define Vexternal_LAT                LATB3
#define Vexternal_PORT               PORTBbits.RB3
#define Vexternal_WPU                WPUB3
#define Vexternal_ANS                ANSB3
#define Vexternal_SetHigh()    do { LATB3 = 1; } while(0)
#define Vexternal_SetLow()   do { LATB3 = 0; } while(0)
#define Vexternal_Toggle()   do { LATB3 = ~LATB3; } while(0)
#define Vexternal_GetValue()         PORTBbits.RB3
#define Vexternal_SetDigitalInput()    do { TRISB3 = 1; } while(0)
#define Vexternal_SetDigitalOutput()   do { TRISB3 = 0; } while(0)

#define Vexternal_SetPullup()    do { WPUB3 = 1; } while(0)
#define Vexternal_ResetPullup()   do { WPUB3 = 0; } while(0)
#define Vexternal_SetAnalogMode()   do { ANSB3 = 1; } while(0)
#define Vexternal_SetDigitalMode()   do { ANSB3 = 0; } while(0)
// get/set Asen aliases
#define Asen_TRIS               TRISB4
#define Asen_LAT                LATB4
#define Asen_PORT               PORTBbits.RB4
#define Asen_WPU                WPUB4
#define Asen_ANS                ANSB4
#define Asen_SetHigh()    do { LATB4 = 1; } while(0)
#define Asen_SetLow()   do { LATB4 = 0; } while(0)
#define Asen_Toggle()   do { LATB4 = ~LATB4; } while(0)
#define Asen_GetValue()         PORTBbits.RB4
#define Asen_SetDigitalInput()    do { TRISB4 = 1; } while(0)
#define Asen_SetDigitalOutput()   do { TRISB4 = 0; } while(0)

#define Asen_SetPullup()    do { WPUB4 = 1; } while(0)
#define Asen_ResetPullup()   do { WPUB4 = 0; } while(0)
#define Asen_SetAnalogMode()   do { ANSB4 = 1; } while(0)
#define Asen_SetDigitalMode()   do { ANSB4 = 0; } while(0)
// get/set MUX_C aliases
#define MUX_C_TRIS               TRISC0
#define MUX_C_LAT                LATC0
#define MUX_C_PORT               PORTCbits.RC0
#define MUX_C_SetHigh()    do { LATC0 = 1; } while(0)
#define MUX_C_SetLow()   do { LATC0 = 0; } while(0)
#define MUX_C_Toggle()   do { LATC0 = ~LATC0; } while(0)
#define MUX_C_GetValue()         PORTCbits.RC0
#define MUX_C_SetDigitalInput()    do { TRISC0 = 1; } while(0)
#define MUX_C_SetDigitalOutput()   do { TRISC0 = 0; } while(0)

// get/set Temp1 aliases
#define Temp1_TRIS               TRISC2
#define Temp1_LAT                LATC2
#define Temp1_PORT               PORTCbits.RC2
#define Temp1_ANS                ANSC2
#define Temp1_SetHigh()    do { LATC2 = 1; } while(0)
#define Temp1_SetLow()   do { LATC2 = 0; } while(0)
#define Temp1_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define Temp1_GetValue()         PORTCbits.RC2
#define Temp1_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define Temp1_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define Temp1_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define Temp1_SetDigitalMode()   do { ANSC2 = 0; } while(0)
// get/set Temp_INH aliases
#define Temp_INH_TRIS               TRISC3
#define Temp_INH_LAT                LATC3
#define Temp_INH_PORT               PORTCbits.RC3
#define Temp_INH_ANS                ANSC3
#define Temp_INH_SetHigh()    do { LATC3 = 1; } while(0)
#define Temp_INH_SetLow()   do { LATC3 = 0; } while(0)
#define Temp_INH_Toggle()   do { LATC3 = ~LATC3; } while(0)
#define Temp_INH_GetValue()         PORTCbits.RC3
#define Temp_INH_SetDigitalInput()    do { TRISC3 = 1; } while(0)
#define Temp_INH_SetDigitalOutput()   do { TRISC3 = 0; } while(0)

#define Temp_INH_SetAnalogMode()   do { ANSC3 = 1; } while(0)
#define Temp_INH_SetDigitalMode()   do { ANSC3 = 0; } while(0)
// get/set MODE_RE aliases
#define MODE_RE_TRIS               TRISC5
#define MODE_RE_LAT                LATC5
#define MODE_RE_PORT               PORTCbits.RC5
#define MODE_RE_ANS                ANSC5
#define MODE_RE_SetHigh()    do { LATC5 = 1; } while(0)
#define MODE_RE_SetLow()   do { LATC5 = 0; } while(0)
#define MODE_RE_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define MODE_RE_GetValue()         PORTCbits.RC5
#define MODE_RE_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define MODE_RE_SetDigitalOutput()   do { TRISC5 = 0; } while(0)

#define MODE_RE_SetAnalogMode()   do { ANSC5 = 1; } while(0)
#define MODE_RE_SetDigitalMode()   do { ANSC5 = 0; } while(0)
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
// get/set Relay_RSET aliases
#define Relay_RSET_TRIS               TRISD2
#define Relay_RSET_LAT                LATD2
#define Relay_RSET_PORT               PORTDbits.RD2
#define Relay_RSET_ANS                ANSD2
#define Relay_RSET_SetHigh()    do { LATD2 = 1; } while(0)
#define Relay_RSET_SetLow()   do { LATD2 = 0; } while(0)
#define Relay_RSET_Toggle()   do { LATD2 = ~LATD2; } while(0)
#define Relay_RSET_GetValue()         PORTDbits.RD2
#define Relay_RSET_SetDigitalInput()    do { TRISD2 = 1; } while(0)
#define Relay_RSET_SetDigitalOutput()   do { TRISD2 = 0; } while(0)

#define Relay_RSET_SetAnalogMode()   do { ANSD2 = 1; } while(0)
#define Relay_RSET_SetDigitalMode()   do { ANSD2 = 0; } while(0)
// get/set Relay_SET aliases
#define Relay_SET_TRIS               TRISD3
#define Relay_SET_LAT                LATD3
#define Relay_SET_PORT               PORTDbits.RD3
#define Relay_SET_ANS                ANSD3
#define Relay_SET_SetHigh()    do { LATD3 = 1; } while(0)
#define Relay_SET_SetLow()   do { LATD3 = 0; } while(0)
#define Relay_SET_Toggle()   do { LATD3 = ~LATD3; } while(0)
#define Relay_SET_GetValue()         PORTDbits.RD3
#define Relay_SET_SetDigitalInput()    do { TRISD3 = 1; } while(0)
#define Relay_SET_SetDigitalOutput()   do { TRISD3 = 0; } while(0)

#define Relay_SET_SetAnalogMode()   do { ANSD3 = 1; } while(0)
#define Relay_SET_SetDigitalMode()   do { ANSD3 = 0; } while(0)
// get/set BP_ENBL1 aliases
#define BP_ENBL1_TRIS               TRISD4
#define BP_ENBL1_LAT                LATD4
#define BP_ENBL1_PORT               PORTDbits.RD4
#define BP_ENBL1_ANS                ANSD4
#define BP_ENBL1_SetHigh()    do { LATD4 = 1; } while(0)
#define BP_ENBL1_SetLow()   do { LATD4 = 0; } while(0)
#define BP_ENBL1_Toggle()   do { LATD4 = ~LATD4; } while(0)
#define BP_ENBL1_GetValue()         PORTDbits.RD4
#define BP_ENBL1_SetDigitalInput()    do { TRISD4 = 1; } while(0)
#define BP_ENBL1_SetDigitalOutput()   do { TRISD4 = 0; } while(0)

#define BP_ENBL1_SetAnalogMode()   do { ANSD4 = 1; } while(0)
#define BP_ENBL1_SetDigitalMode()   do { ANSD4 = 0; } while(0)
// get/set BP_ENBL2 aliases
#define BP_ENBL2_TRIS               TRISD5
#define BP_ENBL2_LAT                LATD5
#define BP_ENBL2_PORT               PORTDbits.RD5
#define BP_ENBL2_ANS                ANSD5
#define BP_ENBL2_SetHigh()    do { LATD5 = 1; } while(0)
#define BP_ENBL2_SetLow()   do { LATD5 = 0; } while(0)
#define BP_ENBL2_Toggle()   do { LATD5 = ~LATD5; } while(0)
#define BP_ENBL2_GetValue()         PORTDbits.RD5
#define BP_ENBL2_SetDigitalInput()    do { TRISD5 = 1; } while(0)
#define BP_ENBL2_SetDigitalOutput()   do { TRISD5 = 0; } while(0)

#define BP_ENBL2_SetAnalogMode()   do { ANSD5 = 1; } while(0)
#define BP_ENBL2_SetDigitalMode()   do { ANSD5 = 0; } while(0)
// get/set BP_ENBL3 aliases
#define BP_ENBL3_TRIS               TRISD6
#define BP_ENBL3_LAT                LATD6
#define BP_ENBL3_PORT               PORTDbits.RD6
#define BP_ENBL3_ANS                ANSD6
#define BP_ENBL3_SetHigh()    do { LATD6 = 1; } while(0)
#define BP_ENBL3_SetLow()   do { LATD6 = 0; } while(0)
#define BP_ENBL3_Toggle()   do { LATD6 = ~LATD6; } while(0)
#define BP_ENBL3_GetValue()         PORTDbits.RD6
#define BP_ENBL3_SetDigitalInput()    do { TRISD6 = 1; } while(0)
#define BP_ENBL3_SetDigitalOutput()   do { TRISD6 = 0; } while(0)

#define BP_ENBL3_SetAnalogMode()   do { ANSD6 = 1; } while(0)
#define BP_ENBL3_SetDigitalMode()   do { ANSD6 = 0; } while(0)
// get/set BP_ENBL4 aliases
#define BP_ENBL4_TRIS               TRISD7
#define BP_ENBL4_LAT                LATD7
#define BP_ENBL4_PORT               PORTDbits.RD7
#define BP_ENBL4_ANS                ANSD7
#define BP_ENBL4_SetHigh()    do { LATD7 = 1; } while(0)
#define BP_ENBL4_SetLow()   do { LATD7 = 0; } while(0)
#define BP_ENBL4_Toggle()   do { LATD7 = ~LATD7; } while(0)
#define BP_ENBL4_GetValue()         PORTDbits.RD7
#define BP_ENBL4_SetDigitalInput()    do { TRISD7 = 1; } while(0)
#define BP_ENBL4_SetDigitalOutput()   do { TRISD7 = 0; } while(0)

#define BP_ENBL4_SetAnalogMode()   do { ANSD7 = 1; } while(0)
#define BP_ENBL4_SetDigitalMode()   do { ANSD7 = 0; } while(0)
// get/set AN_CELL3 aliases
#define AN_CELL3_TRIS               TRISE0
#define AN_CELL3_LAT                LATE0
#define AN_CELL3_PORT               PORTEbits.RE0
#define AN_CELL3_ANS                ANSE0
#define AN_CELL3_SetHigh()    do { LATE0 = 1; } while(0)
#define AN_CELL3_SetLow()   do { LATE0 = 0; } while(0)
#define AN_CELL3_Toggle()   do { LATE0 = ~LATE0; } while(0)
#define AN_CELL3_GetValue()         PORTEbits.RE0
#define AN_CELL3_SetDigitalInput()    do { TRISE0 = 1; } while(0)
#define AN_CELL3_SetDigitalOutput()   do { TRISE0 = 0; } while(0)

#define AN_CELL3_SetAnalogMode()   do { ANSE0 = 1; } while(0)
#define AN_CELL3_SetDigitalMode()   do { ANSE0 = 0; } while(0)
// get/set AN_CELL2 aliases
#define AN_CELL2_TRIS               TRISE1
#define AN_CELL2_LAT                LATE1
#define AN_CELL2_PORT               PORTEbits.RE1
#define AN_CELL2_ANS                ANSE1
#define AN_CELL2_SetHigh()    do { LATE1 = 1; } while(0)
#define AN_CELL2_SetLow()   do { LATE1 = 0; } while(0)
#define AN_CELL2_Toggle()   do { LATE1 = ~LATE1; } while(0)
#define AN_CELL2_GetValue()         PORTEbits.RE1
#define AN_CELL2_SetDigitalInput()    do { TRISE1 = 1; } while(0)
#define AN_CELL2_SetDigitalOutput()   do { TRISE1 = 0; } while(0)

#define AN_CELL2_SetAnalogMode()   do { ANSE1 = 1; } while(0)
#define AN_CELL2_SetDigitalMode()   do { ANSE1 = 0; } while(0)
// get/set AN_CELL1 aliases
#define AN_CELL1_TRIS               TRISE2
#define AN_CELL1_LAT                LATE2
#define AN_CELL1_PORT               PORTEbits.RE2
#define AN_CELL1_ANS                ANSE2
#define AN_CELL1_SetHigh()    do { LATE2 = 1; } while(0)
#define AN_CELL1_SetLow()   do { LATE2 = 0; } while(0)
#define AN_CELL1_Toggle()   do { LATE2 = ~LATE2; } while(0)
#define AN_CELL1_GetValue()         PORTEbits.RE2
#define AN_CELL1_SetDigitalInput()    do { TRISE2 = 1; } while(0)
#define AN_CELL1_SetDigitalOutput()   do { TRISE2 = 0; } while(0)

#define AN_CELL1_SetAnalogMode()   do { ANSE2 = 1; } while(0)
#define AN_CELL1_SetDigitalMode()   do { ANSE2 = 0; } while(0)

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