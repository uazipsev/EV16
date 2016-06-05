/* 
 * File:   Communications.h
 * Author: User
 *
 * Created on June 7, 2015, 5:50 PM
 */

#ifndef COMMUNICATIONS_H
#define	COMMUNICATIONS_H

#include <xc.h>
#include <stdbool.h>
#include "PinDef.h"
#include "ADDRESSING.h"

    void updateComms();
    void checkCommDirection();
    void respondECU();
    void CommStartup();


#endif	/* COMMUNICATIONS_H */

