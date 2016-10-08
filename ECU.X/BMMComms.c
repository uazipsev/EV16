#include "BMMComms.h"
#include "SlaveAddressing.h"
#include "Timers.h"
#include "FastTransfer.h"
#include <xc.h>
#include "PinDef.h"

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

int current1, current2, current3, CellMaxVolt, CellMinVolt, CellMinTemp, CellMaxTemp;
int FaultV, FaultT, FaultC;
int SubPackV[6];
int SubPackT[6];
int faultingBattery;
bool batteryFault = false;
bool requestBMMData(char state);
bool receiveCommBMM(char state);
bool readyToSendBMM = true;
bool BMM_COMMS_ERROR = false;

bool requestBMMData(char state) {

    if((GetTime(BMMTIMER) > BMM_BOARD_RESEND_MIN) && (readyToSendBMM == true)) {
        //INDICATOR = !INDICATOR;
            INDICATOR ^= 1;
        readyToSendBMM = false;
        SetTime(BMMTIMER);
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
        return true;
    }
    else if(readyToSendBMM == false){
        return true;
    }
    else{
        return false;
    }
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
                FaultV = receiveArray[1];
                FaultC = receiveArray[2];
                FaultT = receiveArray[3];
                break;
            case BATTERY_VOLTS:
                for(j = 0;j<5;j++){
                    SubPackV[j] = receiveArray[j+1];
                }
                CellMaxVolt = receiveArray[7];
                CellMinVolt = receiveArray[8];
                break;
            case BATTERY_TEMPS:
                for(j = 0;j<5;j++){
                    SubPackT[j] = receiveArray[j+1];
                }
                CellMaxTemp = receiveArray[7];
                CellMinTemp = receiveArray[8];
                break;
            case BATTERY_POWER:
                current1 = receiveArray[1];
                current2 = receiveArray[2];
                current3 = receiveArray[3];
                break;
        }
        readyToSendBMM = true;
        SetTime(BMMTIMER);
        return true;
    } 
    else{
        return false;
    }
}

void ClearBMMTalk(){
    readyToSendBMM = true;
}


int GetVolt(unsigned char num){
    if(num == 6){
        return CellMaxVolt;
    }
    if(num == 7){
        return CellMinVolt;
    }
    else{
        return SubPackV[num];
    }
}

int GetTemp(unsigned char num){
    if(num == 6){
        return CellMaxTemp;
    }
    else if(num == 7){
        return CellMinTemp;
    }
    else{
        return SubPackT[num];
    }
}

int GetCurrent(unsigned  char num){
    if(num == 1){
        return current1;
    }
    else if(num == 2){
        return current2;
    }
    else if(num == 3){
        return current3;
    }
    else{
        return 0;
    }
}