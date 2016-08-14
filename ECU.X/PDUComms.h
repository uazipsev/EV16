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

    extern void RS485_Direction2(int T_L);
    bool requestPDUData();
    bool receiveCommPDU();

#endif	/* PDUCOMMS_H */

