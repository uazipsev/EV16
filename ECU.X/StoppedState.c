
#include "StoppedState.h"
#include "PinDef.h"
#include "debug.h"
#include "horn.h"

#define BMS_LED        5
#define ACTIVE_LED     3
#define IMD_INDICATOR  2
#define START_BUTTON   4
#define DEBUG_BUTTON   6

struct powerStates {
    bool DDS;
    bool MCS;
    bool SAS;
    bool BMM;
};
extern struct powerStates powerSet;

enum BMM {
    BATTERY_FAULT = 0,
    BATTERY_VOLTS = 1,
    BATTERY_TEMPS = 2,
    BATTERY_POWER = 3
};

struct commsStates {
    bool DDS;
    bool MCS;
    bool SAS;
    bool BMM;
    bool PDU;
    int DDS_SEND;
    int MCS_SEND;
    int SAS_SEND;
    enum BMM BMM_SEND;
    int PDU_SEND;
};
extern struct commsStates comms;

enum ECUstates {
    stopped = 0,
    booting = 1,
    running = 2,
    stopping = 3,
    fault = 4,
    override = 5,
    NUM_STATES = 6
};
extern enum ECUstates currentState;
extern enum debugStates debugState;
#define EGG 5
void doStuff();

void updateStoppedState() {
    //handleDebugRequests();
    //If start button is depressed, do start system request, show on LED
    switch (seekButtonChange()) {

        case DEBUG_BUTTON:
            switch (buttonArray[DEBUG_BUTTON]) {
                case 0:
                    doStuff();
                    if (debugState < NUM_DEBUG_STATES - 1) {
                        debugState++;
                    } else debugState = 0;
                    switch (debugState) {
                        case NO_DEBUG:
                            comms.BMM_SEND = BATTERY_FAULT;
                            break;
                        case THROTTLE_BRAKE:
                            break;
                        case BATTERY_DEBUG_VOLTS:
                            comms.BMM_SEND = BATTERY_VOLTS;
                            break;
                        case BATTERY_DEBUG_TEMPS:
                            comms.BMM_SEND = BATTERY_TEMPS;
                            break;
                        case BATTERY_DEBUG_POWER:
                            comms.BMM_SEND = BATTERY_POWER;
                            break;
                        case FAULT_RECOVERY:
                            break;
                        case NUM_DEBUG_STATES:
                            break;
                    }
                    break;
                case 1:

                    break;
            }

            break;
        case START_BUTTON:
            if (!buttonArray[START_BUTTON]) {
                changeLEDState(ACTIVE_LED, !buttonArray[START_BUTTON]);
                currentState++;
            }
            doStuff();
            break;
    }
}

void doStuff() {
    static int Easter = 0;
    if (!buttonArray[DEBUG_BUTTON] && buttonArray[START_BUTTON]) {
        Easter = 0;
    } else {
        //check if the start button is also held
        if (easterEggs()) {
            //this is the first time
            if (!Easter)
                Easter++;
                //has been a few?
            else if (Easter < 8) {
                Easter++;
            } else {
                //Power up the MCS
                powerSet.MCS = true;
                //Set the safety system to boot
                SS_RELAY = 1;
                //Set the current state to running
                currentState = override;
            }
            //Start button not held
        } else {
            Easter = 0;
        }
    }

}
//Just for debugging and so on

bool easterEggs() {
    if (!buttonArray[DEBUG_BUTTON]) {
        if (!buttonArray[START_BUTTON]) {
            return true;
        }
    }
    return false;

}