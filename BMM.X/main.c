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
extern int readADC(int inputNum);
int ADCReadings[4];
extern int BVolts[NUMSLAVES][BATTPERSLAVE];
extern int BTemps[NUMSLAVES][TEMPPERSLAVE];

/*
 * 
 */

int main(int argc, char** argv) {
    Setup();
    int l = 0, j = 0;
    for (l = 0; l < NUMSLAVES; l++) {
        for (j = 0; j < BATTPERSLAVE; j++) {
            BVolts[l][j] = 100;
        }
        for (j = 0; j < TEMPPERSLAVE; j++) {
            BTemps[l][j] = 70;
        }
    }
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

