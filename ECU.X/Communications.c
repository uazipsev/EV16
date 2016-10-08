/*
 * File:   Communications.h
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015
 *
 * Handles all of the communications system updates and error checking
 * -- Each board has a turn being communicated with
 *      --If the board doesnt respond, several attemps will be made to retry
 *      --At the end of the communications train there is room to send an error code
 *      --Rs485 direction is automated with packet sends.
 *      --All timers are inside T1 interrupt.. implied approx milliseconds
 */


#include <xc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "PinDef.h"
#include "ADDRESSING.h"
#include "Communications.h"
#include "SASComms.h"
#include "MCSComms.h"
#include "DDSComms.h"
#include "PDUComms.h"
#include "BMMComms.h"
#include "SScomms.h"
#include "Timers.h"
#include "UART.h"
#include "UART1.h"
#include "UART2.h"
#include "UART3.h"
#include "horn.h"
#include "FastTransfer.h"
#include "FastTransfer1.h"
#include "FastTransfer3.h"
#include "Functions.h"
#include "DriverConfigs.h"

char x = 0;

unsigned int BoardTimeOutCounterBus1 = 0;
unsigned int BoardTimeOutCounterBus2 = 0;

enum bus1CommState {
    SAS_UPDATE = 0, DDS_UPDATE = 1, SS_UPDATE = 2, CHECK_STATE1 = 3, ERROR_STATE1 = 4, NUM_STATES1 = 5
};
enum bus1CommState commsBus1State = SAS_UPDATE;
    
enum bus2CommState {
    MCS_UPDATE = 0, BMM_UPDATE = 1,  PDU_UPDATE = 2, CHECK_STATE2 = 3, ERROR_STATE2 = 4, NUM_STATES2 = 5
};
enum bus2CommState commsBus2State = MCS_UPDATE;

struct commsStates {
    bool DDS;
    bool MCS;
    bool SAS;
    bool BMM;
    bool PDU;
    bool SS;
    int DDS_SEND;
    int MCS_SEND;
    int SAS_SEND;
    int BMM_SEND;
    int PDU_SEND;
    int SS_SEND;
};
struct commsStates comms;

void ComStart(){
    UART_init();
    UART1_init();
    UART2_init();
    UART3_init();   
    StartFastTransfer();
    StartFastTransfer1();
    StartFastTransfer3();
}
    
void updateComms() {
    bus1Update();
    //if(GetDriverEnabled()){  //prevents MCS and BMM from coming up....Stopping system boot 
        bus2Update();
    //}
    checkCommDirection();
    checkCommDirection1();
    Delay(5);
}

void bus1Update() {
    switch (commsBus1State) {
        case SAS_UPDATE:
            if (requestSASData()) {
                //INDICATOR ^= 1;
                if (receiveCommSAS()) {
                    comms.SAS = true;
                    commsBus1State++;
                    resetCommTimers();
                    
                }
                else{
                    BoardTimeOutCounterBus1++;
                    if(BoardTimeOutCounterBus1 > BOARD_TIMEOUT){
                        commsBus1State++;
                        BoardTimeOutCounterBus1 = 0;

                    }
                }
            }
             else {
                //FLAG ERROR ON SAS COMMS -- Move on
                comms.SAS = false;
                commsBus1State++;
                resetCommTimers();
            }
            break;
        case DDS_UPDATE:
            if (requestDDSData()) {
                if (receiveCommDDS()) {
                    comms.DDS = true;
                    commsBus1State++;
                    resetCommTimers();
                }
                else{
                    BoardTimeOutCounterBus1++;
                    if(BoardTimeOutCounterBus1 > BOARD_TIMEOUT){
                        commsBus1State++;
                        BoardTimeOutCounterBus1 = 0;

                    }
                }
            }
            else {
                    //FLAG ERROR ON DDS COMMS -- Move on
                    commsBus1State++;
                    resetCommTimers();
            }
            break;
        case SS_UPDATE:
            if (requestSSData()) {
                if (receiveCommSS()) {
                    comms.SS = true;
                    commsBus1State++;
                    resetCommTimers();
                }
                else{
                    BoardTimeOutCounterBus1++;
                    if(BoardTimeOutCounterBus1 > BOARD_TIMEOUT){
                        commsBus1State++;
                        BoardTimeOutCounterBus1 = 0;

                    }
                }
            }
            else {
                //comms.SS = false;
                commsBus1State++;
                resetCommTimers();
            }
            break;
        case CHECK_STATE1:
//            //Before continuing the comms, send to error state if something is wrong
//            if (DDS_COMMS_ERROR || SAS_COMMS_ERROR || PDU_COMMS_ERROR) {
//                commsBus1State = ERROR_STATE1;
//            } else
                //otherwise continue the normal comms update
                commsBus1State = SAS_UPDATE;
            break;
        case ERROR_STATE1:
            //sendErrorCode();
            commsBus1State = SAS_UPDATE;
            break;
        case NUM_STATES1:
            break;
    }
}

