#include "PDUComms.h"
#include "StateMachine.h"
#include <xc.h>
#include "PinDef.h"
#include "xc.h"

bool requestPDUData();
int constructPowerSet();
bool receiveCommPDU();
bool readyToSendPDU = true;
bool PDU_COMMS_ERROR = false;
bool powerChange();
extern struct powerStates powerSet;

bool requestPDUData() {
    if (((PDUTimer > BOARD_RESEND_MIN) && (readyToSendPDU)) || (PDUTimer > BOARD_TIMEOUT)) { // if (((PDUTimer > BOARD_RESEND_MIN) && (readyToSendPDU)) || (PDUTimer > BOARD_TIMEOUT)) {
        static int PDUErrorCounter = 0;
        if (!readyToSendPDU) {
            PDUErrorCounter++;
            if (PDUErrorCounter > 1) {
                PDUErrorCounter = 0;
                return false;
            }
        } else {
            PDUErrorCounter = 0;
            readyToSendPDU = false;
        }
        PDUTimer = 0;
        RS485_Direction2(TALK);
        ToSend(RESPONSE_ADDRESS, ECU_ADDRESS);
        if (powerChange())
            ToSend(POWER_RAILS, constructPowerSet());
        sendData(PDU_ADDRESS);
    }
    return true;
}

bool receiveCommPDU() {
    if (receiveData()) {
        if (receiveArray[RESPONSE_ADDRESS] == PDU_ADDRESS) {
            readyToSendPDU = true;
            PDUTimer = 0;
            //INDICATOR ^= 1;
            return true;
        } else return false;
    } else return false;
}

bool powerChange() {
    static bool BMM, MCS, DDS, SAS;
    bool returnable = false;
    if (BMM != powerSet.BMM) {
        BMM = powerSet.BMM;
        returnable = true;
    }
    if (DDS != powerSet.DDS) {
        DDS = powerSet.DDS;
        returnable = true;
    }
    if (SAS != powerSet.SAS) {
        SAS = powerSet.SAS;
        returnable = true;
    }
    if (MCS != powerSet.MCS) {
        MCS = powerSet.MCS;
        returnable = true;
    }
    return returnable;
}

int constructPowerSet() {
    static int powerSettings = 0;
    if (powerSet.BMM) {
        powerSettings = powerSettings | 0x0001;
    } else
        powerSettings = powerSettings & 0xFFFE;
    if (powerSet.MCS) {
        powerSettings = powerSettings | 0x0002;
    } else
        powerSettings = powerSettings & 0xFFFD;
    if (powerSet.DDS) {
        powerSettings = powerSettings | 0x0004;
    } else
        powerSettings = powerSettings & 0xFFFB;
    if (powerSet.SAS) {
        powerSettings = powerSettings | 0x0008;
    } else
        powerSettings = powerSettings & 0xFFF7;
    return powerSettings;
}
