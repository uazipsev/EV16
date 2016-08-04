/*
 * File:   Main.c
 * Author: Rick
 *
 * Created on August 3, 2016, 10:52 AM
 */


#include "xc.h"
#include "Function.H"
#include "Radio.h"
#include "SR_FRS.h"

int main(void) {
    Start();
    SR_FRSStart();
    while(1){
        RadioOperation();
    }
    return 0;
}
