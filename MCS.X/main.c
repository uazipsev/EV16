/* 
 * File:   main.c
 * Author: Rick
 *
 * Created on May 11, 2015, 11:19 PM
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "PinDef.h"
#include "Communications.h"
#include "ADDRESSING.h"
#include "Function.h"
#include "MotorControler.h"
/*
 * 
 */



int main(int argc, char** argv) {
    
    Setup();
    MotorUpdate();
    Delay(100);
    MotorMode(GetMotorMode()+1);
    MotorUpdate();
    Delay(100);
    MotorMode(GetMotorMode()+1);
    MotorUpdate();
    Delay(100);
    while (1) {
        updateComms();
        ledDebug();
        MotorUpdate();
        //Delay(1000);
        
    }

    return (EXIT_SUCCESS);
}

