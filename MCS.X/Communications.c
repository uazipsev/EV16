#include "Communications.h"
#include "Timers.h"
#include "MotorControler.h"
#include "PinDef.h"
#include "FastTransfer.h"

int throttleOut = 0, brakeOut = 0;
bool pendingSend = false;
bool portClosed = true;
//static bool started =false;

void commSafety();
void updateComms() {
    checkCommDirection();
    
    //If a new packet has arrived
    if (receiveData() && !pendingSend) {
       
        SetCarMode(ReceiveArrayGet(OUTPUT_ACTIVE));
        SetSpeed(ReceiveArrayGet(THROTTLE_OUTPUT));
        SetRegen(ReceiveArrayGet(BRAKE_OUTPUT));
        //SetDirection(ReceiveArrayGet(DIR_ACTIVE));

        ClearTime(TALKTIME);
        //ClearTime(SAFETYTIME);
        pendingSend = true;
    }
    
    //Control the RS485 Direction pin based on time and sending
    else if (pendingSend && portClosed && (GetTime(TALKTIME) > 120)) {
        ClearTime(TALKTIME);
        portClosed = false;
        RS485_1_Port = TALK;
    }


    //Respond to the ECU when the portHas been open for a short time
    else if (pendingSend && GetTime(TALKTIME) > 5 && !portClosed) {
        ClearTime(TALKTIME);
        respondECU();
        pendingSend = false;
    }
    //Provide safety timer
    //commSafety();
}

/*
 
     checkCommDirection();
    //LED ^= 1;
    if (receiveData() && !pendingSend) {
        //LED ^= 1;
        talkTime = 0;
        pendingSend = true;
        portClosed=true;
    }
    else if(pendingSend && portClosed && talkTime > 5){
        talkTime=0;
        portClosed=false;
        RS485_1_Port = TALK;
    }
    else if (pendingSend && talkTime > 5 && !portClosed) {
        talkTime = 0;
        prepAndSendData();
        pendingSend = false;
    }  
 
 
 */

//If the safety timer overruns 200 then shut off outputs and set DACs to 0
void commSafety() {
    if (GetTime(SAFETYTIME) > 1000) {
        //SetMotor(0, 1);
        //SetRegen(0);
        //Motor controller 12V
        //LATAbits.LATA10=0;
        //Relay for DAC
        //LATAbits.LATA0=0;
    }
}

//Shoot a packet to the ECU
void respondECU() {
    ToSend(RESPONSE_ADDRESS, MCS_ADDRESS);
    sendData(ECU_ADDRESS);
    ClearTime(TALKTIME);
}

void checkCommDirection() {
    //you have finished send and time has elapsed.. start listen
    if (Transmit_stall && (GetTime(TALKTIME) > 10) && (RS485_1_Port == TALK) && !pendingSend && !portClosed) {
        RS485_1_Port = LISTEN;
        portClosed = true;
    }
}

/*
 
     if (Transmit_stall && (talkTime > 10) && (RS485_1_Port == TALK) && !pendingSend && !portClosed) {
        RS485_1_Port = LISTEN;
        portClosed=true;
    }
 
 */