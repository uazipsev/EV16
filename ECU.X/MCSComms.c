#include "MCSComms.h"
#include "PinDef.h"
#include "Timers.h"


bool requestMCSData();
bool receiveCommMCS();
bool readyToSendMCS = true;
bool MCS_COMMS_ERROR = false;
extern int carActive;

bool requestMCSData() {
    if (((GetTime(MCSTIMER) > BOARD_RESEND_MIN+100) && (readyToSendMCS)) || (GetTime(MCSTIMER) > BOARD_TIMEOUT)) {
        static int MCSErrorCounter = 0;
        //INDICATOR ^= 1;
        RS485_Direction2(TALK);
        if (!readyToSendMCS) {
            MCSErrorCounter++;
            if (MCSErrorCounter > 1) {
                MCSErrorCounter = 0;
                return false;
            }
        } else {
            readyToSendMCS = false;
            MCSErrorCounter = 0;
        }
        
        ToSend(RESPONSE_ADDRESS, ECU_ADDRESS);
        ToSend(OUTPUT_ACTIVE, carActive);
        ToSend(THROTTLE_OUTPUT, throttle1 );//TODO may need to add 40.95 if mcs gets rid of theres
        ToSend(BRAKE_OUTPUT, brake); //TODO may need to add 40.95 if mcs gets rid of theres
        sendData(MCS_ADDRESS);
        SetTime(MCSTIMER);
    }
    return true;
}

bool receiveCommMCS() {
    if (receiveData()) {
        if (receiveArray[RESPONSE_ADDRESS] == MCS_ADDRESS) {
            readyToSendMCS = true;
            SetTime(MCSTIMER);
            return true;
        } else return false;
    } else return false;
    return true;
}
