/*
 PDU Communications
    Authored by Zac Kilburn 6/2/2015
 */

#include <stdbool.h>
#include <xc.h>
#include "Communications.h"
#include "ADDRESSING.h"
#include "Functions.h"

void updateComms() {
    if (receiveData()) {
        Precharge(receiveArray[CHARGE]);
        SetCharger(1, receiveArray[CURRENT], receiveArray[VOLTAGE]);
        respondChargerAsECU();
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

/*******************************************************************
 * @brief           RespondChargerAsECU 
 * @brief           This fcn talks to the BMM as if it was the ECU but there is a dirrent data going across the buss now
 * @return          N/A
 * @note            We are responding with data like state and faults and charger data maybe?
 *******************************************************************/

void respondChargerAsECU() {
    LATCbits.LATC5 = 1;
    ToSend(RESPONSE_ADDRESS, ECU_ADDRESS);
    ToSend(BMM_COMM_STATE, 1);
    Delay(5);
    sendData(BMM_ADDRESS);
    Delay(3);
    LATCbits.LATC5 = 0;
}

/*******************************************************************
 * @brief           SetBMM
 * @brief           This puts the BMM into charger mode
 * @return          N/A
 * @note            We are waiting for the BMM to respond so we know its on :)
 *******************************************************************/

bool SetBMM() {
    LATCbits.LATC5 = 1;
    ToSend(RESPONSE_ADDRESS, ECU_ADDRESS);
    ToSend(BMM_COMM_STATE, 1);
    Delay(5);
    sendData(BMM_ADDRESS);
    Delay(3);
    LATCbits.LATC5 = 0;
    Delay(100);
    if (receiveData()){
        return 0;
    }
    else return 1;
}