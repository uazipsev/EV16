/*
 PDU Communications


    Authored by Zac Kilburn 6/2/2015



 */

#include <stdbool.h>
#include <xc.h>
#include "Communications.h"
#include "ADDRESSING.h"
#include "Functions.h"
#include "PDU.h"

void processPowerRequest(int powerSet);
void respondECU();

void updateComms() {
    if (receiveData()) {
        static int previousPowerState;
        if (previousPowerState != receiveArray[POWER_RAILS]) {
            previousPowerState = receiveArray[POWER_RAILS];
            processPowerRequest(previousPowerState);
        }
        respondECU();
    }
}


void processPowerRequest(int powerSet) {

    if (powerSet & 0x01) EnableSlavePower(BMM, ON);
    else EnableSlavePower(BMM, OFF);
    if (powerSet & 0x02) EnableSlavePower(MCS, ON);
    else EnableSlavePower(MCS,OFF);
    if (powerSet & 0x04) EnableSlavePower(DDS,ON);
    else EnableSlavePower(DDS,OFF);
    if(powerSet & 0x08) EnableSlavePower(SAS,ON);
    else EnableSlavePower(SAS,OFF);
    if(powerSet & 0x10) EnableSlavePower(TSS, ON);
    else EnableSlavePower(TSS,OFF);
    Update();
}

unsigned int FaultsCollector() {
    unsigned int sendVal = 0;
    int i = 0;
    for (i = 0; i < 5; i++) {
        sendVal = sendVal | ((GetPDUFault(i)&0x01) << i);
    }
    return sendVal;
}

void respondECU() {
    LATCbits.LATC5 = 1;
    ToSend(RESPONSE_ADDRESS, PDU_ADDRESS);
    ToSend(1,FaultsCollector());
    Delay(5);
    sendData(ECU_ADDRESS);
    Delay(3);
    LATCbits.LATC5 = 0;
}