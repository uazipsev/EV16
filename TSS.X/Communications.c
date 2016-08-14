#include <stdbool.h>
#include <xc.h>
#include "FastTransfer.h"
#include "Communications.h"
#include "ADDRESSING.h"
#include "mcc_generated_files/eusart1.h"

char receiveArray[10];

void CommsStart(){
    begin(receiveArray, sizeof (receiveArray), TM_ADDRESS, false, Send_put, Receive_get, Receive_available, Receive_peek);
    EUSART1_Initialize();
}

void updateComms() {
    if (receiveData()) {
        //if (receiveArray[RESPONSE_ADDRESS] == ECU_ADDRESS) {
        respondTM();
        //}
        //handleIndicators(receiveArray[LED_DDS]);
        //TBbarGraphs(receiveArray[THROTTLE_DDS], receiveArray[BRAKE_DDS]);
        //receiveArray[RESPONSE_ADDRESS] = 0;
    }
}

void respondTM() {
    LATCbits.LATC5 = 1;
    ToSend(RESPONSE_ADDRESS, DDS_ADDRESS);
    //ToSend(BUTTONS_DDS, buttonsCollector());
    Delay(9);
    sendData(ECU_ADDRESS);
    Delay(3);
    LATCbits.LATC5 = 0;
}
