/* 
 * File:   PinDef.h
 * Author: Rick
 *
 * Created on May 19, 2015, 1:18 AM
 */

#ifndef PINDEF_H
#define	PINDEF_H


#define ON         0
#define OFF        1

#define TALK 1
#define LISTEN 0

#define INPUT 1
#define OUTPUT 0

#define WEAK_PULL_UP 1

extern bool receiveData();
extern void sendData(unsigned char whereToSend);
extern void ToSend(const unsigned char where, const unsigned int what);

#define LED LATBbits.LATB9
#define LED_Tris TRISBbits.TRISB9
#define LED_Port PORTBbits.RB9
#define WDI _LATB12
#define WDI_Port PORTBbits.RB12
#define RS485 _LATC8
#define RS485_1_Tris TRISCbits.TRISC8
#define RS485_1_Port LATCbits.LATC8


#define RX1_Pin_Tris TRISCbits.TRISC6
#define TX1_Pin_Tris TRISCbits.TRISC7
#define RX1_Pin_Port LATCbits.LATC6
#define TX1_Pin_Port LATCbits.LATC7
#define RX1_Pin_Map RPINR18bits.U1RXR
#define RX1_PIN_SET 22
#define Pin_22_Output RPOR11bits.RP22R
#define Pin_23_Output RPOR11bits.RP23R
#define TX1_OUTPUT 3

#define RX2_Pin_Map RPINR19bits.U2RXR
#define Pin_8_Output RPOR4bits.RP8R
#define TX2_OUTPUT 7


#endif	/* PINDEF_H */

