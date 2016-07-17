/*
 * File:   Functions.c
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015
 */
#include "xc.h"
#include "pps.h"
#include "PinDef.h"
#include "ADDRESSING.h"
#include <libpic30.h>
#include <stdio.h>
#include <stdbool.h>
#include "Functions.h"

#define BRAKE_LIGHT_THRESHOLD 21


int read= 0;

void Setup(void) {

                  // __C30_UART=2;
    PinSetMode();
    // setup internal clock for 72MHz/36MIPS
    // 12/2=6*24=132/2=72
    CLKDIVbits.PLLPRE = 0; // PLLPRE (N2) 0=/2
    PLLFBD = 22; // pll multiplier (M) = +2
    CLKDIVbits.PLLPOST = 0; // PLLPOST (N1) 0=/2
      // Initiate Clock Switch to Primary Oscillator with PLL (NOSC = 0b011)
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(OSCCON | 0x01);
    // Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b011);
    while (!OSCCONbits.LOCK); // wait for PLL ready

    INTCON1bits.NSTDIS = 1; //No nesting of interrupts

    PPSUnLock;
    //RX0/TX0  -- RS485-1 (U3) --SAS -DDS
    Pin_42_Output = TX2_Output;
    RX1_Pin_Map = 48;

    //RX1/TX1  -- RS485-2 (U1) --BMM -MCS
    Pin_49_Output = TX1_Output;
    RX2_Pin_Map = 43;

    //RX/TX  --SWITCH becomes RX3/TX3 (USB) -> RX4/TX4 (WIRELESS)
    Pin_55_Output = TX3_Output;
    RX3_Pin_Map = 56;

    //RX2/TX2 -- RS485 Full Duplex --Telem Master
    Pin_70_Output = TX4_Output;
    RX4_Pin_Map = 57;

    //PPSout(_OC1, _RP37);
    PPSLock;

    UART_init();
    UART1_init();
    UART2_init();
    UART3_init();

    begin(receiveArray, sizeof (receiveArray), ECU_ADDRESS, false, Send_put, Receive_get, Receive_available, Receive_peek);
    begin1(receiveArray1, sizeof (receiveArray1), ECU_ADDRESS, false, Send_put1, Receive_get1, Receive_available1, Receive_peek1);
    //begin2(receiveArray2, sizeof (receiveArray2), ECU_ADDRESS, false, Send_put2, Receive_get2, Receive_available2, Receive_peek2);
    begin3(receiveArray3, sizeof (receiveArray3), ECU_ADDRESS, false, Send_put3, Receive_get3, Receive_available3, Receive_peek3);

    //PWM_Init();
    initTimerOne();
}

void Delay(int wait) {
    int x;
    for (x = 0; x < wait; x++) {
        delay_ms(1); //using predef fcn
    }
}

void PinSetMode(void) {
    TRISBbits.TRISB10=INPUT;
    TRISEbits.TRISE13 = OUTPUT; //Set LED as output
    TRISBbits.TRISB6 = OUTPUT; //Set Brake Light as OUTPUT
    TRISBbits.TRISB5 = OUTPUT; //Set HORN PWM as OUTPUT
    SS_state_TRS = INPUT;     //Set Safty feedback as input
    RS485_1_Direction_Tris = OUTPUT;
    RS485_2_Direction_Tris = OUTPUT;
    RS485_1_Direction = LISTEN;
    RS485_2_Direction = LISTEN;
    TRISCbits.TRISC10=OUTPUT;
    TRISCbits.TRISC4=OUTPUT;
    TRISCbits.TRISC3=OUTPUT;
    TRISAbits.TRISA9=OUTPUT;
    LATCbits.LATC10 = 0;
    ANSELCbits.ANSC0 = 0;
    ANSELAbits.ANSA4 = 1;
    ANSELCbits.ANSC3 = 1;
    //RX0_Tris=OUTPUT;
    //TX0_Tris=OUTPUT;
    //RX1_Tris=OUTPUT;
    //TX1_Tris=OUTPUT;
    //RX_Tris=OUTPUT;
    //TX_Tris=OUTPUT;
    //RX2_Tris=OUTPUT;
    //TX2_Tris=OUTPUT;

}

void ledDebug(){
    if (time > 1000) {
            INDICATOR ^= 1;
           // HORN_EN ^=1;
           // BRAKELT ^= 1;
            SS_RELAY ^= 1;
            time = 0;
        }
    }
//TODO May need update Values  
void updateBrakeLight() {
    if (brake > BRAKE_LIGHT_THRESHOLD) {
        BRAKELT = 1;
    } else if (brake<(BRAKE_LIGHT_THRESHOLD-3))  //Prevent Ossicliation Number subject to chan
       BRAKELT = 0;
}

void ReadReset(){
    read = RCON;
    RCON = 0;
}

int GetResetValue(){
    return read;
}