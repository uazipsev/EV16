/*
 PDU Communications
    Authored by Zac Kilburn 6/2/2015
 */

#include <stdbool.h>
#include <xc.h>
#include "Communications.h"
#include "ADDRESSING.h"
#include "Functions.h"
#include "FastTransfer.h"
#include "UART.h"
#include "mcc_generated_files/pin_manager.h"
char receiveArray[50];

void CommsStart(){
    begin(receiveArray, sizeof (receiveArray), ECU_ADDRESS, false, Send_put, Receive_get, Receive_available, Receive_peek);
    EUSART1_Initialize();
}

void updateComms() {
    if (receiveData()) {
        LED_Toggle();
        //Precharge(receiveArray[CHARGE]);
        //SetCharger(1, receiveArray[CURRENT], receiveArray[VOLTAGE]);
    }
}


/*******************************************************************
 * @brief           RespondChargerAsECU 
 * @brief           This fcn talks to the BMM as if it was the ECU but there is a dirrent data going across the buss now
 * @return          N/A
 * @note            We are responding with data like state and faults and charger data maybe?
 *******************************************************************/

void respondChargerAsECU() {
    RS485_Port = TALK;
    //ToSend(RESPONSE_ADDRESS, CHARGER_ADDRESS);
    ToSend(0, 1);// GetPowerState());
    ToSend(1, 3);// GetPowerState());
    //Delay(5);
    sendData(BMM_ADDRESS);
    Delay(3);
    RS485_Port = LISTEN;
}

/*******************************************************************
 * @brief           SetBMM
 * @brief           This puts the BMM into charger mode
 * @return          N/A
 * @note            We are waiting for the BMM to respond so we know its on :)
 *******************************************************************/

bool SetBMM() {
    RS485_Port = TALK;
    //ToSend(RESPONSE_ADDRESS, ECU_ADDRESS);
    ToSend(BMM_COMM_STATE, 7);
    //Delay(5);
    sendData(BMM_ADDRESS);
    Delay(3);
    RS485_Port = LISTEN;
    Delay(1000);
    if (receiveData()){
    //    LED_Toggle();
        return 0;
    }
    else return 1;
}