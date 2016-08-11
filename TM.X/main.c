/* 
 * File:   main.c
 * Author: Rick
 *
 * Created on May 11, 2015, 11:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>
#include "PinDef.h"
#include "Functions.h"
#include "Communications.h"


int main(int argc, char** argv) {
    Setup();
    //Delay(1000);
    while (1) {
        ledDebug();
        updateComms();
    }
    return (EXIT_SUCCESS);
}

