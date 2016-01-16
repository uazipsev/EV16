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

/*
 *  RS485 Flow control
 */
#define RS_RE_DE PORTBbits.RB0

/*
 *    LED :)
 */
#define INDICATOR _LATB1

/*
 *   Motor Control Pins
 */


#define FORWARD _LATC1
#define REVERSE _LATC2
#define BRAKE   _LATA8
#define PROGEN  _LATB4
#define REGENEN _LATA4


#define FORWARD_R PORTCbits.RC1
#define REVERSE_R PORTCbits.RC2
#define BRAKE_R   PORTAbits.RA8
#define PROGEN_R  PORTBbits.RB4
#define REGENEN_R PORTAbits.RA4

#define FORWARD_TRIS TRISCbits.TRISC1
#define REVERSE_TRIS TRISCbits.TRISC2
#define BRAKE_TRIS   TRISAbits.TRISA8
#define PROGEN_TRIS  TRISBbits.TRISB4
#define REGENEN_TRIS TRISAbits.TRISA4

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
#define DC12DISABLE LATAbits.LATA10=1
#define DC12ENABLE  LATAbits.LATA10=0

/*
 *    FAN PWM
 */
#define FAN !_LATB5



#define RX1_Pin_Tris TRISCbits.TRISC6
#define TX1_Pin_Tris TRISCbits.TRISC7
#define RX1_Pin_Port PORTCbits.RC6
#define TX1_Pin_Port PORTCbits.RC7
#define RX1_Pin_Map RPINR18bits.U1RXR
#define RX1_PIN_SET 22
#define Pin_22_Output RPOR11bits.RP22R
#define Pin_23_Output RPOR11bits.RP23R
#define TX1_OUTPUT 3
#define RS485_1_Port LATBbits.LATB13
#define TALK 1
#define LISTEN 0

#endif	/* PINDEF_H */

