#include "SASComms.h"

unsigned int throttle1, throttle2, brake;
unsigned int t1Raw, t2Raw, bRaw;
bool receiveCommSAS();
bool requestSASData();
bool readyToSendSAS = true;
bool SAS_COMMS_ERROR = false;
#define THROTTLE_SANITY_CHECK 1
#define THROTTLE_BRAKE_CHECK  2
void debugSAS() {
    ToSend2(5, throttle1);
    ToSend2(6, throttle2);
    ToSend2(7, brake);
    sendData2(DEBUG_ADDRESS);

}

bool requestSASData() {
    //If either timeout or response with delay already occurred
    if (((SASTimer > BOARD_RESEND_MIN) && (readyToSendSAS)) || (SASTimer > BOARD_TIMEOUT)) {
        static int SASErrorCounter = 0;
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
        SASTimer = 0;
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
        if (!(((t1*1.1) > t2) && ((t1 *0.9) < t2))) {
            SAS_FAULT_CONDITION = THROTTLE_SANITY_CHECK;
            return false;
        }

    return true;
}

void storeSASInputs() {
    if (t1Raw < 100 && t1Raw > 0) {
        throttle1 = t1Raw;
        if (throttle1 < 0) throttle1 = 0;
        if (throttle1 > 100) throttle1 = 100;
    } else throttle1 = 0;
    if (t2Raw < 100 && t2Raw > 0) {
        throttle2 =t2Raw;
        if (throttle2 < 0) throttle2 = 0;
        if (throttle2 > 100) throttle2 = 100;
    } else throttle2 = 0;
    if (bRaw < 100 && bRaw > 0) {
        brake = bRaw;
        if (brake < 0) brake = 0;
        if (brake > 100) brake = 100;
    } else brake = 0;
    //    //Brake vs. throttle safety
        if ((((throttle1 + throttle2) / 2) > TRIP_THROTTLE) && (brake > TRIP_BRAKE)) {
            SAS_FAULT_CONDITION = THROTTLE_BRAKE_CHECK;
            throttle1=0;
            throttle2=0;
            brake=0;
        }
}

bool receiveCommSAS() {
    if (receiveData1()) {
        if (receiveArray1[RESPONSE_ADDRESS] == SAS_ADDRESS) {
            if (checkSASInputs(receiveArray1[THROTTLE1_SAS], receiveArray1[THROTTLE2_SAS], receiveArray1[BRAKE_SAS])) {
                storeSASInputs();
            }

            readyToSendSAS = true;
            SASTimer = 0;
            return true;
        } else return false;
    } else return false;
}
