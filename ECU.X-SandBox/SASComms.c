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
//    
//    if ((GetTime(SASTIMER) > BOARD_RESEND_MIN) && (readyToSendSAS == true)) {
//        readyToSendSAS = false;
//        RS485_Direction1(TALK);
//        Delay(1);
//        ToSend1(RESPONSE_ADDRESS, ECU_ADDRESS);
//        sendData1(SAS_ADDRESS);
//        SetTime(SASTIMER);
//        return true;
//    }
//    else if(readyToSendSAS == false){
        return true;
//    }
//    else{
//        return false;
//    }
}

bool receiveCommSAS() {
//    if (receiveData1()) {
//        if (ReceiveArray1Get(RESPONSE_ADDRESS) == SAS_ADDRESS) {
//           // INDICATOR ^= 1;
//            t1Raw = ReceiveArray1Get(THROTTLE1_SAS);
//            t2Raw = ReceiveArray1Get(THROTTLE2_SAS);
//            b1Raw = ReceiveArray1Get(BRAKE1_SAS);
//            b2Raw = ReceiveArray1Get(BRAKE2_SAS);
//            CheckThrotleConsistency();
//            readyToSendSAS = true;
//            SetTime(SASTIMER);
            return true;
//        }
//        else{
//            //SASErrorCounter++;
//            wipeRxBuffer1();
//            return false;
//        }
//    } 
//    else{
//        //SASErrorCounter++;
//        return false;
//    }
}

int GetSASError(){
    return SASErrorCounter;
}

void ClearSASTalk(){
    readyToSendSAS = true;
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
