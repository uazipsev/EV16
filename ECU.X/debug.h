/*******************************************************************
 * @brief           DriverConfig.c
 * @brief           
 * @return          N/A
 * @note            assembles bytes together to make a valid data packet 
 *******************************************************************/

#ifndef DEBUG_H
#define	DEBUG_H

#include <xc.h>
#include <stdbool.h>
#include "DriverConfigs.h"

enum debugStates {
    NO_DEBUG = 0,
    THROTTLE = 1,
    BRAKE = 2,
    BATTERY_DEBUG_VOLTS = 3,
    BATTERY_DEBUG_TEMPS = 4,
    BATTERY_DEBUG_POWER = 5,
    FAULT_RECOVERY = 6,
    NUM_DEBUG_STATES = 7,
            FIND_STATE =8,
            FAULT =9,
            Reset=10,
            comm_on=11,
            buttons = 12,
            error_rate = 13
};

void handleDebugRequests();
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
void MenuClearFlag();

#endif	/* DEBUG_H */

