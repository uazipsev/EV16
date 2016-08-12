
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

#include <stdio.h>
#include <stdlib.h>
#include "Communications.h"
#include <xc.h>
#include "PinDef.h"

void Delay(int wait);

void main(void) {
    
    while (1) {
        updateComms();
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