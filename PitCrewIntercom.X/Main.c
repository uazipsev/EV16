/*
 * File:   Main.c
 * Author: Rick
 *
 * Created on August 3, 2016, 10:52 AM
 */


#include "xc.h"
#include "Function.H"
#include "Radio.h"

int main(void) {
    Start();
    RadioBegin();
    LEDOff();
    while(1){
        RadioOperation();
        Delay(100);
    }
    return 0;
}
