/* 
 * File:   main.c
 * Author: Rick
 *
 * Created on May 11, 2015, 11:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "xc.h"
#include "PinDef.h"
#include "ADDRESSING.h"
#include "main.h"
#include "StateMachine.h"
#include "horn.h"

int main(int argc, char** argv) {
    Setup();
    Delay(1000);
    //Boot(100);
    while (1) {
        ledDebug();
        updateComms();
        updateECUState();
        updateBrakeLight();
    }
    return (EXIT_SUCCESS);
}

void updateBrakeLight() {
    if (brake > 10) {
        BRAKELT = 1;
    } else BRAKELT = 0;
}