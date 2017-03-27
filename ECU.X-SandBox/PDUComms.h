/* 
 * File:   PDUComms.h
 * Author: User
 *
 * Created on June 7, 2015, 7:35 PM
 */

#ifndef PDUCOMMS_H
#define	PDUCOMMS_H

#include "ADDRESSING.h"
#include <stdbool.h>

bool requestPDUData();
bool receiveCommPDU();
bool powerChange();
int constructPowerSet();
void ClearPDUTalk();

#endif	/* PDUCOMMS_H */

