#include <stdbool.h>
#include <xc.h>
#include "FastTransfer.h"
#include "Communications.h"
#include "ADDRESSING.h"
#include "UART.h"
#include "PinDef.h"

char receiveArray[50];

void TSSCommsStart(){
    begin(receiveArray, sizeof (receiveArray), TM_ADDRESS, false, Send_put, Receive_get, Receive_available, Receive_peek);
    UART_init();
}

void updateComms() {
    if()
    if(receiveData()) {
       //respondTM(1);
    }
}

void respondTM(char val) {
    RS485_TSS_Direction = TALK;
    if(val == 1){
        sendData(TSS_1_ADDRESS);
    }
    if(val == 2){
        sendData(TSS_2_ADDRESS);
    } 
    RS485_TSS_Direction = LISTEN;
}
