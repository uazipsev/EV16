#include "SASComms.h"
#include "PinDef.h"
#include "Timers.h"
#include "FastTransfer1.h"
#include "Communications.h"

unsigned int throttle1, throttle2, brake1,brake2, TripThrottle;
unsigned int t1Raw, t2Raw, bRaw, TripBrake;
bool receiveCommSAS();
bool requestSASData();
bool readyToSendSAS = true;
bool SAS_COMMS_ERROR = false;
static int SASErrorCounter = 0;
int ThrottlePrecent;

#define THROTTLE_SANITY_CHECK 1
#define THROTTLE_BRAKE_CHECK  2

bool requestSASData() {
    //If either timeout or response with delay already occurred
    if (((GetTime(SASTIMER) > BOARD_RESEND_MIN) && (readyToSendSAS)) || (GetTime(SASTIMER) > BOARD_TIMEOUT)) {
        SASErrorCounter = 0;
        if (!readyToSendSAS) {
            SASErrorCounter++;
            if (SASErrorCounter > 1) {
                SASErrorCounter = 0;
                return false;
            }
        } else {
            readyToSendSAS = false;
            SASErrorCounter = 0;
        }
        SetTime(SASTIMER);
        RS485_Direction1(TALK);
        ToSend1(RESPONSE_ADDRESS, ECU_ADDRESS);
        sendData1(SAS_ADDRESS);
    }

    return true;
}

extern int SAS_FAULT_CONDITION;
bool checkSASInputs(unsigned int t1, unsigned int t2, unsigned int b) {
    t1Raw = t1;
    t2Raw = t2;
    bRaw = b;

    //throttle consistency check
//        if (!(((t1*(ThrottlePrecent\100)) > t2) && ((t1 *((ThrottlePrecent\100)-1)) < t2))) {
//            SAS_FAULT_CONDITION = THROTTLE_SANITY_CHECK; // TODO: This is erroring out - need filtering!
//            return false;
//        }

    return true;
}

void storeSASInputs() {
//    if (t1Raw < 100 && t1Raw > 0) {
        throttle1 = t1Raw;
//        if (throttle1 < 0) throttle1 = 0;
//        if (throttle1 > 100) throttle1 = 100;
//    } else throttle1 = 0;
//    if (t2Raw < 100 && t2Raw > 0) {
        throttle2 =t2Raw;
//        if (throttle2 < 0) throttle2 = 0;
//        if (throttle2 > 100) throttle2 = 100;
//    } else throttle2 = 0;
//    if (bRaw < 100 && bRaw > 0) {
        brake1 = bRaw;
//        if (brake < 0) brake = 0;
//        if (brake > 100) brake = 100;
//    } else brake = 0;
    //    //Brake vs. throttle safety
        if ((((throttle1 + throttle2) / 2) > TripThrottle) && (brake1 > TripBrake)) {
            SAS_FAULT_CONDITION = THROTTLE_BRAKE_CHECK;  //  TODO: Fix me
            throttle1=0;
            throttle2=0;
            brake1=0;
        }
}

bool receiveCommSAS() {
    if (receiveData1()) {
        //INDICATOR ^= 1;
        if (ReceiveArray1Get(RESPONSE_ADDRESS) == SAS_ADDRESS) {
           // INDICATOR ^= 1;
            if (checkSASInputs(ReceiveArray1Get(THROTTLE1_SAS), ReceiveArray1Get(THROTTLE2_SAS), ReceiveArray1Get(BRAKE_SAS))) {
                storeSASInputs();
            }

            readyToSendSAS = true;
            SetTime(SASTIMER);
            return true;
        } else return false;
    } else return false;
}

void SetBrakeValue(int val){
    TripBrake = val;
}

void SetThrottleValue(int val){
    TripThrottle = val;
}

char GetSASFalts(){
    return SAS_FAULT_CONDITION;
}

unsigned int GetSASValue(char request){
    if(request == GETSAST1){
        return throttle1;
    }
    else if(request == GETSAST2){
        return throttle2;
    }
    else if(request == GETSASB1){
        return brake1;
    }
    else if(request == GETSASB2){
        return brake2;
    }
    else return 0;
}

unsigned int GetSASRaw(char request){
    if(request == GETSAST1RAW){
        return t1Raw;
    }
    else if(request == GETSAST2RAW){
        return t2Raw;
    }
    else if(request == GETSASB1RAW){
        return bRaw;
    }
    else if(request == GETSASB2RAW){
        return 0;
    }
    else return 0;
}
