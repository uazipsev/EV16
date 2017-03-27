/* 
 * File:   PinDef.h
 * Author: richc
 *
 * Created on August 11, 2016, 10:17 PM
 */

#ifndef PINDEF_H
#define	PINDEF_H

#define true 1
#define false 0
#define OUTPUT 0
#define INPUT  1
#define TALK   1
#define LISTEN 0

#define _XTAL_FREQ  16000000

/*
 *  RS485 Flow control
 */
#define RS485_TSS_Direction_Tris TRISDbits.TRISD4
#define RS485_TSS_Direction   LATDbits.LATD4

/*
 *    LED :)
 */
#define INDICATOR LATAbits.LATA3
#define INDICATOR_TRIS TRISAbits.TRISA3

/*
 *   Safty inputs
 */
#define ECU_FAULT PORTCbits.RC5
#define ECU_FAULT_TRIS TRISCbits.TRISC5
#define BOTS_FAULT PORTCbits.RC4
#define BOTS_FAULT_TRIS TRISCbits.TRISC4
#define AMD_FAULT PORTDbits.RD3
#define AMD_FAULT_TRIS TRISDbits.TRISD3
#define STOP_L_FAULT PORTDbits.RD2
#define STOP_L_FAULT_TRIS TRISDbits.TRISD2
#define STOP_R_FAULT PORTDbits.RD1
#define STOP_R_FAULT_TRIS TRISDbits.TRISD1
#define STOP_C_FAULT PORTDbits.RD0
#define STOP_C_FAULT_TRIS TRISDbits.TRISD0
#define IMD_FAULT PORTCbits.RC3
#define IMD_FAULT_TRIS TRISCbits.TRISC3
#define BPD_FAULT PORTCbits.RC2
#define BPD_FAULT_TRIS TRISCbits.TRISC2
#define TSMS_FAULT PORTCbits.RC1
#define TSMS_FAULT_TRIS TRISCbits.TRISC1
#define IS_FAULT PORTAbits.RA7
#define IS_FAULT_TRIS TRISAbits.TRISA7

#define AUX_FAULT PORTCbits.RC0
#define AUX_FAULT_TRIS TRISCbits.TRISC0

#define IMD_INPUT PORTAbits.RA6
#define IMD_INPUT_TRIS TRISAbits.TRISA6

#define RTG_INPUT PORTAbits.RA4
#define RTG_INPUT_TRIS TRISAbits.TRISA4

#endif	/* PINDEF_H */

