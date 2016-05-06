/* 
 * File:   main.c
 * Author: Rick and Zac
 *
 * Created on May 11, 2015, 11:19 PM
 */

#include "main.h"
#include "Function.h"
#include <stdio.h>
#include "PinDef.h"

/*
 * 
 */

int main(int argc, char** argv) {
    //printf("InMainLoop");
    Setup();
    //printf("Start");

    while (1) { 
        //updateTimers();
//        if (time_get(ADCTM) > 50) {
//            static int counter = 0;
//            if (counter < 4){
//                //ADCReadings[counter]=readADC(counter++);
//            }
//            else counter = 0;
//            ADCTime = 0;
//        }
        //ledDebug();
        //updateComms();
        Delay(500);
        INDICATOR = !INDICATOR;
        printf("Start");
    }

    return (EXIT_SUCCESS);
}

