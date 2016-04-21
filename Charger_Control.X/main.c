

#include "mcc_generated_files/mcc.h"
#include "Functions.h"
#include "Communications.h"
#include "Nokia3310.h"

/*
                         Main application
 */

int Start = 0;
char i;
char ddata[11];

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
        Delay(1000);
        clearLcd();
        ddata[0]='T';
        ddata[1]='E';
        ddata[2]='S';
        ddata[3]='T';
        ddata[4]=' ';
        ddata[5]='L';
        ddata[6]='C';
        ddata[7]='D';
        ddata[8]=' ';
        ddata[9]=i;
        i++;
        gotoXy(2,2);
        lcdStr(ddata,10);
    }
    updateComms();
}
/**
 End of File
 */