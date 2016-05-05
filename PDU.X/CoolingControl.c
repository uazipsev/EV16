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
#include "mcc_generated_files/pwm4.h"

//The system needs to be started to minimum values.

void CoolingStart() {
    PotSetpoint(pumpStart);
    PWM4_LoadDutyValue(fanStart);
}

void CoolingUpdate(void) {

}
