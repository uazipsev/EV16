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
#include "ADDRESSING.h"
#include "StateMachine.h"
#include "Functions.h"
#include "horn.h"
#include "debug.h"
#include "PinDef.h"
#include "ThrottleBrakeControl.h"

int main(int argc, char** argv) {
    ReadReset();
    Setup(); //Setup the I/O system
    Delay(1000); // Wait for everything to get up and running
    Boot(100);    // Boot horn 
    INDICATOR = 1;
    while (1) {
        ledDebug(); //This runs off a timer and blinks status LED
        updateComms(); // Runs the COMS system 
        updateECUState(); // State MSN for CAR 
        updateBrakeLight(); // Runs Brake light!
        handleDebugRequests(); //This runs debug systems
        DeltaThrottle();
        //Delay(10);
    }
    return (EXIT_SUCCESS);
}