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
bool requestBMMData(struct commsStates * cS);
bool receiveCommBMM(struct commsStates * cS);
bool readyToSendBMM = true;
bool BMM_COMMS_ERROR = false;

bool requestBMMData(struct commsStates * cS) {
    if (((GetTime(BMMTimer) > BOARD_RESEND_MIN) && (readyToSendBMM)) || (GetTime(BMMTimer) > BOARD_TIMEOUT)) {
        static int BMMErrorCounter = 0;
        if (!readyToSendBMM) {
            BMMErrorCounter++;
            if (BMMErrorCounter > 1) {
                BMMErrorCounter = 0;
                return false;
            }
        } else {
            BMMErrorCounter = 0;
            readyToSendBMM = false;
        }
        SetTime(BMMTimer);
        RS485_Direction2(TALK);

        switch ((*cS).BMM_SEND) {
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
        ToSend(RESPONSE_ADDRESS, ECU_ADDRESS);
        sendData(BMM_ADDRESS);
        RS485_Direction2(TALK);
    }
    return true;
}

bool receiveCommBMM(struct commsStates * cS) {
    int j;
    if (receiveData()) {
        if (receiveArray[BMM_FAULT]) {
            BMM_FAULT_CONDITION = receiveArray[BMM_FAULT];
            batteryFault = true;
            faultingBattery = receiveArray[FAULTINGBATTERY];
        }
        switch ((*cS).BMM_SEND) {
            case BATTERY_FAULT:
                break;
            case BATTERY_VOLTS:
                for (j = 0; j < BATTPERSLAVE; j++)
                    milliVolts[receiveArray[SLAVE_ADDRESS_SEND]][j] = receiveArray[BATTERYV_ECU + j];
                break;
            case BATTERY_TEMPS:
                for (j = 0; j < BATTPERSLAVE; j++)
                    temps[receiveArray[SLAVE_ADDRESS_SEND]][j] = receiveArray[BATTERYT_ECU + j];
                break;
            case BATTERY_POWER:
                BMMADC[0] = receiveArray[CURRENT_BMM1];
                BMMADC[1] = receiveArray[CURRENT_BMM2];
                BMMADC[2] = receiveArray[CURRENT_BMM3];
                BMMADC[3] = receiveArray[CURRENT_BMM4];
                break;
        }
        readyToSendBMM = true;
        SetTime(BMMTimer);
        return true;
    } else return false;
}
