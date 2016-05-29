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
#include <libpic30.h>
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

extern void UART_init(void);
extern unsigned char Receive_peek(void);
extern int Receive_available(void);
extern unsigned char Receive_get(void);
extern void Send_put(unsigned char _data);

extern void UART1_init(void);
extern unsigned char Receive_peek1(void);
extern int Receive_available1(void);
extern unsigned char Receive_get1(void);
extern void Send_put1(unsigned char _data);

extern void UART2_init(void);
extern unsigned char Receive_peek2(void);
extern int Receive_available2(void);
extern unsigned char Receive_get2(void);
extern void Send_put2(unsigned char _data);

extern void UART3_init(void);
extern unsigned char Receive_peek3(void);
extern int Receive_available3(void);
extern unsigned char Receive_get3(void);
extern void Send_put3(unsigned char _data);

extern void begin(volatile int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void), int (*stuffavailable)(void), unsigned char (*stuffpeek)(void));
extern void begin1(volatile int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void), int (*stuffavailable)(void), unsigned char (*stuffpeek)(void));
extern void begin2(volatile int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void), int (*stuffavailable)(void), unsigned char (*stuffpeek)(void));
extern void begin3(volatile int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void), int (*stuffavailable)(void), unsigned char (*stuffpeek)(void));

extern volatile int receiveArray[100];
extern volatile int receiveArray1[20];
extern volatile int receiveArray2[20];
extern volatile int receiveArray3[20];

extern void Setup(void);
extern void Delay(int wait);
void PinSetMode(void);

extern void initTimerOne();
extern volatile unsigned int time;
extern unsigned int brake;
void updateBrakeLight();
void ledDebug();

#endif	/* FUNCTIONS_H */

