/*
 * File:   MotorController.c
 * Author: Rick
 *
 * Created on May 20, 2015, 3:05 AM
 *
 * This controls the IO for the motor controller
 * It uses the MCP4725 and IO to set modes of the device (ex FW / REV)
 *
 * Data sheet:
 */

#include "MotorControler.h"
#include <stdbool.h>
#include <stdlib.h>
#include "PinDef.h"
#include "Function.h"
#include "MCP4725.h"
#include <xc.h>
//#include "UART2.h" Not working HELP



void SetMotorDefaults() {
    DACRELAY = 0;
    SetDAC1(0);
    SetDAC2(0);   
}

void MotorEnable() {
    LATAbits.LATA0=1;
    BRAKE = 1;
    DC12ENABLE;
    Delay(100);
    IGNEN = 1;
    DACRELAY = 0;
}

void MotorDisable() {
    BRAKE = 0;
    Delay(100);
    DACRELAY = 0;
    DC12DISABLE;
}

//sets the direction of the motor and sets speed

void SetMotor(int speed, int direction) {
    //directionMismatchCheck(direction);
    SetDAC2(speed);
    DACRELAY = 1;
}

bool motorControllerValuesCheck(int t, int b) {
    //As long as the brake and gas are not both applied heavily
    if (b > 75 && t > 75) {
        return false;
    }
    return true;
}

void directionMismatchCheck(int direction) {
    static int past_direction = backward;
    if ((direction == forward) && (past_direction == backward)) {
        SetDAC2(0);
        Delay(10);
        REVERSE = 0;
        Delay(10);
        FORWARD = 1;
        past_direction = direction;
        
        //BRAKE =0;
    } else if ((direction == backward) && (past_direction == forward)) {
        SetDAC2(0);
        Delay(10);
        FORWARD = 0;
        Delay(100);
        //REVERSE = 1;
        past_direction = direction;
    }
}

//Set Regen amout ( to DAC)

void SetRegen(int amount) {
    static int lastRegen;
    if(amount != lastRegen){
    SetDAC1(amount);
    lastRegen=amount;
    }
}

// toggles regen

void Regen(bool enable) {
    if (enable == 1) {
        REGENEN = 1;
    } else
        REGENEN = 0;
}

/*  Reads the rs232 data. It gets 4 nibbles as ascii this function converts each paramter 
 *  into int's and store them into the structure to be used later.
 *  Still needs to work on implementation i have a rough idea below
    
 */

//Not sure how to read ascii HELP it could be for something else.

  //Converst value to to the right value depending on the type of value it is like temprature etc.




