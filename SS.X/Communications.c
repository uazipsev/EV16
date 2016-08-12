#include <stdbool.h>
#include <xc.h>
#include "FastTransfer.h"
#include "Communications.h"
#include "ADDRESSING.h"
#include "PinDef.h"

void updateComms() {
    if (receiveData()) {
        respondECU();
    }
}

void respondECU() {
    RS485_TSS_Direction = TALK;
    ToSend(1,0);
    Delay(9);
    sendData(ECU_ADDRESS);
    Delay(3);
    RS485_TSS_Direction = LISTEN;
}

void Delay(int wait) {
    int x;
    for (x = 0; x < wait; x++) {
        __delay_ms(1);
    }
}

