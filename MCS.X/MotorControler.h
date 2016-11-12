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

enum MotorStates {
    MCTURNON = 1,
    MCSTARTUP = 2,
    MCWAIT = 3,
    MCSET = 4,
    MCRUN = 5,
    MCSTOP = 6,
};

#define forward     1
#define backward    2
#define stop        3

void MotorMode(int value);
int GetMotorMode();
void SetDirection(char direction);
void SetSpeed(int value);
void SetRegen(int value);
void SetCarMode(bool value);
void RegenEn(bool enable);
void MotorUpdate();



#endif	/* MOTORCONTROLER_H */

