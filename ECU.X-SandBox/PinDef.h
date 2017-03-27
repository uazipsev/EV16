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
#define INDICATOR _LATE13

#define SS_RELAY _LATA9
/*
 *   Safty Read in
 */
#define SS_state PORTAbits.RA4
#define SS_state_TRS TRISAbits.TRISA4

/*
 *    HORN
 */
#define HORN_EN _LATC4

/*
 *   Brake Light
 */
#define BRAKELT _LATC3

#define OUTPUT 0
#define INPUT  1
#define TALK   1
#define LISTEN 0
#define RS485_2_Direction_Tris TRISCbits.TRISC2
#define RS485_1_Direction_Tris TRISFbits.TRISF1
#define RS485_2_Direction   LATCbits.LATC2
#define RS485_1_Direction   LATFbits.LATF1
#define RX0_Tris TRISBbits.TRISB11
#define TX0_Tris TRISBbits.TRISB10
#define RX1_Tris TRISCbits.TRISC0
#define TX1_Tris TRISCbits.TRISC1
#define RX_Tris TRISCbits.TRISC8
#define TX_Tris TRISCbits.TRISC7
#define RX2_Tris TRISCbits.TRISC9
#define TX2_Tris TRISDbits.TRISD6

#define THROTTLE_SANITY_CHECK 1
#define THROTTLE_BRAKE_CHECK 2

#endif	/* PINDEF_H */

