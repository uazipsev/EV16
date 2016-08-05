#include "Function.H"
#include "Timer.h"
#include "UART.h"
#include <xc.h>
#include "PinDef.h"
#include "Radio.h"
#include "ADC.h"

void Start(void){
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
    if(PIE1bits.RCIE == 1 && PIR1bits.RCIF == 1)
    {
        EUSART1_Receive_ISR();
    }
    if(PIE1bits.TXIE == 1 && PIR1bits.TXIF == 1)
    {
        EUSART1_Transmit_ISR();
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
    LED_Red = 1;
    LED_Green = 1;
    LED_Blue = 1;
}
