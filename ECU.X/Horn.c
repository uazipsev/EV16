#include "horn.h"
#include "pwm.h"
#include "PinDef.h"
#include <xc.h>

void RTD(int lenth) {
    //Start horn
    HORN_EN = 1; // Starting Horn
    PWMupdate(80);
    int x = 0;
    for (; x < lenth; x++) {
        PERupdate(0x04F0);
        Delay(1);
        //PERupdate(0x04E9);
        //Delay(250);
    }
    HORN_EN = 0;
    //end horn
}