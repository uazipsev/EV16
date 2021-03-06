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
#define ON    0
#define OFF   1

/*
 *  RS485 Flow control
 */
#define RS_RE_DE PORTBbits.RB0

/*
 *    LED :)
 */
#define INDICATOR _LATE13

#define OUTPUT 0
#define INPUT  1
#define TALK   1
#define LISTEN 0
#define RS485_TSS_Direction_Tris TRISFbits.TRISF1
#define RS485_TSS_Direction   LATFbits.LATF1
//#define RX1_Tris TRISBbits.TRISB11
//#define TX1_Tris TRISBbits.TRISB10
//#define RX2_Tris TRISCbits.TRISC0
//#define TX2_Tris TRISCbits.TRISC1
//#define RX3_Tris TRISCbits.TRISC8
//#define TX3_Tris TRISCbits.TRISC7
#define RX4_Tris TRISCbits.TRISC1
#define TX4_Tris TRISCbits.TRISC0

#endif	/* PINDEF_H */

