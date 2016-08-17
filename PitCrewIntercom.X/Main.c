/**
 *********************************************************************************************************
 *
 * @brief        PitCrewIntercom - This device reads in button presses and controls modem, with a touch of battery monitoring
 * @file         main.c
 * @author       Richard Johnson
 *
 *********************************************************************************************************
 * @note  The Firmware shall:
 *               -Read in button inputs PTT
 *               -Set LED status (RGB)
 *               -Set up and runs modem
 *               -Read battery voltage and charger status
 *********************************************************************************************************/

#include "xc.h"
#include "Function.H"
#include "Radio.h"
#include "Timer.h"
#include "PinDef.h"
#include <stdio.h>

int main(void) {

    Start();    //Start up processor, I/O, ADC, UART, OSS
    LEDOff();       //turn LEDs off
    RadioBegin();   //Start radio
    //TMR2_StartTimer();  //Start timer for inactivity 
    while(1){
        RadioOperation();  //run state mashen 
        Delay(100);        //Wait 100ms
    }
    return 0;
}
