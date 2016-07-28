#include "BMMComms.h"
#include "SlaveAddressing.h"
#include "Timers.h"

extern int BMM_FAULT_CONDITION;
int BMMADC[4];

enum BMM {
    BATTERY_FAULT = 0,
    BATTERY_VOLTS = 1,
    BATTERY_TEMPS = 2,
    BATTERY_POWER = 3
};

struct commsStates {
    bool DDS;
    bool MCS;
    bool SAS;
    bool BMM;
    bool PDU;
    int DDS_SEND;
    int MCS_SEND;
    int SAS_SEND;
    enum BMM BMM_SEND;
    int PDU_SEND;
};

int milliVolts[NUMSLAVES][BATTPERSLAVE];
int temps[NUMSLAVES][BATTPERSLAVE];
int current1, current2, bigVolts;
int faultingBattery;
bool batteryFault = false;
bool requestBMMData(char state);
bool receiveCommBMM(char state);
bool readyToSendBMM = true;
bool BMM_COMMS_ERROR = false;

bool requestBMMData(char state) {
    if (((GetTime(BMMTimer) > BOARD_RESEND_MIN) && (readyToSendBMM)) || (GetTime(BMMTimer) > BOARD_TIMEOUT)) {
//        static int BMMErrorCounter = 0;
//        if (!readyToSendBMM) {
//            BMMErrorCounter++;
//            if (BMMErrorCounter > 1) {
//                BMMErrorCounter = 0;
//                return false;
//            }
//        } else {
//            BMMErrorCounter = 0;
//            readyToSendBMM = false;
//        }
        SetTime(BMMTimer);
        RS485_Direction2(TALK);

        switch (state) {
            case BATTERY_FAULT:
                ToSend(BMM_COMM_STATE, 0);
                break;
            case BATTERY_VOLTS:
                ToSend(BMM_COMM_STATE, 1);
                break;
            case BATTERY_TEMPS:
                ToSend(BMM_COMM_STATE, 2);
                break;
            case BATTERY_POWER:
                ToSend(BMM_COMM_STATE, 3);
                break;
        }
        //ToSend(RESPONSE_ADDRESS, ECU_ADDRESS);
        sendData(BMM_ADDRESS);
        RS485_Direction2(TALK);
    }
    return true;
}

bool receiveCommBMM(char state) {
    int j;
    if (receiveData()) {
//        if (receiveArray[BMM_FAULT]) {
//            BMM_FAULT_CONDITION = receiveArray[BMM_FAULT];
//            batteryFault = true;
//            faultingBattery = receiveArray[FAULTINGBATTERY];
//        }
        switch (state) {
            case BATTERY_FAULT:
                printf("BF1 = %d ",receiveArray[1]);
                printf("BF2 = %d ",receiveArray[2]);
                printf("BF3 = %d\n",receiveArray[3]);
                break;
            case BATTERY_VOLTS:
                printf("BV1 = %d ",receiveArray[1]);
                printf("BV2 = %d\n",receiveArray[2]);
                break;
            case BATTERY_TEMPS:
                printf("BT1 = %d ",receiveArray[1]);
                printf("BT2 = %d\n",receiveArray[2]);
                break;
            case BATTERY_POWER:
                printf("BA1 = %d ",receiveArray[1]);
                printf("BA2 = %d ",receiveArray[2]);
                printf("BA3 = %d\n",receiveArray[3]);
                break;
        }
        readyToSendBMM = true;
        SetTime(BMMTimer);
        return true;
    } else return false;
}
