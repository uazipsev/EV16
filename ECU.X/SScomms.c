#include "SScomms.h"
#include <stdbool.h>
#include "ADDRESSING.h"
#include "Timers.h"
#include "FastTransfer1.h"
#include "Communications.h"

bool readyToSendSS = 0;
int SSErrorCounter = 0;

bool HardFault[12];

int FaultsHigh = 0;
int FaultsLow = 0;

bool requestSSData() {
    if (((GetTime(SSTIMER) > BOARD_RESEND_MIN) && (readyToSendSS)) || (GetTime(SSTIMER) > BOARD_TIMEOUT)) {
        //static int SSErrorCounter = 0;
        if (!readyToSendSS) {
            SSErrorCounter++;
            if (SSErrorCounter > 1) {
                SSErrorCounter = 0;
                return false;
            }
        } else {
            readyToSendSS = false;
            SSErrorCounter = 0;
        }
        ToSend1(RESPONSE_ADDRESS, ECU_ADDRESS);
        RS485_Direction1(TALK);
        sendData1(SS_ADDRESS);
        SetTime(SSTIMER);
    }
    return true;

}

bool receiveCommSS() {
    if (receiveData1()) {
        if (ReceiveArray1Get(RESPONSE_ADDRESS) == SS_ADDRESS) {
            FaultsHigh = (unsigned char)ReceiveArray1Get(1);
            FaultsLow = (unsigned char)ReceiveArray1Get(2);
            readyToSendSS = true;
            SetTime(SSTIMER);
            return true;
        } else return false;
    } else return false;
}

int GetFaultChar(char val){
    if(val == 1){
        return FaultsHigh;
    }
    else{
        return FaultsLow;
    }
}

bool GetFaultBool(char val){
    switch(val){
        case ECU_FAULT:
            return ((FaultsHigh >> (ECU_FAULT-1))  & 0x01);
            break;
        case BOTS_FAULT:
            return ((FaultsHigh >> (BOTS_FAULT-1))  & 0x01);
            break;
        case AMD_FAULT:
            return ((FaultsHigh >> (AMD_FAULT-1))  & 0x01);
            break;
        case STOP_L_FAULT:
            return ((FaultsHigh >> (STOP_L_FAULT-1))  & 0x01);
            break;
        case STOP_R_FAULT:
            return ((FaultsHigh >> (STOP_R_FAULT-1))  & 0x01);
            break;
        case STOP_C_FAULT:
            return ((FaultsHigh >> (STOP_C_FAULT-1))  & 0x01);
            break;
        case IMD_FAULT:
            return ((FaultsHigh >> (IMD_FAULT-1))  & 0x01);
            break;
        case BPD_FAULT:
            return ((FaultsHigh >> (BPD_FAULT-1))  & 0x01);
            break;
        case TSMS_FAULT:
            return ((FaultsLow >> (TSMS_FAULT-9))  & 0x01);
            break;
        case IS_FAULT:
            return ((FaultsLow >> (IS_FAULT-9))  & 0x01);
            break;
        case AUX_FAULT:
            return ((FaultsLow >> (AUX_FAULT-9))  & 0x01);
            break;
    }
}


