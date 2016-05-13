

#include "mcc_generated_files/mcc.h"
#include "functions.h"
#include "Communications.h"
#include "NokiaLCD.h"

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
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    NokiaStart();  // We are setting ut the display for text. We dont have a GFX lib installed for program size limits :(
    Delay(100);    
    clearLcd();    //found out the display needs cleard after a little bit to keep it clear. So I added a little delay to give the LCD a break 
    respondECU();  //This is unique to this board, we are "faking" the ECU here to get the BMM into a master mode talking to us, controling this board. 
    //LED_SetDigitalOutput(); //Maybe not needed? I don't know why this was added, This is for the status LED on the board. 
    LED_SetHigh();  //We are getting the LED on for toggle control, I hope.
    while(1){
        respondECU();
        updateComms();
        ledDebug();
    }
}
/**
 End of File
 */