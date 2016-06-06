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

int MotorState, spd, brk = 0;
char dir = 0;

void MotorUpdate(){
    switch(MotorState){
        case turnon:
            DACRELAY = 0;
            SetDAC1(0);
            SetDAC2(0);   
            BRAKE = 1;
            DC12ENABLE;
            break;
        case startup:
            IGNEN = 1;
            break;
        case wait:
            DACRELAY = 0;
            break;
        case set:
            if(dir == forward){
                REVERSE = 0;
                FORWARD = 1;
            }
            if(dir == backward){
                FORWARD = 0;
                REVERSE = 1; 
            }
            DACRELAY = 1;
            break;
        case run:
            SetDAC1(spd*40.9);
            SetDAC2(brk*40.9);
            break;
        case stoping:
            BRAKE = 0;
            DACRELAY = 0;
            DC12DISABLE;
            SetDAC1(0);
            SetDAC2(0);
            break;
    }
}

void MotorMode(int value){
    MotorState = value;
}

int GetMotorMode(){
   return MotorState;
}

void SetDirection(int direction){
    dir = direction;
}

void SetSpeed(int value){
    spd = value;
}

void SetRegen(int value){
    brk = value;
}
// toggles regen

void RegenEn(bool enable) {
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




