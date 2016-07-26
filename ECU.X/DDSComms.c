#include "DDSComms.h"
#include "Timers.h"

bool requestDDSData();
bool receiveCommDDS();
bool readyToSendDDS = true;
bool DDS_COMMS_ERROR = false;

bool requestDDSData() {
    if (((GetTime(DDSTimer) > BOARD_RESEND_MIN) && (readyToSendDDS)) || (GetTime(DDSTimer) > BOARD_TIMEOUT)) {
        static int DDSErrorCounter = 0;
        if (!readyToSendDDS) {
            DDSErrorCounter++;
            if (DDSErrorCounter > 1) {
                DDSErrorCounter = 0;
                return false;
            }
        } else {
            readyToSendDDS = false;
            DDSErrorCounter = 0;
        }
        ToSend1(RESPONSE_ADDRESS, ECU_ADDRESS);
        ToSend1(THROTTLE_DDS, throttle1);
        ToSend1(BRAKE_DDS, brake);
        ToSend1(LED_DDS, indicators);
        RS485_Direction1(TALK);
        sendData1(DDS_ADDRESS);
        SetTime(DDSTimer);
    }
    return true;

}

bool receiveCommDDS() {
    if (receiveData1()) {
        if (receiveArray1[RESPONSE_ADDRESS] == DDS_ADDRESS) {
            buttons = receiveArray1[BUTTONS_DDS];
            readyToSendDDS = true;
            SetTime(DDSTimer);
            return true;
        } else return false;
    } else return false;
}
