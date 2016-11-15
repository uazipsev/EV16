
#include "Communications.h"
#include "BatteryManagment.h"
#include "Function.h"
#include "FastTransfer.h"
#include "UART.h"
#include "Timers.h"
#include <stdbool.h>

#define LOW_VOLTAGE_FLAG 1
#define HIGH_TEMPERATURE_FLAG 2
#define COMMUNICATIONS_FAULT 3
#define UART_BUFFER_SIZE 200

int x = 0;

char receiveArray[100];

bool pendingSend = false;

enum BMM {
    BATTERY_FAULT = 0,
    BATTERY_VOLTS = 1,
    BATTERY_TEMPS = 2,
    BATTERY_POWER = 3,
    CHARGER = 7
} COMM_STATE;
int faultFlag = 0;
int slaveaddr = 0;
bool portClosed = false;

void CommStart(){
    begin(receiveArray, sizeof (receiveArray), BMM_ADDRESS, false, Send_put, Receive_get, Receive_available, Receive_peek);
    UART_init();
}

void updateComms() {
    if (receiveData()) {
        
        //TODO: need to remove this and make the arrays static :(
        //UART_buff_flush(&input_buffer,1);
        time_Set(TLKTM,0);
        COMM_STATE = receiveArray[BMM_COMM_STATE];
        pendingSend = true;
        //INDICATOR = !INDICATOR;
    }
    if (!portClosed && pendingSend ) {
        RS485_Port = TALK;
        portClosed = true;
        //INDICATOR = !INDICATOR;
    }
    if (pendingSend && time_get(TLKTM)> 6 && portClosed) {
        if(!ChargerVal()){
            switch (COMM_STATE) {
                case BATTERY_VOLTS:
                    ToSend(1, 15);
                    ToSend(2, 30);
                    ToSend(3, 30);
                    ToSend(4, 30);
                    ToSend(5, 30);
                    ToSend(6, 30);
                    ToSend(7, 425);
                    ToSend(8, 225);
                    break;
                case BATTERY_TEMPS:
                    ToSend(1, 45);
                    ToSend(2, 30);
                    ToSend(3, 44);
                    ToSend(4, 43);
                    ToSend(5, 46);
                    ToSend(6, 50);
                    ToSend(7, 23);
                    ToSend(8, 50);
                    break;
                case BATTERY_POWER:
                    ToSend(1, CurrentGet(0,1));
                    ToSend(2, CurrentGet(0,2));
                    ToSend(3, CurrentGet(0,3));
                    break;
                case BATTERY_FAULT:
                    ToSend(1, 0);
                    ToSend(2, 1);
                    ToSend(3, 2);
                    break;
                case CHARGER:
                    ChargerEN();
                    break;
                default:
                    break;

            }
        }
        else{
            //This is where we add info for the charger communication 
            ToSend(1, 1); //Set Precharge enable and on 
            ToSend(2, 25); //Set charging current 
            ToSend(3, 295); //Set Voltage
            ToSend(4, 415); //Set avg cell V
            ToSend(4, 5); //Set BMM mode
        }
        //ToSend(RESPONSE_ADDRESS, ECU_ADDRESS);
        sendData(ECU_ADDRESS);
        pendingSend = false;
        TalkTimeSet(0);
    }
    checkCommDirection();
}
void Send_To_Charger(int Charge, int voltage, int amps){


}
void checkCommDirection() {
    //you have finished send and time has elapsed.. start listen
    //if (GetTxStall() && (time_get(TLKTM) > 20) && (RS485_Port == TALK) && portClosed && !pendingSend) {
    if ((time_get(TLKTM) > 20) && (RS485_Port == TALK) && !pendingSend) {
        RS485_Port = LISTEN;
        portClosed = false;
        //pendingSend = false;
    }
}

