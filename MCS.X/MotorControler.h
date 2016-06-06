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

enum MotorControlState{
    turnon = 1,
    startup = 2,
    wait = 3,
    set = 4,
    run = 5,
    stoping = 6
};

#define forward     1
#define backward    2
#define stop        3

void MotorUpdate();

void RegenEn(bool enable);
void SetDirection(int dir);

void SetSpeed(int value);
void SetRegen(int value);

void MotorMode(int value);
int GetMotorMode();


#endif	/* MOTORCONTROLER_H */

