/* 
 * File:   SScomms.h
 * Author: Rick
 *
 * Created on August 14, 2016, 5:27 AM
 */

#ifndef SSCOMMS_H
#define	SSCOMMS_H

#include <stdbool.h>

#define ECU_FAULT 1
#define BOTS_FAULT 2
#define AMD_FAULT 3
#define STOP_L_FAULT 4
#define STOP_R_FAULT 5
#define STOP_C_FAULT 6
#define IMD_FAULT 7
#define BPD_FAULT 8
#define TSMS_FAULT 9
#define IS_FAULT 10
#define AUX_FAULT 11

bool requestSSData();
bool receiveCommSS();
int GetFaultChar(char val);
bool GetFaultBool(char val);
void ClearSSTalk();

#endif	/* SSCOMMS_H */

