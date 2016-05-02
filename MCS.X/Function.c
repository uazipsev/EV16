
#include "xc.h"
#include <libpic30.h>
#include <pps.h>
#include <stdbool.h>
#include "Function.h"
#include "I2C.h"
#include "pwm.h"
#include "MotorControler.h"
#include "PinDef.h"
#include "ADDRESSING.h"
#include "Timers.h"

void Setup(void) {
    MotorDisable();
    // setup internal clock for 66MHz/33MIPS
    // 12/2=6*22=132/2=66
    CLKDIVbits.PLLPRE = 0; // PLLPRE (N2) 0=/2
    PLLFBD = 22; // pll multiplier (M) = +2
    CLKDIVbits.PLLPOST = 0; // PLLPOST (N1) 0=/2
    // Initiate Clock Switch to Primary Oscillator with PLL (NOSC = 0b011)
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(OSCCON | 0x01);
    // Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b011);
    while (!OSCCONbits.LOCK); // wait for PLL ready

    PPSUnLock;

    PPSout(_U2TX, _RP7);
    PPSout(_OC1, _RP5);

    PPSin(_U2RX, _RP6);

    Pin_23_Output = TX1_OUTPUT;
    RX1_Pin_Map = 22;
    PPSLock;
    
    PinSetMode();
    UART_init();
    begin(receiveArray, sizeof (receiveArray), MCS_ADDRESS, false, Send_put, Receive_get, Receive_available, Receive_peek);

    i2c_init();
    timerOne();
    SetMotorDefaults();
}

void Delay(int wait) {
    int x;
    for ( x = 0; x < wait; x++) {
        delay_ms(1); //using predef fcn
    }
}

void ledDebug() {
    if (getLEDTime() > 1000) {
        ClearLEDTime();
        INDICATOR ^= 1;
    }
}
    

void PinSetMode(void) {
    AD1PCFGLbits.PCFG11 = 1;

    LATCbits.LATC6 = 1;

    TRISBbits.TRISB13 = 0;
    LATBbits.LATB13 = 0;

    TRISBbits.TRISB1 = 0; //Set LED as output
    TRISAbits.TRISA0 = 0; //DAC relay OUT
    TRISAbits.TRISA10 = 0; //Set 12v DC/DC enable OUT

    TRISBbits.TRISB15 = 0; //DigiPot CS OUT
    TRISBbits.TRISB14 = 0; //DigiPot INC OUT
    TRISAbits.TRISA7 = 0; //DigiPot UP_DN OUT

    TRISBbits.TRISB5 = 0; //Fan control OUT
    
    FORWARD_TRIS =0;
    REVERSE_TRIS =0;
    BRAKE_TRIS   =0;
    PROGEN_TRIS  =0;
    REGENEN_TRIS =0;
    IGNEN_TRIS = 0;
    DACRELAY_TRIS = 0;
    
}
