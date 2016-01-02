
/**
 *********************************************************************************************************
 *
 * @brief        DDS - This device reads in button presses and sets LEDS / bar graph
 * @file         main.c
 * @author       Richard Johnson - Mark K
 * @moduleID
 * @ingroup
 *
 *********************************************************************************************************
 * @note  The Firmware shall:
 *               -Read in button inputs (O1-O8)
 *               -Set LED status (LED1-LED6)
 *               -Set LED Bar Graph - http://www.adafruit.com/products/1721
 *               -Read RS485 BUS for data and reply with expectied data (set requested LED states and rely with button states)
 *********************************************************************************************************

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <stdlib.h>
#include "LED_BarGraph.h"
#include "IO.h"
#include "Communications.h"
void Delay(int wait);

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
    int ADCNT = 1;
    LEDbegin(0x70);
    LEDbegin(0x71);
    INDICATOR_SetHigh();

    LATCbits.LATC5 = 0;
    while (1) {
        updateComms();

        // ADCNT = ADC_GetConversion(Volume);
        // Add your application code
        //printf("ADC Volume = %d",ADCNT);

        if (time > 1) {
            LEDsetValue((throttle)*(24.0 / 100.0), LED_RED);
            LEDwriteDisplay(0x70);
            LEDsetValue((brake)*(24.0 / 100.0), LED_RED);
            LEDwriteDisplay(0x71);
            INDICATOR_Toggle();
            time = 0;
        }
        //        for (uint8_t b=0; b<24; b++) {
        //           LEDsetBar(b, LED_YELLOW);
        //           LEDwriteDisplay(0x70);
        //           LEDwriteDisplay(0x71);
        //           Delay(100);
        //           LEDsetBar(b, LED_OFF);
        //           LEDwriteDisplay(0x70);
        //           LEDwriteDisplay(0x71);
        //         }
        //          for (uint8_t b=0; b<24; b++) {
        //           LEDsetBar(b, LED_GREEN);
        //           LEDwriteDisplay(0x70);
        //           LEDwriteDisplay(0x71);
        //           Delay(100);
        //           LEDsetBar(b, LED_OFF);
        //           LEDwriteDisplay(0x70);
        //           LEDwriteDisplay(0x71);
        //         }

        //INDICATOR_Toggle();

        /*
        SetLEDOut(ADCNT++);
        if (ADCNT > 6){
            ADCNT = 0;
        }
         */
        //       if(GetButtonState(4) ==1)
        //       {
        //           Delay(500);
        //       }
    }
}

void Delay(int wait) {
    int x;
    for (x = 0; x < wait; x++) {
        __delay_ms(1);
    }
}
/**
 End of File
 */