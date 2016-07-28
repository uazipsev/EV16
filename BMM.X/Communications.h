/* 
 * File:   Communications.h
 * Author: User
 *
 * Created on June 3, 2015, 9:14 PM
 */

#ifndef COMMUNICATIONS_H
#define	COMMUNICATIONS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <xc.h>
#include "ADDRESSING.h"
   

#define RS485_Port LATBbits.LATB7
#define TALK 1
#define LISTEN 0

    void updateComms();
    void checkCommDirection();
    void CommStart();
    
#endif	/* COMMUNICATIONS_H */