void checkCommDirection() {
    //you have finished send and time has elapsed.. start listen
    if (TXStallGet() && (GetTime(TALKTIME) > CLOSE_COMM_TIME)) {
        RS485_Direction1(LISTEN);
    }
}

void resetCommTimers() {
    SetTime(SASTIMER);
    SetTime(DDSTIMER);
    SetTime(SSTIMER);
    //PDUTimer = 0;
}

void RS485_Direction1(int T_L) {
    RS485_1_Direction = T_L;
    SetTime(TALKTIME);
}

void bus2Update() {
    switch (commsBus2State) {
        case MCS_UPDATE:
            if (requestMCSData()) {
                if (receiveCommMCS()) {
                    comms.MCS = true;
                    commsBus2State++;
                    SetTime(MCSTIMER);
                }
                else{            
                    BoardTimeOutCounterBus2++;
                    if(BoardTimeOutCounterBus2 > BOARD_TIMEOUT){
                        commsBus2State++;
                        BoardTimeOutCounterBus2 = 0;
                        comms.MCS = false;
                        ClearMCSTalk();
                        SetTime(MCSTIMER);
                        break;
                    }
                    else{
                        break;
                    }
                }
            } 
            else{
                //FLAG ERROR ON MCS COMMS -- Move on
                commsBus2State++;
                break;
            }
        case BMM_UPDATE:
            if(requestBMMData(x)){
                if(receiveCommBMM(x)){
                    //INDICATOR ^= 1;
                    comms.BMM = true;
                    commsBus2State++;
                    SetTime(BMMTIMER);
                    x++;
                    if(x>3){
                        x = 0;
                    }
                }
                else{
                    BoardTimeOutCounterBus2++;
                    if(BoardTimeOutCounterBus2 > BOARD_TIMEOUT){
                        //INDICATOR ^= 1;
                        commsBus2State++;
                        BoardTimeOutCounterBus2 = 0;
                        comms.BMM = false;
                        ClearBMMTalk();
                        SetTime(BMMTIMER);
                        break;
                    }
                    else{
                        break;
                    }
                }
            } 
            else {
                //FLAG ERROR ON MCS COMMS -- Move on
                commsBus2State++;
                break;
            }
        case PDU_UPDATE:       
            if (requestPDUData()) {
                if (receiveCommPDU()) {
                    comms.PDU = true;
                    commsBus2State++;
                    SetTime(PDUTIMER);
                }
                else{            
                    BoardTimeOutCounterBus2++;
                    if(BoardTimeOutCounterBus2 > BOARD_TIMEOUT){
                        commsBus2State++;
                        BoardTimeOutCounterBus2 = 0;
                        comms.PDU = false;
                        ClearPDUTalk();
                        SetTime(PDUTIMER);
                        break;
                    }
                    else{
                        break;
                    }
                }
            }
            else{
                //FLAG ERROR ON MCS COMMS -- Move on
                commsBus2State++;
                break;
            }
        case CHECK_STATE2:
//            if (MCS_COMMS_ERROR || BMM_COMMS_ERROR) {
//                commsBus2State = ERROR_STATE2;
//            } else
//                //otherwise continue the normal comms update
                commsBus2State = MCS_UPDATE;
            break;
        case ERROR_STATE2:
            //sendErrorCode2();
            commsBus2State = MCS_UPDATE;
            break;
        case NUM_STATES2:
            break;
    }
}

void checkCommDirection1() {
    //you have finished send and time has elapsed.. start listen
    if (TXStallGet1() && (GetTime(TALKTIME1) > 4)) { //5CLOSE_COMM_TIME
        RS485_Direction2(LISTEN);
    }
}

void resetCommTimers2() {
    


}

void RS485_Direction2(int T_L) {
    RS485_2_Direction = T_L;
    SetTime(TALKTIME1);
}

//Debug interface for printf
extern void Send_put2(unsigned char _data);
extern unsigned char Receive_get2(void);

char getch(void) {
    return Receive_get2();
}

void putch(char txData) {
    Send_put2(txData);
}

bool ComCheck(char device){
    if(device == MCSSTATE){
        return comms.MCS;
    }
    if(device == DDSSTATE){
        return comms.DDS;
    }
    if(device == SASSTATE){
        return comms.SAS;
    }
    if(device == BMMSTATE){
        return comms.BMM;
    }
    if(device == PDUSTATE){
        return comms.PDU;
    }
    else{
        return 0;
    }
}