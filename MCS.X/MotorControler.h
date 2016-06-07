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

void MotorUpdate();



#endif	/* MOTORCONTROLER_H */

