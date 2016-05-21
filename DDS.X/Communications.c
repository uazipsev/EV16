#include <stdbool.h>
#include <xc.h>
#include "FastTransfer.h"
#include "Communications.h"
#include "ADDRESSING.h"

void updateComms() {
  
    if (receiveData()) {
        //if (receiveArray[RESPONSE_ADDRESS] == ECU_ADDRESS) {
        respondECU();
        //}
        handleIndicators(receiveArray[LED_DDS]);
        TBbarGraphs(receiveArray[THROTTLE_DDS], receiveArray[BRAKE_DDS]);
        receiveArray[RESPONSE_ADDRESS] = 0;
    }
}

void respondECU() {
    LATCbits.LATC5 = 1;
    ToSend(RESPONSE_ADDRESS, DDS_ADDRESS);
    ToSend(BUTTONS_DDS, buttonsCollector());
    Delay(9);
    sendData(ECU_ADDRESS);
    Delay(3);
    LATCbits.LATC5 = 0;
}

extern void SetLEDOut(int lednum, int state);
#define NUM_INDICATORS 6

void handleIndicators(int receivedIndicators) {
    static int oldIndicators = 0;
    if (receivedIndicators != oldIndicators) {
        int i = 0;
        for (i = 0; i < NUM_INDICATORS; i++) {
            SetLEDOut(i, ((receivedIndicators >> i)&0x01));
        }
        oldIndicators = receivedIndicators;
    }

}

void TBbarGraphs(int t, int b) {
    throttle = t;
    brake = b;
}


extern bool GetButtonState(int btnnum);
#define NUM_BUTTONS 8

unsigned int buttonsCollector() {
    unsigned int sendVal = 0;
    int i = 0;
    for (i = 0; i < NUM_BUTTONS; i++) {
        sendVal = sendVal | ((GetButtonState(i)&0x01) << i);
    }
    return sendVal;
}
