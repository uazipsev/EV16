

#include "mcc_generated_files/mcc.h"
#include "Functions.h"

/*
                         Main application
 */

int Start = 0;

void main(void) {
    // Initialize the device
    SYSTEM_Initialize();

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
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1) {
        if((Start_GetValue() == 0) && (Start != 1)){
            Delay(500);
            if(Start_GetValue() == 0){
                Start = 1;  //Start the Sequence
                Yellow_SetHigh();
                Pre_Charge_SetHigh();
                for(int i = 0;i<5;i++){
                    Delay(1000);
                }
                Main_SetHigh();
                Blue_SetHigh();
                Power_SetHigh();
            }
        }
        
        else if((Start_GetValue() == 0) && (Start != 0)){
            Delay(500);
            if(Start_GetValue() == 0){
                Start = 0;  //Start the Sequence
                Pre_Charge_SetLow();
                Main_SetLow();
                Blue_SetLow();
                for(int i = 0;i<5;i++){
                    Delay(1000);
                }
                Yellow_SetLow();
                Power_SetLow();
            }
        }
    }
}
/**
 End of File
 */