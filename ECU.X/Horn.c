#include "horn.h"
#include "pwm.h"
#include "PinDef.h"
#include "Function.h"
#include <xc.h>

// This fcn runs the Ready to Drive sound for competiton rules.

void RTD(int lenth) {
    //Start horn
    HORN_EN = 1; // Starting Horn
    PWMupdate(80);
    int x = 0;
    for (; x < lenth; x++) {
        PERupdate(0x04F0);
        Delay(1);
        PERupdate(0x04E9);
        //Delay(250);
    }
    HORN_EN = 0;
    //end horn
}

// This fcn runs the boot sound so I know when the car starts.

void Boot(int lenth) {
    //Start horn
    HORN_EN = 1; // Starting Horn
    Delay(lenth);
    HORN_EN = 0;
    //end horn
}

// This fcn runs a fault sound so I know when it happens.

void Fault(int lenth) {
    //Start horn
    HORN_EN = 1; // Starting Horn
    PWMupdate(80);
    int x = 0;
    for (; x < lenth; x++) {
        PERupdate(0x0400);
        Delay(1);
        //PERupdate(0x04E9);
        //Delay(250);
    }
    HORN_EN = 0;
    //end horn
}