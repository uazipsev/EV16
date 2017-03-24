/* 
 * File:   main.c
 * Author: Rick and Zac
 *
 * Created on May 11, 2015, 11:19 PM
 */

#include "Function.h"
#include <stdio.h>
#include "PinDef.h"
#include "Communications.h"
#include "BatteryManagment.h"
#include "Timers.h"
#include <stdbool.h>
#include <stdlib.h>
#include <xc.h>
#include "ADDRESSING.h"
#include "debug.h"

int main(int argc, char** argv) {
    int mode=1;  //mode=1=Run car  mode=2=Charge Car
    bool BMM_Setup=true;
    Setup();
   printf("Start");
   Start_BMS(mode);
   while (1) { 
        
       
      // printf("\n-----Temp Bank A Mod 1----\n");
       updateTimers();
//        if (time_get(ADCTM) > 50) {
//            static int counter = 0;
//            if (counter < 4){
//                //ADCReadings[counter]=readADC(counter++);
//            }
//            else counter = 0;
//            ADCTime = 0;
//        }
       //ledDebug();
        Run_Mode(BMM_Setup); //Start run mode with setup.
        BMM_Setup=false;
        if (mode == 1) {
            //Run_Mode(BMM_Setup); //Start run mode with setup.
            //BMM_Setup=false;
        } else if (mode == 2) {
            Charge_Mode();
        }
       
       
       
       handleDebugRequests();
       updateComms();
    }

    return (EXIT_SUCCESS);
}

