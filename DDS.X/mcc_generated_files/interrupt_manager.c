#include <xc.h>

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
    else
    {
        //Unhandled Interrupt
    }
}

/**
 End of File
*/