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

enum debugStates {
    NO_DEBUG = 0,
    TEMPSBAM1 = 1,
    TEMPSBAM2 = 2,
    TEMPSBAM3 = 3,
    TEMPSBBM1 = 4,
    TEMPSBBM2 = 5,
    TEMPSBBM3 = 6,
    VOLTSBAM1 = 7,
    VOLTSBAM2 = 8,
    VOLTSBAM3 = 9,
    VOLTSBBM1 = 10,
    VOLTSBBM2 = 11,
    VOLTSBBM3 = 12,
    CURRENT_PV = 13,
    FAULT = 14,
    ERRORRATE = 15,
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

