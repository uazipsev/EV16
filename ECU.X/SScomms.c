#include "SScomms.h"
#include <stdbool.h>
#include "ADDRESSING.h"
#include "Timers.h"

bool readyToSendSS = 0;

bool requestSSData() {
    if (((GetTime(SSTIMER) > BOARD_RESEND_MIN) && (readyToSendSS)) || (GetTime(SSTIMER) > BOARD_TIMEOUT)) {
//        static int DDSErrorCounter = 0;
//        if (!readyToSendDDS) {
//            DDSErrorCounter++;
//            if (DDSErrorCounter > 1) {
//                DDSErrorCounter = 0;
//                return false;
//            }
//        } else {
//            readyToSendDDS = false;
//            DDSErrorCounter = 0;
//        }
//        ToSend1(RESPONSE_ADDRESS, ECU_ADDRESS);
//        ToSend1(THROTTLE_DDS, throttle1);
//        ToSend1(BRAKE_DDS, brake);
//        ToSend1(LED_DDS, indicators);
//        RS485_Direction1(TALK);
//        sendData1(DDS_ADDRESS);
//        SetTime(DDSTIMER);
    }
    return true;

}

bool receiveCommSS() {
    if (receiveData1()) {
//        if (receiveArray1[RESPONSE_ADDRESS] == DDS_ADDRESS) {
//            buttons = receiveArray1[BUTTONS_DDS];
//            readyToSendDDS = true;
//            SetTime(DDSTIMER);
//            return true;
//        } else return false;
    } else return false;
}