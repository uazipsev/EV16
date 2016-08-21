/*******************************************************************
 * @brief           Functions.c
 * @brief           A catch all for random fcn's for the device
 * @return          N/A
 * @note            Author: Zac Kilburn
 *******************************************************************/
#include "xc.h"
#include "PinDef.h"
#include <libpic30.h>
#include <stdio.h>
#include <stdbool.h>
#include "Functions.h"
#include "Communications.h"
#include "Timers.h"
#include "pps.h"

int BrakeLightThreshold = 0;


int read= 0;

/*******************************************************************
 * @brief           Setup
 * @brief           This sets up the device
 * @return          N/A
 * @note            OSSC - USART - I2C - PPS - CONFIGS
 *******************************************************************/
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
    PPSout(_U1TX, _RP43);
    PPSin(_U1RX, _RP42);

    //RX1/TX1  -- RS485-2 (U1) --BMM -MCS
    PPSout(_U2TX, _RP48);
    PPSin(_U2RX, _RP49);

    //RX2/TX2  --SWITCH becomes RX3/TX3 (USB) -> RX4/TX4 (WIRELESS)
    PPSout(_U3TX, _RP57);
    PPSin(_U3RX, _RP70);

    //RX2/TX2 -- RS485 Full Duplex --Telem Master
    PPSout(_U4TX, _RP55);
    PPSin(_U4RX, _RP56);
    
    PPSLock;
    
    TSSCommsStart();

    //This controls the timing system to control communication rates  
    initTimerOne();
}

/*******************************************************************
 * @brief           Delay
 * @brief           its a delay..duh
 * @return          N/A
 * @note            This fcn uses delay_ms - provided by xc.h
 *******************************************************************/
void Delay(int wait) {
    int x;
    for (x = 0; x < wait; x++) {
        delay_ms(1); //using predef fcn
    }
}

/*******************************************************************
 * @brief           PinSetMode
 * @brief           Pin configuration
 * @return          N/A
 * @note            Sets up I/O on the device
 *******************************************************************/
void PinSetMode(void) {
    TRISEbits.TRISE13 = OUTPUT; //Set LED as output
    RS485_TSS_Direction_Tris = OUTPUT;
    RS485_TSS_Direction = LISTEN;
//    TRISCbits.TRISC10=OUTPUT;
//    TRISCbits.TRISC4=OUTPUT;
//    TRISCbits.TRISC3=OUTPUT;
//    TRISAbits.TRISA9=OUTPUT;
//    LATCbits.LATC10 = 0;
//    ANSELCbits.ANSC0 = 0;
//    ANSELAbits.ANSA4 = 1;
//    ANSELCbits.ANSC3 = 1;
//    //RX0_Tris=OUTPUT;
//    //TX0_Tris=OUTPUT;
//    //RX1_Tris=OUTPUT;
//    //TX1_Tris=OUTPUT;
//    //RX_Tris=OUTPUT;
//    //TX_Tris=OUTPUT;
//    //RX2_Tris=OUTPUT;
//    //TX2_Tris=OUTPUT;
}

/*******************************************************************
 * @brief           ledDebug
 * @brief           Allows us to see device activity
 * @return          N/A
 * @note            uses timer to control the function tick rate
 *******************************************************************/
void ledDebug(){
    if (GetTime(TIME) > 250) {
        INDICATOR ^= 1;
        SetTime(TIME);
    }
}

/*******************************************************************
 * @brief           ReadReset
 * @brief           This fcn reads in the RCON
 * @return          N/A
 * @note            This fcn saves the RCON RIGHT AT BOOT! This is important for v
 *******************************************************************/
void ReadReset(){
    read = RCON;
    RCON = 0;
}

/*******************************************************************
 * @brief           GetResetValue
 * @brief           getter
 * @return          return RCON (int - 16 bit)
 * @note            Acts are a getter to keep data integrity 
 *******************************************************************/
int GetResetValue(){
    return read;
}

