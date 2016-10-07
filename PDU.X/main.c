#include "mcc_generated_files/mcc.h"
#include "Functions.h"
#include "PDU.h"
#include "Communications.h"
#include "CoolingControl.h"
#include "DigiPot.h"
#include "Shift595.h"
/*
                         Main application
 */
void main(void) {
    // Initialize the device
    SYSTEM_Initialize();
    PDUStartup();
    //
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
//    DATAEE_WriteByte(0, 0x03);
//    DATAEE_WriteByte(1, 0xE8);
//    DATAEE_WriteByte(2, 0x03);
//    DATAEE_WriteByte(3, 0xE8);
//    DATAEE_WriteByte(4, 0x03);
//    DATAEE_WriteByte(5, 0xE8);
//    DATAEE_WriteByte(6, 0x03);
//    DATAEE_WriteByte(7, 0xE8);
//    DATAEE_WriteByte(8, 0x03);
//    DATAEE_WriteByte(9, 0xE8);
//    DATAEE_WriteByte(10, 0x03);
//    DATAEE_WriteByte(11, 0xE8);
            
    PotSetpoint(0);
    PWM4_LoadDutyValue(0);
    LATCbits.LATC5 = 0;
    LED1_SetHigh();
    LED2_SetHigh();
    int i = 0;
    bool UP = 0;
    ComputeStorageData();
    
    int j = 1;
    while (1) {
        updateComms();
        if(CoolingCheck() && UP == 0){
            UP = 1;
            CoolingStart();
        }
        if(!CoolingCheck() && UP == 1){
            UP = 0;
            CoolingStop();
        }
        i++;
        PWM4_LoadDutyValue(i);
        if(i>500){
            i = 0;

        }
    }
}
/**
 End of File
 */