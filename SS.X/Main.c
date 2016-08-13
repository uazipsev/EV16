
/**
 *********************************************************************************************************
 *
 * @brief        SS - This device reads in safety device statuses 
 * @file         main.c
 * @author       Richard Johnson - Mark K
 * @moduleID
 * @ingroup
 *
 *********************************************************************************************************
 * @note  The Firmware shall:
 *               -Read in button inputs (Safty switches)
 *               -Read RS485 BUS for data and reply with expectied data (rely with safty states)
 *********************************************************************************************************/
#include "Communications.h"
#include "tmr0.h"
#include <xc.h>
#include "PinDef.h"
#include "Function.h"


void main(void) {
    Start(); //Set up pic for application use
    while (1) {
        updateComms(); //Read UART ring buffer and look if packet is here for us!
        if(GetTime() > 1000){  //read ticker and if it greater than one second
            INDICATOR ^= 1;    //blink LED
            SetTime();         // Clear timer 
            ReadFaults();      //Read ports and load data into bytes
        }
    }
}
/**
 End of File
 */