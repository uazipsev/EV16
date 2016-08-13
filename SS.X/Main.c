
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

//#include <stdio.h>
//#include <stdlib.h>
#include "Communications.h"
#include "tmr0.h"
#include <xc.h>
#include "PinDef.h"
#include "Function.h"


void main(void) {
    Start();
    while (1) {
        updateComms();
        if(GetTime() > 1000){
            INDICATOR ^= 1;
            SetTime();
            ReadFaults();
        }
    }
}
/**
 End of File
 */