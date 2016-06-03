
#include <xc.h>
#include <stdbool.h>
//#include "ADC.h"
#include "PinDef.h"
#include "pps.h"
#include "ADDRESSING.h"
#include "Functions.h"
#include <stdio.h>
#include "pps.h"

void Setup(void) {

    PinSetMode();
    // setup internal clock for 72MHz/36MIPS
    // 12 /2 = 6  *24 = 144 / 2=72
    CLKDIVbits.PLLPRE = 0; // PLLPRE (N2) 0=/2c
    CLKDIVbits.DOZE = 0;
    PLLFBD = 22; // pll multiplier (M) = +2
    CLKDIVbits.PLLPOST = 0; // PLLPOST (N1) 0=/2   
    // Initiate Clock Switch to Primary Oscillator with PLL (NOSC = 0b011)
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(OSCCON | 0x01);
    // Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b011);
    while (!OSCCONbits.LOCK); // wait for PLL ready


    INTCON1bits.NSTDIS = 1; //no nesting of interrupts
    timerOne();
    initADC();
    //timerTwo();
    begin(receiveArray, sizeof (receiveArray), SAS_ADDRESS, false, Send_put, Receive_get, Receive_available, Receive_peek);
    UART_init();
    UART1_init();
    //begin(receiveArray1, sizeof (receiveArray1), SAS_ADDRESS, false, Send_put1, Receive_get1, Receive_available1, Receive_peek1);

}

void timerOne(void) {
    T1CONbits.TON = 0; // turn off timer
    T1CONbits.TCS = 0; //internal instruction clock (36,000,000 Hertz)
    T1CONbits.TCKPS = 0b10; //11/10 /01  /00   //0b10 - 64 divider 0-1:1
    PR1 = 586; //75/600/4500/37500// 0.001s timer
    IFS0bits.T1IF = 0; // clear interrupt flag
    IEC0bits.T1IE = 1; // enable timer 1 interrupt
    T1CONbits.TON = 1; // turn on timer
}
//

void timerTwo(void) {
    // timer 2
    T2CONbits.T32 = 0;
    T2CONbits.TON = 0; //disable timer 2
    T2CONbits.TCS = 0; //internal instruction clock (36,000,000 Hertz)
    T2CONbits.TGATE = 0; //disable gated timer mode
    T2CONbits.TCKPS = 0b11; // 1:256 prescalar    60MHz/256= 234.375KHz (4.266us)
    //TMR2 = 0x00; //clear timer register
    PR2 = 30000; //- set to 279 ms per overflow (4.266 us * 65535)= 279 ms
    IFS0bits.T2IF = 0; // clear timer2 interrupt flag
    IEC0bits.T2IE = 1; // enable timer2 interrupt
    T2CONbits.TON = 1; //enable timer 2
}

//void initUART1(void)
//{
//    U1MODEbits.BRGH = 0; // 16 multiplier
//    U1BRG = 64; // 57600 baud rate
//    U1MODEbits.UARTEN = 1; // enable uart
//}

//void inputCapture(void)
//{
//    // Initialize the Input Capture Module
//    IC1CON1bits.ICM = 0b00; // Disable Input Capture 1 module
//    IC1CON1bits.ICTSEL= 1; // Select Timer2 as the IC1 Time base
//    IC1CON1bits.ICI = 0b00; // Interrupt on every capture event
//    IC1CON1bits.ICM = 0b010; // Generate capture event on every Falling edge
//
//    // Enable Capture Interrupt And Timer2
//    IPC0bits.IC1IP = 1; // Setup IC1 interrupt priority level
//    IFS0bits.IC1IF = 0; // Clear IC1 Interrupt Status Flag
//    IEC0bits.IC1IE = 1; // Enable IC1
//
//    //pin remap
//    RPINR7bits.IC1R = 98; // right tread
//
//    // Initialize the Input Capture Module
//    IC2CON1bits.ICM = 0b00; // Disable Input Capture 2 module
//    IC2CON1bits.ICTSEL = 1; // Select Timer2 as the IC2 Time base
//    IC2CON1bits.ICI = 0b00; // Interrupt on every capture event
//    IC2CON1bits.ICM = 0b010; // Generate capture event on every Falling edge
//
//    // Enable Capture Interrupt And Timer2
//    IPC1bits.IC2IP = 1; // Setup IC2 interrupt priority level
//    IFS0bits.IC2IF = 0; // Clear IC2 Interrupt Status Flag
//    IEC0bits.IC2IE = 1; // Enable IC2
//
//    //pin remap
//    RPINR7bits.IC2R = 99; // left tread
//}

void PinSetMode(void) {
    LED_Tris = OUTPUT;
    LED_Port = 1; // LED indicator OUT
    RS485_1_Tris = OUTPUT; //RS485 Flow OUT
    RS485_1_Port = LISTEN;
    RX1_Pin_Tris = INPUT;
    RX1_Pin_Port = 1;
    TRISAbits.TRISA0=INPUT;
    TRISAbits.TRISA1=INPUT;
    TRISBbits.TRISB2=INPUT;

    RS485_1_Port = 0;
    PPSUnLock;
    Pin_23_Output = TX1_OUTPUT;
    RX1_Pin_Map = 22;

    PPSin(_U2RX, _RP8);
    PPSout(_U2TX, _RP7);

    PPSLock;
}

void Delay(int wait) {
    int x = 0;
    for (; x < wait; x++) {
        delay_ms(1);
    }
}