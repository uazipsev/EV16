/* 
 * File:   Timers.h
 * Author: User
 *
 * Created on June 3, 2015, 8:03 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <xc.h>
#include "PinDef.h"

    void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void);
    void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);

    void initTimerTwo(void);
    void initTimerOne(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TIMERS_H */

