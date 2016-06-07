
#include "xc.h"
#include <libpic30.h>
#include "pps.h"
#include <stdbool.h>
#include "Function.h"
#include "I2C.h"
#include "MotorControler.h"
#include "PinDef.h"
#include "ADDRESSING.h"
#include "Timers.h"

void Setup(void) {
    //MotorDisable();
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

    PPSout(_U1TX, _RP22);
    PPSin(_U1RX, _RP23);

    //Pin_23_Output = TX1_OUTPUT;
    //RX1_Pin_Map = 22;
    PPSLock;
    
    PinSetMode();
    UART_init();
    begin(receiveArray, sizeof (receiveArray), MCS_ADDRESS, false, Send_put, Receive_get, Receive_available, Receive_peek);

    i2c_init();
    timerOne();
    //SetMotorDefaults();
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
    INDICATOR_TRIS = OUTPUT;
    
    //RX1_Pin_Tris = INPUT;
    //TX1_Pin_Tris = OUTPUT;        
    
    DC12_TRIS = OUTPUT;

    DACRELAY_TRIS = OUTPUT;
    
    RS485_1_Tris = OUTPUT;
    FORWARD_TRIS = OUTPUT;
    REVERSE_TRIS = OUTPUT;
    BRAKE_TRIS   = OUTPUT;
    PROGEN_TRIS  = OUTPUT;
    REGENEN_TRIS = OUTPUT;
    IGNEN_TRIS = OUTPUT;
    DACRELAY_TRIS = OUTPUT;
}
