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

#define FORWARD _LATB4
#define REVERSE _LATA8
#define BRAKE   _LATA9
#define PROGEN  _LATA4
#define REGENEN _LATC4
#define IGNEN   _LATC3


#define FORWARD_R PORTBbits.RB4
#define REVERSE_R PORTAbits.RA8
#define BRAKE_R   PORTAbits.RA9
#define PROGEN_R  PORTAbits.RA4
#define REGENEN_R PORTCbits.RC4
#define IGNEN_R   PORTCbits.RC3

#define FORWARD_TRIS TRISBbits.TRISB4
#define REVERSE_TRIS TRISAbits.TRISA8
#define BRAKE_TRIS   TRISAbits.TRISA9
#define PROGEN_TRIS  TRISAbits.TRISA4
#define REGENEN_TRIS TRISCbits.TRISC4
#define IGNEN_TRIS   TRISCbits.TRISC3

/*
 *    12 DC/DC
 */
#define DC12DISABLE LATAbits.LATA10=0
#define DC12ENABLE  LATAbits.LATA10=1
/*
 *    Relay
 */
#define DACRELAY _LATB5
#define DACRELAY_TRIS TRISBbits.TRISB5 


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

