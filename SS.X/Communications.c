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
    EUSART1_Initialize();  //Config USART  
    begin(receiveArray, sizeof (receiveArray), SS_ADDRESS, false, Send_put, Receive_get, Receive_available, Receive_peek); //Start FT
}

void updateComms() {
    if (receiveData()) {  // If data is here for us 
        respondECU();     //respond with Falt data
    }
}

void respondECU() {
    RS485_TSS_Direction = TALK;  //RS485 set to talk
    ToSend(0,SS_ADDRESS);      //Send fault high byte
    ToSend(1,GetFaults(1));      //Send fault high byte
    ToSend(2,GetFaults(0));      //Send fault low byte
    Delay(5);
    sendData(ECU_ADDRESS);       //Send data to ECU
    Delay(3);
    RS485_TSS_Direction = LISTEN;  ///RS485 set to listen
}




