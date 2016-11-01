#include "DDSComms.h"
#include "Timers.h"
#include "FastTransfer1.h"
#include "SASComms.h"
#include "Communications.h"
#include "ThrottleBrakeControl.h"
#include "PinDef.h"
#include <xc.h>

bool requestDDSData();
bool receiveCommDDS();
bool readyToSendDDS = true;
bool DDS_COMMS_ERROR = false;

unsigned int indicators;
unsigned int buttons;
int DDSErrorCounter = 0;

int buttonArray[8];

bool requestDDSData() {
    if ((GetTime(DDSTIMER) > DDS_BOARD_RESEND_MIN) && (readyToSendDDS == true)) {
        readyToSendDDS = false;
        ToSend1(RESPONSE_ADDRESS, ECU_ADDRESS);
        ToSend1(THROTTLE_DDS, GetThrottleBrakeValue(GETSAST1));
        ToSend1(BRAKE_DDS, GetThrottleBrakeValue(GETSASB1));
        ToSend1(LED_DDS, indicators);
        //ToSend1(LED_DDS, indicators);
        RS485_Direction1(TALK);
        sendData1(DDS_ADDRESS);
        SetTime(DDSTIMER);
        return true;
    }
    else if(readyToSendDDS == false){
        return true;
    }
    else{
        return false;
    }
}

bool receiveCommDDS() {
    if (receiveData1()) {                  
        if (ReceiveArray1Get(RESPONSE_ADDRESS) == DDS_ADDRESS){
            buttons = ReceiveArray1Get(BUTTONS_DDS);
            readyToSendDDS = true;
            SetTime(DDSTIMER);
            return true;
        } else return false;
    } else return false;
}

int seekButtonChange() {
    int i = 0;
    int changeInButton = 0;
    for (i = 0; i < 8; i++) {
        bool buttonState = ((buttons >> i)&(0x01));
        if (buttonArray[i] != buttonState) {
            buttonArray[i] = buttonState;
            changeInButton = i;
        }
    }
    return changeInButton;
}

void changeLEDState(int LED, int state) {
    if (state)
        indicators = indicators | (state << LED);
    
//    else if (state == 2)
//        indicators = indicators;//| (state << LED);
    
    else
        indicators = indicators & (0xFF^(!state << LED));
}

int GetDDSerrorCounter(){
    return DDSErrorCounter;
}


void ClearDDSTalk(){
    readyToSendDDS = true;
}