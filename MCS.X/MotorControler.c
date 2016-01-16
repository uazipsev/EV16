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
#include "PinDef.h"
#include "Function.h"
#include "MCP4725.h"
#include <xc.h>
//#include "UART2.h" Not working HELP


struct RMS_Parameters CarParameters;


void SetMotorDefaults() {
    SetDAC1(0);
    SetDAC2(0);
}

void MotorEnable() {
    LATAbits.LATA0=1;
    //BRAKE =1;
    DC12ENABLE;
    FORWARD=1;
    REVERSE=0;
}

void MotorDisable() {
    //DC12DISABLE;
    //BRAKE =0;
}

//sets the direction of the motor and sets speed

void SetMotor(int speed, int direction) {
    //directionMismatchCheck(direction);
    SetDAC2(speed);
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
        //Delay(100);
        REVERSE = 0;
        //Delay(100);
        FORWARD = 1;
        past_direction = direction;
        
        //BRAKE =0;
    } else if ((direction == backward) && (past_direction == forward)) {
        SetDAC2(0);
        Delay(100);
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
void Read_rs232(struct RMS_Parameters *car){
    int count_of_Param=0;
    int paramter_total;  // Total of the parameter 
      int bitplace=0;   //A marker to keep track at which bit it is.
    while (count_of_Param<20){
    /* Not sure how to read from UArt from this class. HELP
     * Going to put psudeo code.
     int ascii_value[3];
     * 
    
     * 
     * 
     * if (ascii value is a space){
     * 
     * paramter_total=ascii_value[0]
     * 
     * paramter_total= paramter_tota+ascii_value[1]*16
     * 
     *  paramter_total= paramter_tota+ascii_value[2]*256
     * 
     *  paramter_total= paramter_tota+ascii_value[3]*4096
     * car.carsearch(count_of_Param)=paramter_total             // need to make function will be a case statement dictating what varible needs to be updated. 
     * 
     * count_of_Param=count_of_Param+1;                         // Update count and repeat
     * paramter_total=0                                         //Clear total and bitplace
     * bitplace=0
     * 
     *  for (int bit=0, bit<4, bit++){
     *      ascii_value[bitplace]=0;                                 //Clear bit values
     *      }
     * }
     * 
     * else{ 
     *      //read 4 bits (which are in ascii) through uart
     *      for (int bit=0, bit<4, bit++){
     *      ascii_value[bitplace]=ascii_value+getuart*2^bit;
     *      }
         bitplace=bitplace+1;
     *      }
     
     */ 
        ;
    }
  
  ;
  }
  //Converst value to to the right value depending on the type of value it is like temprature etc.

void Convert_rs232(struct RMS_Parameters *car){
  
  
  ;
  }

//Gets the actual value you want from rs232
int Get_rs232(struct RMS_Parameters *car, int values){
  // Return the value it requests
  // return car.carsearch(values);
  ;
  }

// Turns on data and analize input
//needs work

void GetMCData(int values) {
    Read_rs232(&CarParameters);
    Convert_rs232(&CarParameters);
    Get_rs232( &CarParameters,values);
}
