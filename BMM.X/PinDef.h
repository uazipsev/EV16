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
#define RS_RE_DE PORTBbits.RB7
#define BMS_TURN_ON LATBbits.LATB5
/*
 *    LED :)
 */
#define INDICATOR LATBbits.LATB1
/*
 *    Relay control 
 */
#define Saftey_Relay_Set PORTBbits.RB3
#define Saftey_Relay_Reset PORTBbits.RB2
/*
 *    LT6020 CS & EN
 */
#define LT6020_1_CS PORTAbits.RA4
#define LT6020_2_CS PORTAbits.RA8
#define LT6020_1_EN PORTAbits.RA9
#define LT6020_2_EN PORTBbits.RB4

/*
 
 * SPI PPS mapping
 
 */
#define MOSI_Pin_Map RPOR20bits.SDO1
#define MISO_Pin_Map RPINR20bits.SDI1R
#define SCK_Pin_Map  RPOR21bits.SCK1


#endif	/* PINDEF_H */

