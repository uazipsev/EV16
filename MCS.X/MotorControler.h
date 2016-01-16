/* 
 * File:   MotorControler.h
 * Author: Rick
 *
 * Created on May 12, 2015, 1:09 AM
 */

#ifndef MOTORCONTROLER_H
#define	MOTORCONTROLER_H

#include <stdbool.h>

typedef enum Directionality {
    forward = 1,
    backward = 2,
    stop = 3
} dirr;

#define forward     1
#define backward    2
#define stop        3

void SetMotor(int speed, int direction);
void SetMotorDefaults();
void MotorEnable();
void MotorDisable();
void SetRegen(int amount);
void Regen(bool enable);
bool motorControllerValuesCheck(int t, int b);
void directionMismatchCheck(int direction);



// Structure to get parameters from the rms

struct RMS_Parameters {
    int Slow_Interrupt_Counter;             //Not Sure
    int Filtered_Accel_pot ;                //Not Sure
    int Blended_Torque;                     //Torque
    int Vehicle_Torque_Command ;            //Torque
    int DC_Voltage ;                        //Voltage not sure if high or low assuming high
    int DC_Current ;                        // Current
    int Omega_Tach;                         //Not Sure
    int Flux_Weakening_Regulator_Output;    //Flux
    int FB_Voltage_Magnitude;               //Voltage not sure if high or low assuming low
    int IQ_Command;                         //Not Sure 
    int IQ_Feedback;                        // Not Sure perhaps gain?
    int ID_Command;                         //Not Sure
    int ID_Feedback;                        //Not Sure
    int Modulation;                         //Not Sure
    int Module_A_Temperature;               //Temperature
    int Motor_Temperature;                  //Temperature
    int Run_Fault_Low_Word;                 //Not Sure  
    int Run_Fault_High_Word;                //Not Sure
    int Torque_Shudder;                     //Torque
    int Filtered_Brake_pot;                  //Not Sure
    
    
};
//Functions to read convert the structure 
void Read_rs232( struct RMS_Parameters *car);
 void Convert_rs232(struct RMS_Parameters *car);
   int  Get_rs232(struct RMS_Parameters *car, int Value);

#endif	/* MOTORCONTROLER_H */

