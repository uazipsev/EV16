#include <xc.h>
#include "../UART.h"
#include "tmr0.h"
#include "tmr2.h"
#include "adc.h"
#include "i2c1.h"

void  INTERRUPT_Initialize (void)
{
    // Disable Interrupt Priority Vectors (16CXXX Compatibility Mode)
    RCONbits.IPEN = 0;

    // Clear peripheral interrupt priority bits (default reset value)

    // RCI
    IPR1bits.RC1IP = 0;
    // TXI
    IPR1bits.TX1IP = 0;
    // TMRI
    INTCON2bits.TMR0IP = 0;
    // ADI
    IPR1bits.ADIP = 0;
    // SSPI
    IPR1bits.SSP1IP = 0;
    // BCLI
    IPR2bits.BCL1IP = 0;
    IPR1bits.TMR2IP=0;
    
}

void interrupt INTERRUPT_InterruptManager (void)
{
   // interrupt handler
    if(PIE1bits.RC1IE == 1 && PIR1bits.RC1IF == 1)
    {
        EUSART1_Receive_ISR();
    }
    else if(PIE1bits.TX1IE == 1 && PIR1bits.TX1IF == 1)
    {
        EUSART1_Transmit_ISR();
    }
    else if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1)
    {
        TMR0_ISR();
    }
    else if(PIE1bits.TMR2IE == 1 && PIR1bits.TMR2IF == 1)
    {
        TMR2_ISR();
    }
    else if(PIE1bits.ADIE == 1 && PIR1bits.ADIF == 1)
    {
        ADC_ISR();
    }
    else if(PIE1bits.SSP1IE == 1 && PIR1bits.SSP1IF == 1)
    {
        I2C1_ISR();
    }
    else if(PIE2bits.BCL1IE == 1 && PIR2bits.BCL1IF == 1)
    {
        I2C1_BusCollisionISR();
    }
    else
    {
        //Unhandled Interrupt
    }
}

/**
 End of File
*/