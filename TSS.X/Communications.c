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
        //handleIndicators(receiveArray[LED_DDS]);
        //TBbarGraphs(receiveArray[THROTTLE_DDS], receiveArray[BRAKE_DDS]);
        //receiveArray[RESPONSE_ADDRESS] = 0;
    }
}

void respondECU() {
    LATCbits.LATC5 = 1;
    ToSend(RESPONSE_ADDRESS, DDS_ADDRESS);
    //ToSend(BUTTONS_DDS, buttonsCollector());
    Delay(9);
    sendData(ECU_ADDRESS);
    Delay(3);
    LATCbits.LATC5 = 0;
}
