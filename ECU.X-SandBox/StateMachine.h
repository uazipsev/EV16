/* 
 * File:   StateMachine.h
 * Author: User
 *
 * Created on June 9, 2015, 5:45 PM
 */

#ifndef STATEMACHINE_H
#define	STATEMACHINE_H

#ifdef	__cplusplus
extern "C" {
#endif

void updateECUState();

struct powerStates {
    bool DDS;
    bool MCS;
    bool SAS;
    bool BMM;
};

struct faultStates {
    int DDS;
    int MCS;
    int SAS;
    int BMM;
    int PDU;
    int SS;
};
enum ECUstates {
    stopped = 0,
    booting = 1,
    startup = 2,
    running = 3,
    stopping = 4,
    softFault=5,
    fault = 6,
    override = 7,
    NUM_STATES = 8
};

#ifdef	__cplusplus
}
#endif

#endif	/* STATEMACHINE_H */

