#include <stdbool.h>
#include <xc.h>
#include "FastTransfer.h"
#include "Communications.h"
#include "ADDRESSING.h"
#include "PinDef.h"
#include "Function.h"
#include "UART.h"

char receiveArray[10];

void ComStart(){
    EUSART1_Initialize();    
    begin(receiveArray, sizeof (receiveArray), SS_ADDRESS, false, Send_put, Receive_get, Receive_available, Receive_peek);
}

void updateComms() {
    if (receiveData()) {  // If data is here for us 
        respondECU();     //respond with Falt data
    }
}

void respondECU() {
    RS485_TSS_Direction = TALK;  //RS485 set to talk
    ToSend(1,GetFaults(1));      //Send falt high byte
    ToSend(2,GetFaults(0));      //Send falt low byte
    Delay(9);
    sendData(ECU_ADDRESS);       //Send data to ECU
    Delay(3);
    RS485_TSS_Direction = LISTEN;  ///RS485 set to listen
}




