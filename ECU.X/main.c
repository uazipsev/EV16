/* 
 * File:   main.c
 * Author: Rick
 *
 * Created on May 11, 2015, 11:19 PM
 */
#include "main.h"

int main(int argc, char** argv) {
    ReadReset();
    Setup(); //Setup the I/O system
    Delay(1000); // Wait for everything to get up and running
    Boot(100);    // Boot horn 
    while (1) {
        ledDebug(); //This runs off a timer and blinks status LED
        updateComms(); // Runs the COMS system 
        updateECUState(); // State MSN for CAR 
        updateBrakeLight(); // Runs Brake light!
        handleDebugRequests(); //This runs debug systems
        //Delay(10);
    }
    return (EXIT_SUCCESS);
}