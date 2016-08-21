#include <stdbool.h>
#include <xc.h>
#include "FastTransfer.h"
#include "Communications.h"
#include "ADDRESSING.h"
#include "UART.h"
#include "PinDef.h"
#include "Timers.h"

#define SAMPLERATE 500

int receiveArray[50];

bool portClosed = true;
bool pendingSend = false;

void TSSCommsStart(){
    begin(receiveArray, sizeof (receiveArray), TM_ADDRESS, false, Send_put, Receive_get, Receive_available, Receive_peek);
    UART_init();
}

void updateComms() {
    if (receiveData()) {
        //INDICATOR = !INDICATOR;
        
    }
    if(GetTime(TSSTIME) > SAMPLERATE){
        pendingSend = true;
    }
    if (!portClosed && pendingSend ) {
        RS485_TSS_Direction = TALK;
        portClosed = true;
    }
    if (!pendingSend && portClosed) {

            sendData(ECU_ADDRESS);
            pendingSend = true;

            SetTime(TSSTIME);
    }
    checkCommDirection();
}

void checkCommDirection() {
    //you have finished send and time has elapsed.. start listen
    //if (GetTxStall() && (time_get(TLKTM) > 20) && (RS485_Port == TALK) && portClosed && !pendingSend) {
    if ((GetTime(TSSTIME) > 20) && (RS485_TSS_Direction == TALK) && pendingSend) {
        RS485_TSS_Direction = LISTEN;
        portClosed = false;
        pendingSend = false;
    }
}
