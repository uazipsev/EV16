/*
 * File:   DigiPot.c
 * Author: Rick
 *
 * Created on May 20, 2015, 3:05 AM
 *
 * This controls the digital pot for the pump
 *
 * Data sheet: http://www.intersil.com/content/dam/Intersil/documents/x901/x9015.pdf
 */

#include "xc.h"
#include "MCC_Generated_Files/pin_manager.h"
#include "DigiPot.h"
#include "Functions.h"

int prev_pos = 0;

//This function is given a value to set the analog output

void PotSetpoint(int new_point) {
    int set_point;
    //bound the input to the fcn
    if (new_point > 32) {
        new_point = 32;
    }
    if (new_point <= 0) {
        new_point = 0;
    }

    int new_pos = new_point; //(new_point/100)*32;
    //I am bit banging the control to this

    //!CS this to select the device
    DIGI_CS_LAT = 0;

    //Tells the device if the clock moves output up or down
    if (new_pos > prev_pos) {
        //moving up
        DIGI_UP_DN_LAT = 1;
        set_point = new_pos - prev_pos;
    }
    if (new_pos < prev_pos) {
        //moving down
        DIGI_UP_DN_LAT = 0;
        set_point = prev_pos - new_pos;
    }
    Delay(1);

    int x;
    //clock to move it desired steps
    for (x = 0; x < set_point; x++) {
        DIGI_INC_LAT = 1;
        Delay(1);
        DIGI_INC_LAT = 0;
        Delay(1);
    }
    //We are done, let it go
    DIGI_CS_LAT = 1;
    prev_pos = new_pos;

}

//zeros output of device

void PotClear(void) {
    Delay(1);
    //!CS this Bitch
    DIGI_CS_LAT = 0;
    Delay(1);
    DIGI_UP_DN_LAT = 0;
    Delay(1);
    int x;
    for (x = 0; x < 32; x++) {
        DIGI_INC_LAT = 1;
        Delay(1);
        DIGI_INC_LAT = 0;
        Delay(1);
    }
    DIGI_INC_LAT = 1;
    Delay(1);
    //We are done, let it go
    DIGI_CS_LAT = 1;
    prev_pos = 0;
    Delay(1);
}