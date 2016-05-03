/*
 PDU Communications
    Authored by Zac Kilburn 6/2/2015
 */

#include <stdbool.h>
#include <xc.h>
#include "Communications.h"
#include "ADDRESSING.h"
#include "Functions.h"
//void processPowerRequest(int powerSet);
void respondECU();

void updateComms() {
    if (receiveData()) {
        Precharge(receiveArray[CHARGE]);
        SetCharger(1, receiveArray[CURRENT], receiveArray[VOLTAGE]);
        respondECU();
    }
}

/*
 
 *     //Charger Receive
#define CHARGE                  1
#define CURRENT                 2
#define VOLTAGE                 3
#define AVGCELL                 4
#define BMMFAULT                5
 
 */

void respondECU() {
    LATCbits.LATC5 = 1;
    ToSend(RESPONSE_ADDRESS, ECU_ADDRESS);
    ToSend(BMM_COMM_STATE, 1);
    Delay(5);

    sendData(BMM_ADDRESS);
    Delay(3);
    LATCbits.LATC5 = 0;
}