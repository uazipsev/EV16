#include "SASComms.h"
#include "PinDef.h"
#include "Timers.h"
#include "FastTransfer1.h"
#include "Communications.h"
#include <xc.h>
#include "ThrottleBrakeControl.h"

unsigned int t1Raw, t2Raw, b1Raw, b2Raw;
bool receiveCommSAS();
bool requestSASData();
bool readyToSendSAS = true;
bool SAS_COMMS_ERROR = false;
int SASErrorCounter = 0;


#define THROTTLE_SANITY_CHECK 1
#define THROTTLE_BRAKE_CHECK  2

bool requestSASData() {
    //If either timeout or response with delay already occurred
    
    if (((GetTime(SASTIMER) > BOARD_RESEND_MIN) && (readyToSendSAS)) || (GetTime(SASTIMER) > BOARD_TIMEOUT)) {
        
//        SASErrorCounter = 0;
//        if (!readyToSendSAS) {
//            SASErrorCounter++;
//            if (SASErrorCounter > 1) {
//                SASErrorCounter = 0;
//                return false;
//            }
//        } else {
//            readyToSendSAS = false;
//            SASErrorCounter = 0;
//        }
        SetTime(SASTIMER);
        RS485_Direction1(TALK);
        ToSend1(RESPONSE_ADDRESS, ECU_ADDRESS);
        sendData1(SAS_ADDRESS);
        
    }

    return true;
}

bool receiveCommSAS() {
    if (receiveData1()) {
        //INDICATOR ^= 1;
        if (ReceiveArray1Get(RESPONSE_ADDRESS) == SAS_ADDRESS) {
           // INDICATOR ^= 1;
            t1Raw = ReceiveArray1Get(THROTTLE1_SAS);
            t2Raw = ReceiveArray1Get(THROTTLE2_SAS);
            b1Raw = ReceiveArray1Get(BRAKE1_SAS);
            b2Raw = ReceiveArray1Get(BRAKE2_SAS);
            CheckThrotleConsistency();
            readyToSendSAS = true;
            SetTime(SASTIMER);
            return true;
        }
        else{
            SASErrorCounter++;
            return false;
        }
    } 
    else{
        SASErrorCounter++;
        return false;
    }
}

int GetSASError(){
    return SASErrorCounter;
}

unsigned int GetSASRaw(char request){
    if(request == GETSAST1RAW){
        return t1Raw;
    }
    else if(request == GETSAST2RAW){
        return t2Raw;
    }
    else if(request == GETSASB1RAW){
        return b1Raw;
    }
    else if(request == GETSASB2RAW){
        return b2Raw;
    }
    else return 0;
}
