/* 
 * File:   debug.h
 * Author: User
 *
 * Created on June 8, 2015, 7:10 PM
 */

#ifndef DEBUG_H
#define	DEBUG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdbool.h>

enum debugStates {
    NO_DEBUG = 0,
    THROTTLE_BRAKE = 1,
    BATTERY_DEBUG_VOLTS = 2,
    BATTERY_DEBUG_TEMPS = 3,
    BATTERY_DEBUG_POWER = 4,
    FAULT_RECOVERY = 5,
    NUM_DEBUG_STATES = 10,
            Find_State =6,
            State_fault=7,
            Reset=8,
            comm_on=9
};

    extern unsigned int throttle1, throttle2, brake;
    extern void handleDebugRequests();
    extern volatile unsigned int DebugTimer;
    extern void Send_put2(unsigned char _data);
    extern void sendData2(unsigned char whereToSend);
    extern bool receiveData2();
    extern void ToSend2(const unsigned char where, const unsigned int what);
extern int getstate();
extern int getstatefault();


#ifdef	__cplusplus
}
#endif

#endif	/* DEBUG_H */

