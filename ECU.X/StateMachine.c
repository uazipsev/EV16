#include <stdbool.h>
#include <stdlib.h>
#include <xc.h>
#include "PinDef.h"
#include "StateMachine.h"
#include "debug.h"
#include "StoppedState.h"
#include "horn.h"
#include "SlaveAddressing.h"
#include "Communications.h"

int carActive = false;
//Each board has a condition that says which fault it is experiencing if any
int DDS_FAULT_CONDITION, MCS_FAULT_CONDITION, SAS_FAULT_CONDITION, BMM_FAULT_CONDITION, PDU_FAULT_CONDITION, ECU_FAULT_CONDITION;
//Control the debug state
extern enum debugStates debugState;
//Record and report fault conditions
struct faultStates faults;
//Record and control ECU states
enum ECUstates currentState = stopped;// TODO make back to start
//Control the power rails on the PDU
struct powerStates powerSet;
//Check to see if boot is completed
bool bootSequenceCompleted();
bool StartSequenceCompleted();

bool checkForBootupTimeout();
int faultChecker();
#define HARD_FAULT 1
#define SOFT_FAULT 2
#define THROTTLE_SANITY_CHECK 1
#define THROTTLE_BRAKE_CHECK  2

int getstate(void){

    return currentState;
 }

int getstatefault(void){
    
    return faultChecker();
}


void updateECUState() {
    static enum ECUstates previousState = NUM_STATES;
    switch (currentState) {
            //CAR IS NOT RUNNING AND CAN BE STARTED OR DEBUG
        case stopped:
            //Means this is your first time in this state
            if (previousState != currentState) {
                changeLEDState(DDS_IMD_INDICATOR, 0);
                changeLEDState(DDS_BMS_LED, 0);
                changeLEDState(DDS_ACTIVE_LED, 0);
                previousState = currentState;
                powerSet.DDS = true;
                powerSet.SAS = true;
                powerSet.BMM = false;  //TODO Change back to false
                powerSet.MCS = false;   //TODO Change back to false
                carActive = false;
                SS_RELAY = 0;
            }
            updateStoppedState();
            break;
            //CAR IS ATTEMPTING TO BOOT UP
        case booting:
            //Means this is your first time in this state
            if (previousState != currentState) {
                carActive = false;
                previousState = currentState;
                //Set the safety system to boot
                SS_RELAY = 1;
                //Turn on the BMM to watch precharge
                powerSet.BMM = true;
                //reset timeout timer
                BootTimer = 0;
            }
                        //if start button changes to depressed here, exit boot sequence
            if (seekButtonChange()) {
                if (!buttonArray[DDS_START_BUTTON]) {
                    changeLEDState(DDS_ACTIVE_LED, 0);
                    currentState--;
                }
            }
            

            //Wait for complete or for timeout
            if (StartSequenceCompleted()){
                currentState++;
            }
            else checkForBootupTimeout();

            break;
        case startup:
            //Means this is your first time in this state
            if (previousState != currentState) {
                carActive = true;
                previousState = currentState;
                //Power up the MCS
                changeLEDState(DDS_ACTIVE_LED, 1);
                powerSet.MCS = true;
                //reset timeout timer
                BootTimer = 0;
            }
            //if start button changes to depressed here, exit boot sequence
            if (seekButtonChange()) {
                if (!buttonArray[DDS_START_BUTTON]) {
                    changeLEDState(DDS_ACTIVE_LED, 0);
                    currentState = stopped;
                }
            }
            //Wait for complete or for timeout
            if (bootSequenceCompleted()){
                RTD(1500);
                carActive = true;
                currentState++;
            }
            else checkForBootupTimeout();
           
            break;
            //CAR IS RUNNING BREAK ON FAULTS OR ON BUTTON
        case running:
            //Means this is your first time in this state
            if (previousState != currentState) {
                previousState = currentState;
                carActive = true;
            }
            int fCheck = faultChecker();
            if (fCheck == HARD_FAULT) {
                currentState = fault;
            } else if (fCheck == SOFT_FAULT) {
                currentState = softFault;
            }


            if (seekButtonChange()) {
                if (!buttonArray[DDS_START_BUTTON]) {
                    changeLEDState(DDS_ACTIVE_LED, 0);
                    currentState++;
                }
            }
            break;
            //MAY BE UNNECCESSARY BUT THIS STATE ALLOWS CAR TO SHUT DOWN SOFTLY
        case stopping:
            //Means this is your first time in this state
            if (previousState != currentState) {
                previousState = currentState;
                changeLEDState(DDS_ACTIVE_LED, 0);
                powerSet.DDS = true;
                powerSet.SAS = true;
                powerSet.BMM = false;
                powerSet.MCS = false;
                carActive = false;
                SS_RELAY = 0;
            }
            if (BootTimer > 300) {
                currentState = stopped;
            }

            break;
            //RESUME OPERATION AFTER FAULT CLEARS
        case softFault:
            //Means this is your first time in this state
            if (previousState != currentState) {
                previousState = currentState;
                carActive = false;
            }



            //EXIT THE FAULT MODE BY PRESSING BUTTON
            switch (seekButtonChange()) {
                case DDS_START_BUTTON:
                    if (!buttonArray[DDS_START_BUTTON]) {
                        currentState = stopping;
                    }
                    break;
            }
            break;
            //HANDLE THE FAULTS THAT BROUGHT YOU HERE
        case fault:
            //Means this is your first time in this state
            if (previousState != currentState) {
                previousState = currentState;

                //Fault(4);
                changeLEDState(DDS_ACTIVE_LED, 0);
                powerSet.DDS = true;
                powerSet.SAS = true;
                powerSet.BMM = false;
                powerSet.MCS = false;
                carActive = false;
                SS_RELAY = 0;
            }

            debugState = FAULT_RECOVERY;

            //EXIT THE FAULT MODE BY PRESSING BUTTON
            switch (seekButtonChange()) {
                case DDS_START_BUTTON:
                    if (!buttonArray[DDS_START_BUTTON]) {
                        currentState = stopping;
                    }
                    break;
            }

            break;
        case override:
            //Means this is your first time in this state
            if (previousState != currentState) {
                previousState = currentState;
                changeLEDState(DDS_ACTIVE_LED, 1);
                carActive = true;
            }

            switch (seekButtonChange()) {
                case DDS_START_BUTTON:
                    if (!buttonArray[DDS_START_BUTTON]&&!buttonArray[DDS_DEBUG_BUTTON]) {
                        changeLEDState(DDS_ACTIVE_LED, 0);
                        currentState = stopping;
                    }
                    break;
            }
            break;
        case NUM_STATES:
            //Means this is your first time in this state
            if (previousState != currentState) {
                previousState = currentState;

            }
            break;

    }
}

