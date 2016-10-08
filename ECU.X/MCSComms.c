#include "MCSComms.h"
#include "PinDef.h"
#include "Timers.h"
#include "ThrottleBrakeControl.h"
#include "FastTransfer.h"
#include "Communications.h"
#include "ADDRESSING.h"


bool requestMCSData();
bool receiveCommMCS();
bool readyToSendMCS = true;
bool MCS_COMMS_ERROR = false;
extern int carActive;
static int MCSErrorCounter = 0;

bool requestMCSData() {
    if((GetTime(MCSTIMER) > BOARD_RESEND_MIN) && (readyToSendMCS == true)) {
        static int MCSErrorCounter = 0;
        //INDICATOR ^= 1;
        RS485_Direction2(TALK);
        readyToSendMCS = false;
        MCSErrorCounter = 0;
        
        ToSend(RESPONSE_ADDRESS, ECU_ADDRESS);
        ToSend(OUTPUT_ACTIVE, carActive);
        ToSend(THROTTLE_OUTPUT, GetThrottleBrakeValue(GETSAST1));//TODO may need to add 40.95 if mcs gets rid of theres
        ToSend(BRAKE_OUTPUT, GetThrottleBrakeValue(GETSASB1)); //TODO may need to add 40.95 if mcs gets rid of theres
        sendData(MCS_ADDRESS);
        SetTime(MCSTIMER);
        return true;
    }
    else if(readyToSendMCS == false){
        return true;
    }
    else{
        return false;
    }
}

bool receiveCommMCS() {
    if (receiveData()) {
        if (ReceiveArrayGet(RESPONSE_ADDRESS) == MCS_ADDRESS) {
            readyToSendMCS = true;
            SetTime(MCSTIMER);
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
    return false;
}

char GetMCSFault(){
    return MCSErrorCounter;
}

void ClearMCSTalk(){
    readyToSendMCS = true;
}
