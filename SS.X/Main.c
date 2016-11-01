
/**
 *********************************************************************************************************
 *
 * @brief        SS - This device reads in safety device statuses 
 * @file         main.c
 * @author       Richard Johnson
 * @moduleID
 * @ingroup
 *
 *********************************************************************************************************
 * @note  The Firmware shall:
 *               -Read in button inputs (Safety switches)
 *               -Read RS485 BUS for data and reply with expected data (relay with safety states)
 *********************************************************************************************************/
#include "Communications.h"
#include "tmr0.h"
#include <xc.h>
#include "PinDef.h"
#include "Function.h"


void main(void) {
    Start(); //Set up pic for application use
    RS485_TSS_Direction = LISTEN;  ///RS485 set to listen
    while (1) {
        updateComms(); //Read UART ring buffer and look if packet is here for us!
        if(BPD_FAULT == 1){  //read ticker and if it greater than one second
           INDICATOR = 1;    //blink LED
           ReadFaults();      //Read ports and load data into bytes
           SetTime();         // Clear timer
        }
        else{
           INDICATOR = 0;
        }
    }
}
/**
 End of File
 */