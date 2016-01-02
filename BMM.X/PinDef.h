/* 
 * File:   PinDef.h
 * Author: Rick
 *
 * Created on May 12, 2015, 12:00 AM
 */

#ifndef PINDEF_H
#define	PINDEF_H

#define true 1
#define false 0

#define OUTPUT 0
#define INPUT  1

#define RX1_Pin_Map RPINR18bits.U1RXR
#define RX2_Pin_Map RPINR19bits.U2RXR
#define RX1_PIN_SET 24
#define RX2_PIN_SET 22
#define Pin_22_Output RPOR11bits.RP22R
#define Pin_23_Output RPOR11bits.RP23R
#define Pin_24_Output RPOR12bits.RP24R
#define Pin_25_Output RPOR12bits.RP25R
#define TX1_OUTPUT 3
#define TX2_OUTPUT 5
/*
 *  RS485 Flow control
 */
#define RS_RE_DE PORTBbits.RB0
/*
 *      BMS Bus Select Mux Pins
 */
 #define S0_TRIS TRISAbits.TRISA4     //Select Comm Line Mux S0
 #define S1_TRIS TRISBbits.TRISB4     //Select Comm Line Mux S1
 #define S0 LATAbits.LATA4
 #define S1 LATBbits.LATB4
/*
 
 */
#define BMS_TURN_ON LATBbits.LATB5


/*
 *    LED :)
 */
#define INDICATOR LATBbits.LATB1

/*
 *   Motor Control Pins
 */
#define FORWARD PORTCbits.RC1
#define REVERSE PORTCbits.RC2
#define BRAKE   PORTAbits.RA8
#define PROGEN  PORTBbits.RB4
#define REGENEN PORTAbits.RA4

/*
 *   DigiPot control lines
 */
#define DIGI_CS     PORTBbits.RB15
#define DIGI_INC    PORTBbits.RB14
#define DIGI_UP_DN  PORTAbits.RA7

/*
 *    Relay control 
 */
#define Analog_Relay _LATA0
#define Analog_Relay_Port PORTAbits.RA0

/*
 *    12 DC/DC
 */
#define DC12EN _LATA10

/*
 *    FAN PWM
 */
#define FAN !_LATB5


#endif	/* PINDEF_H */

