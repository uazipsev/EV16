/* 
 * File:   MCSComms.h
 * Author: User
 *
 * Created on June 7, 2015, 7:35 PM
 */

#ifndef MCSCOMMS_H
#define	MCSCOMMS_H

#include "ADDRESSING.h"
#include <stdbool.h>
    
bool requestMCSData();
bool receiveCommMCS();
char GetMCSFault();
void ClearMCSTalk();

#endif	/* MCSCOMMS_H */

