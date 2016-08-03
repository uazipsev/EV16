

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
    ANSELC = 0;
    ANSELA = 0;
    TRISCbits.TRISC0=0;
    TRISCbits.TRISC1=0;
    TRISCbits.TRISC2=0;
    TRISAbits.TRISA6=0;
    TRISAbits.TRISA7=0;
    TRISBbits.TRISB3=0;
    TRISBbits.TRISB4=0;
    TRISBbits.TRISB5=0;
    TRISDbits.TRISD4 = 0;
    
    LATBbits.LATB3=0;
    LATBbits.LATB5=0;
    LATBbits.LATB4=0;
    
   // HORN_SetDigitalOutput();
    
//    LATCbits.LATC1=1;
//    LATCbits.LATC2=0; //IMD read
//    LATAbits.LATA6=1;
 //   LATCbits.LATC0=1;
    GREEN_SetHigh();
    //BLUE_SetHigh();
    
    //Horn(50);
    
    LED_SetDigitalMode();
    
    
    //NokiaStart();  // We are setting ut the display for text. We dont have a GFX lib installed for program size limits :(
    //Delay(100);    
    
    //clearLcd();    //found out the display needs cleard after a little bit to keep it clear. So I added a little delay to give the LCD a break 
    //Splash();      //Sets display with data about the device
    
    while(SetBMM()); //This is unique to this board, we are "faking" the ECU here to get the BMM into a master mode talking to us, controling this board. 

    while(1){
        updateTimers();
        ledDebug();
    }
}
/**
 End of File
 */