#include "SScomms.h"
#include <stdbool.h>
#include "ADDRESSING.h"
#include "Timers.h"
#include "FastTransfer1.h"

bool readyToSendSS = 0;
int SSErrorCounter = 0;

bool requestSSData() {
    if (((GetTime(SSTIMER) > BOARD_RESEND_MIN) && (readyToSendSS)) || (GetTime(SSTIMER) > BOARD_TIMEOUT)) {
        static int DDSErrorCounter = 0;
        if (!readyToSendSS) {
            SSErrorCounter++;
            if (SSErrorCounter > 1) {
                SSErrorCounter = 0;
                return false;
            }
        } else {
            readyToSendSS = false;
            SSErrorCounter = 0;
        }
        ToSend1(RESPONSE_ADDRESS, ECU_ADDRESS);
        RS485_Direction1(TALK);
        sendData1(SS_ADDRESS);
        SetTime(SSTIMER);
    }
    return true;

}

bool receiveCommSS() {
    if (receiveData1()) {
//        if (receiveArray1[RESPONSE_ADDRESS] == DDS_ADDRESS) {
//            buttons = receiveArray1[BUTTONS_DDS];
//            readyToSendDDS = true;
//            SetTime(DDSTIMER);
            return true;
//        } else return false;
    } else return false;
}