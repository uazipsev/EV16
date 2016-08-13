#include <stdbool.h>
#include <xc.h>
#include "FastTransfer.h"
#include "Communications.h"
#include "ADDRESSING.h"
#include "PinDef.h"
#include "Function.h"

void updateComms() {
    if (receiveData()) {
        respondECU();
    }
}

void respondECU() {
    RS485_TSS_Direction = TALK;
    ToSend(1,GetFaults(1));
    ToSend(2,GetFaults(0));
    Delay(9);
    sendData(ECU_ADDRESS);
    Delay(3);
    RS485_TSS_Direction = LISTEN;
}




