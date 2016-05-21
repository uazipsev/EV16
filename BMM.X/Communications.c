
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

char receiveArray[100];

bool pendingSend = false;

//extern struct UART_ring_buff {
//    unsigned char buf[UART_BUFFER_SIZE];
//    int head;
//    int tail;
//    int count;
//};

//extern struct UART_ring_buff input_buffer;
//extern void UART_buff_flush(struct UART_ring_buff* _this, const int clearBuffer);
//extern int faultingBattery;

enum BMM {
    BATTERY_FAULT = 0,
    BATTERY_VOLTS = 1,
    BATTERY_TEMPS = 2,
    BATTERY_POWER = 3
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
        INDICATOR = !INDICATOR;
        //TODO: need to remove this and make the arrays static :(
        //UART_buff_flush(&input_buffer,1);
        time_Set(TLKTM,0);
        COMM_STATE = receiveArray[BMM_COMM_STATE];
        pendingSend = true;
        //ToSend(2, 12);
    }
    if (!portClosed && pendingSend && time_get(TLKTM) > 5) {
        RS485_Port = TALK;
        portClosed = true;
    }
    if (pendingSend && time_get(TLKTM)> 6 && portClosed) {
        if(ChargerVal()){
            ToSend(2, 12);
            static int lastCommState = 0;
            switch (COMM_STATE) {
                case BATTERY_VOLTS:
                    ToSend(2, 12);
                    if (lastCommState != COMM_STATE) {
                        lastCommState = COMM_STATE;
                        slaveaddr = 0;
                    }
                    populateBatteryV(slaveaddr++);
                   // if (slaveaddr >= NUMSLAVES1) slaveaddr = 0;
                    break;
                case BATTERY_TEMPS:
                    if (lastCommState != COMM_STATE) {
                        lastCommState = COMM_STATE;
                        slaveaddr = 0;
                    }
                    populateBatteryT(slaveaddr++);
                    ToSend(2, 12);
                   // if (slaveaddr >= NUMSLAVES1) slaveaddr = 0;
                    break;
                case BATTERY_POWER:
                    if (lastCommState != COMM_STATE) {
                        lastCommState = COMM_STATE;
                        ToSend(2, 12);
                        ToSend(2, 12);
                        ToSend(2, 12);
                        ToSend(2, 12);
                    }
                    break;
                case BATTERY_FAULT:
                    if (lastCommState != COMM_STATE) {
                        lastCommState = COMM_STATE;
                    }
                    ToSend(2, 12);
                    break;
//                case 6:
//                    if (lastCommState != COMM_STATE) {
//                        lastCommState = COMM_STATE;
//                    }
//                    ChargerEN();
//                    ToSend(2, 12);
//                    break;
                default:
                    ToSend(2, 12);
                    break;

            }
            ToSend(2, 12);
            switch (faultFlag) {
                case 0:
                    LATBbits.LATB0=1;
                    Delay(1);
                    LATBbits.LATB0=0;
                    //faultingBattery = 0;
                    ToSend(2, 12);
                    break;

                case LOW_VOLTAGE_FLAG:
                    ToSend(2, 12);
                case HIGH_TEMPERATURE_FLAG:
                    ToSend(2, 12);
                case COMMUNICATIONS_FAULT:
                    ToSend(2, 12);
                    LATAbits.LATA1=1;
                    Delay(1);
                    LATAbits.LATA1=0;
                default:
                    ToSend(2, 12);
                    break;
            }
            sendData(ECU_ADDRESS);
            pendingSend = false;

            TalkTimeSet(0);
        }
//        else(){
//            //This is where we add info for the charger communication 
//            
//        }
    }
    checkCommDirection();
}

void checkCommDirection() {
    //you have finished send and time has elapsed.. start listen
    if (GetTxStall() && (time_get(TLKTM) > 20) && (RS485_Port == TALK) && portClosed && !pendingSend) {
        RS485_Port = LISTEN;
        portClosed = false;
    }
}

void populateBatteryT(int slave) {
//    ToSend(SLAVE_ADDRESS_SEND, slave);
//    int j = 0;
//    for (j = 0; j < BATTPERSLAVE; j++) {
//        ToSend(BATTERYT_ECU + j, BTemps[slave][j]);
//    }
}

void populateBatteryV(int slave) {
//    ToSend(SLAVE_ADDRESS_SEND, slave);
//    int j = 0;
//    for (j = 0; j < BATTPERSLAVE; j++) {
//        ToSend(BATTERYV_ECU + j, BVolts[slave][j]);
//    }
}


















