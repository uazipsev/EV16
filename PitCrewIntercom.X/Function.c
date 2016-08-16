#include "Function.H"
#include "Timer.h"
#include "UART.h"
#include <xc.h>
#include "PinDef.h"
#include "Radio.h"
#include "ADC.h"

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

void Start(void){
    /*
     * OSS
     */
    OSCCONbits.IRCF = 13;
    OSCCONbits.SCS = 2;
    OSCCONbits.SPLLEN = 0;
    /*
     *  I/O
     */
    TRISCbits.TRISC7 = 0; //set RC7 as output PushToTalkRadio
    TRISCbits.TRISC6 = 0; //set RC6 as output RadioPowerDown
    TRISCbits.TRISC5 = 0; //set RC5 as output LED Blue
    TRISCbits.TRISC4 = 0; //set RC4 as output LED Green
    TRISCbits.TRISC3 = 0; //set RC4 as output LED Red
    TRISAbits.TRISA2 = 1; //set RA2 as input  PushToTalkButton
    TRISCbits.TRISC0 = 1; //set RC0 as input  S1
    TRISCbits.TRISC1 = 1; //set RC1 as input  S2
    TRISAbits.TRISA4 = 1; //set RA4 as input  MIC
    /*
     *  Analog pins that we want digital
     */
    ANSELCbits.ANSC0 = 0; //set RC1 as digital S1
    ANSELCbits.ANSC1 = 0; //set RC1 as digital S1
    ANSELAbits.ANSA2 = 0; //set RA2 as digital PushToTalkButton
    ANSELCbits.ANSC3 = 0; //set RC3 as digital LED Red
    ANSELCbits.ANSC6 = 0; //set RC6 as digital RadioPowerDown
    ANSELCbits.ANSC7 = 0; //set RC7 as digital PushToTalkRadio
    /*
     */
    APFCON0bits.RXDTSEL = 0;
    APFCON0bits.TXCKSEL = 0;
    /*
     *  ADC This is for battery level
     */
    ADC_Initialize();
    /*
     *  UART
     */
    EUSART1_Initialize();
    /*
     *  TMR
     */
    INTERRUPT_Initialize();
    TMR2_Initialize();
}

//Used to allow for longer delays if required. 
void Delay(int wait) {
    int x;
    for (x = 0; x < wait; x++) {
        __delay_ms(1); //using predef fcn NOTE: Delay_MS is wrong...1ms is not 1 ms of wait....
    }
}

void INTERRUPT_Initialize(){
// Interrupt Registers
  INTCON = 0;           // clear the interrpt control register
  INTCONbits.TMR0IE = 0;        // bit5 TMR0 Overflow Interrupt Enable bit...0 = Disables the TMR0 interrupt
  PIR1bits.TMR2IF = 0;            // clear timer1 interupt flag TMR1IF
  PIE1bits.TMR2IE = 1;         // enable Timer2 interrupts
  INTCONbits.TMR0IF = 0;        // bit2 clear timer 0 interrupt flag
  INTCONbits.GIE = 1;           // bit7 global interrupt enable
  INTCONbits.PEIE = 1;          // bit6 Peripheral Interrupt Enable bit...1 = Enables all unmasked peripheral interrupts
}

void interrupt INTERRUPT_InterruptManager(void)
{
    if(PIE1bits.TMR2IE == 1 && PIR1bits.TMR2IF == 1)
    {
        TMR2_ISR();
    }
    else
    {
        //Unhandled Interrupt
    }
}

char ReadCharger(void){
    //Precharge or charging
    if(!ChargerS0 && ChargerS1){
        return CHARGING;         
    }
    //Done charging
    if(ChargerS0 && !ChargerS1){
        return DONE; 
    }
    //Charger off - falt etc
    if(ChargerS0 && ChargerS1){
        return OFF; 
    }
    else{
        return 255;
    }
}

void LEDOff(void){
    LED_Red = 0;
    LED_Green = 0;
    LED_Blue = 0;
}