int faultChecker() {
    if (MCS_FAULT_CONDITION || DDS_FAULT_CONDITION || PDU_FAULT_CONDITION || SAS_FAULT_CONDITION || BMM_FAULT_CONDITION || ECU_FAULT_CONDITION) {
        if (SAS_FAULT_CONDITION == THROTTLE_BRAKE_CHECK) {
            return SOFT_FAULT;
        } else if (SAS_FAULT_CONDITION == THROTTLE_SANITY_CHECK) {
            return SOFT_FAULT;
        }

        return true;
    } else
        return false;
}

bool StartSequenceCompleted() {
    if ((BootTimer > 3000)) return true; //&& PORTAbits.RA4 
    else return false;
}

bool bootSequenceCompleted() {
    if ((BootTimer > 1500) && ComCheck(MCSSTATE)) return true; 
    else return false;
}

bool checkForBootupTimeout() {
    if (BootTimer > 0 && BootTimer <= 5) {
        changeLEDState(DDS_ACTIVE_LED, 0);
    } else if (BootTimer > 250 && BootTimer <= 255) {
        changeLEDState(DDS_ACTIVE_LED, 1);
    } else if (BootTimer > 500 && BootTimer <= 505) {
        changeLEDState(DDS_ACTIVE_LED, 0);
    } else if (BootTimer > 750 && BootTimer <= 755) {
        changeLEDState(DDS_ACTIVE_LED, 1);
    } else if (BootTimer > 1000 && BootTimer <= 1005) {
        changeLEDState(DDS_ACTIVE_LED, 0);
    } else if (BootTimer > 1250 && BootTimer <= 1255) {
        changeLEDState(DDS_ACTIVE_LED, 1);
    } else if (BootTimer > 1500 && BootTimer <= 1505) {
        changeLEDState(DDS_ACTIVE_LED, 0);
    } else if (BootTimer > 1750 && BootTimer <= 1755) {
        changeLEDState(DDS_ACTIVE_LED, 1);
    } else if (BootTimer > 2000 && BootTimer <= 2005) {
        changeLEDState(DDS_ACTIVE_LED, 0);
    } else if (BootTimer > 2250 && BootTimer <= 2255) {
        changeLEDState(DDS_ACTIVE_LED, 1);
    } else if (BootTimer > 2500 && BootTimer <= 2505) {
        changeLEDState(DDS_ACTIVE_LED, 0);
    } else if (BootTimer > 2750 && BootTimer <= 2755) {
        changeLEDState(DDS_ACTIVE_LED, 1);
    }
    if (BootTimer > 3500) {
        currentState--;
        return true;
    }
    return false;

}