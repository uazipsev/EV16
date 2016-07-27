/* 
 * File:   debug.h
 * Author: User
 *
 * Created on June 8, 2015, 7:10 PM
 */

#ifndef DEBUG_H
#define	DEBUG_H

#include <xc.h>
#include <stdbool.h>
#include "DriverConfigs.h"
    
extern int buttonArray[8];

enum debugStates {
    NO_DEBUG = 0,
    THROTTLE_BRAKE = 1,
    BATTERY_DEBUG_VOLTS = 2,
    BATTERY_DEBUG_TEMPS = 3,
    BATTERY_DEBUG_POWER = 4,
    FAULT_RECOVERY = 5,
    NUM_DEBUG_STATES = 11,
            Find_State =6,
            State_fault=7,
            Reset=8,
            comm_on=9,
            buttons = 10
};

    extern unsigned int throttle1, throttle2, brake;
void handleDebugRequests();
//    extern void Send_put2(unsigned char _data);
//    extern void sendData2(unsigned char whereToSend);
//    extern bool receiveData2();
//    extern void ToSend2(const unsigned char where, const unsigned int what);
extern int getstate();
extern int getstatefault();
void ThrottleMenu(char menuitem);
void BrakeMenu(char menuitem);
void SettingMenu(char menuitem);
void BatteryMenu(char menuitem);
void ComMenu(char menuitem);
void DriverMenu(char menuitem);
void SelectDriver();
void ClearScreen();
void MenuBrakeLightValue(char cont);

void MenuPrint(char Menuloc, char Subloc);
void MenuClear();

#endif	/* DEBUG_H */

