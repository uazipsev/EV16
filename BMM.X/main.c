/* 
 * File:   main.c
 * Author: Rick and Zac
 *
 * Created on May 11, 2015, 11:19 PM
 */

#include "main.h"
#include "SlaveAddressing.h"

extern void updateTimers();
extern volatile unsigned long int ADCTime;
int ADCReadings[4];

/*
 * 
 */

int main(int argc, char** argv) {
    Setup();

    while (1) {
        updateTimers();
        if (ADCTime > 50) {
            static int counter = 0;
            if (counter < 4){
                //ADCReadings[counter]=readADC(counter++);
            }
            else counter = 0;
            ADCTime = 0;
        }
        //ledDebug();
        updateComms();
    }

    return (EXIT_SUCCESS);
}

