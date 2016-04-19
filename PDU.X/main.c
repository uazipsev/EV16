#include "mcc_generated_files/mcc.h"
#include "Functions.h"
#include "PDU.h"
#include "Communications.h"

/*
                         Main application
 */
void main(void) {
    // Initialize the device
    SYSTEM_Initialize();
    PDUStartup();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowEnable();

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    LATCbits.LATC5 = 0;
    while (1) {
        //Delay(50);
        //LED2_SetLow();
        //Delay(50);
        //LED2_SetLow();
        //printf("ADC Volume = %d");
        // Add your application code
        updateComms();
    }
}
/**
 End of File
 */