//
//#include "Communications.h"
//#include "Function.h"
//#include "BatteryManagment.h"
//
//#define LOW_VOLTAGE_FLAG 1
//#define HIGH_TEMPERATURE_FLAG 2
//#define COMMUNICATIONS_FAULT 3
//
//#define UART_BUFFER_SIZE 200
//extern struct UART_ring_buff {
//    unsigned char buf[UART_BUFFER_SIZE];
//    int head;
//    int tail;
//    int count;
//};
//
//extern struct UART_ring_buff input_buffer;
//extern void UART_buff_flush(struct UART_ring_buff* _this, const int clearBuffer);
//extern int ADCReadings[4];
//
//enum BMM {
//    BATTERY_FAULT = 0,
//    BATTERY_VOLTS = 1,
//    BATTERY_TEMPS = 2,
//    BATTERY_POWER = 3,
//    BATTERY_MODE = 4
//} COMM_STATE;
//int faultFlag = 0;
//int slaveaddr = 0;
//bool portClosed = false;
//
//void updateComms() {
//    //checkSlaveCommDirection();
//    //updateSlaveCommunications();
//    if (receiveData()) {
//        UART_buff_flush(&input_buffer,1);
//        talkTime = 0;
//        COMM_STATE = receiveArray[BMM_COMM_STATE];
//        pendingSend = true;
//    }
//    if (!portClosed && pendingSend && talkTime > 5) {
//        RS485_Port = TALK;
//        portClosed = true;
//    }
//    if (pendingSend && talkTime > 6 && portClosed) {
//        ToSend(RESPONSE_ADDRESS, BMM_ADDRESS);
//        static int lastCommState = 0;
//        switch (COMM_STATE) {
//            case BATTERY_VOLTS:
//                if (lastCommState != COMM_STATE) {
//                    lastCommState = COMM_STATE;
//                    slaveaddr = 0;
//                }
//                //populateBatteryV(slaveaddr++);
//                //if (slaveaddr >= NUMSLAVES1) slaveaddr = 0;
//                break;
//            case BATTERY_TEMPS:
//                if (lastCommState != COMM_STATE) {
//                    lastCommState = COMM_STATE;
//                    slaveaddr = 0;
//                }
//               // populateBatteryT(slaveaddr++);
//                //if (slaveaddr >= NUMSLAVES1) slaveaddr = 0;
//                break;
//            case BATTERY_POWER:
//                if (lastCommState != COMM_STATE) {
//                    lastCommState = COMM_STATE;
//                    ToSend(CURRENT_BMM1, ADCReadings[0]);
//                    ToSend(CURRENT_BMM2, ADCReadings[1]);
//                    ToSend(CURRENT_BMM3, ADCReadings[2]);
//                    ToSend(CURRENT_BMM4, ADCReadings[3]);
//                }
//                break;
//            case BATTERY_FAULT:
//                if (lastCommState != COMM_STATE) {
//                    lastCommState = COMM_STATE;
//                }
//                break;
//            case BATTERY_MODE:
//                ChargerEN();
//            default:
//                break;
//
//        }
//        ToSend(BMM_FAULT, faultFlag);
//        switch (faultFlag) {
//            case 0:
//                LATBbits.LATB0=1;
//                Delay(1);
//                LATBbits.LATB0=0;
//                //faultingBattery = 0;
//                break;
//            case LOW_VOLTAGE_FLAG:
//            case HIGH_TEMPERATURE_FLAG:
//            case COMMUNICATIONS_FAULT:
//                //ToSend(FAULTINGBATTERY, faultingBattery);
//                LATAbits.LATA1=1;
//                Delay(1);
//                LATAbits.LATA1=0;
//            default:
//                break;
//        }
//        sendData(ECU_ADDRESS);
//        pendingSend = false;
//
//        talkTime = 0;
//    }
//    checkCommDirection();
//}
//
//void checkCommDirection() {
//    //you have finished send and time has elapsed.. start listen
//    if (Transmit_stall && (talkTime > 12) && (RS485_Port == TALK) && portClosed && !pendingSend) {
//        RS485_Port = LISTEN;
//        portClosed = false;
//    }
//}
//
//void populateBatteryT(int slave) {
////    ToSend(SLAVE_ADDRESS_SEND, slave);
////    int j = 0;
////    for (j = 0; j < BATTPERSLAVE; j++) {
////        ToSend(BATTERYT_ECU + j, BTemps[slave][j]);
////    }
//}
//
//void populateBatteryV(int slave) {
////    ToSend(SLAVE_ADDRESS_SEND, slave);
////    int j = 0;
////    for (j = 0; j < BATTPERSLAVE; j++) {
////        ToSend(BATTERYV_ECU + j, BVolts[slave][j]);
////    }
//}
//
