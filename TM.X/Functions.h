/* 
 * File:   Function.h
 * Author: Rick
 *
 * Created on May 12, 2015, 1:00 AM
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#ifndef __DELAY_H
#define FOSC  72000000LL  // clock-frequecy in Hz with suffix LL (64-bit-long), eg. 32000000LL for 32MHz
#define FCY       (FOSC/2)  // MCU is running at FCY MIPS
#define delay_us(x) __delay32(((x*FCY)/1000000L)) // delays x us
#define delay_ms(x) __delay32(((x*FCY)/1000L))  // delays x ms
#define __DELAY_H 1
#incle <libpic30.h>
#endif

#define PPSin(fn,pin)    iPPSInput(IN_FN_PPS##fn,IN_PIN_PPS##pin)
#define PPSout(fn,pin)    iPPSOutput(OUT_PIN_PPS##pin,OUT_FN_PPS##fn)

#define RX1_Pin_Map RPINR18bits.U1RXR
#define RX2_Pin_Map RPINR19bits.U2RXR
#define RX3_Pin_Map RPINR27bits.U3RXR
#define RX4_Pin_Map RPINR28bits.U4RXR

#define Pin_42_Output RPOR4bits.RP42R
#define Pin_49_Output RPOR5bits.RP49R
#define Pin_55_Output RPOR6bits.RP55R
#define Pin_56_Output RPOR7bits.RP56R
#define Pin_70_Output RPOR8bits.RP70R

#define TX1_Output 1
#define TX2_Output 3
#define TX3_Output 27
#define TX4_Output 29

void ReadReset();
int GetResetValue();



extern void Setup(void);
extern void Delay(int wait);
void PinSetMode(void);

extern void initTimerOne();
extern volatile unsigned int time;
extern unsigned int brake;
void updateBrakeLight();
void ledDebug();

#endif	/* FUNCTIONS_H */

