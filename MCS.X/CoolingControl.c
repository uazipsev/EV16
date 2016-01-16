/*
 * File:   CoolingControl.c
 * Author: Rick
 *
 * Created on May 20, 2015, 3:05 AM
 *
 * This controls PID cooling for motor and motor controller
 * The fan is controlled by PWM with high side mosfet driver
 * The pump is controlled by the digital pot - this signal is sent to the pump driver
 *
 */

#include "CoolingControl.h"
#include "DigiPot.h"
#include "pwm.h"

//The system needs to be started to minimum values.

void CoolingStart() {
    PotSetpoint(pumpStart);
    PWMupdate(fanStart);
}

void CoolingUpdate(void) {

}
