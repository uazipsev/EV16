#include "Communications.h"
#include "Timers.h"
#include "MotorControler.h"
#include "PinDef.h"
#include "FastTransfer.h"

int throttleOut = 0, brakeOut = 0;
bool pendingSend = false;
bool portClosed = true;
static bool started=false;

void commSafety();
void updateComms() {
    checkCommDirection();
    
    //If a new packet has arrived
    if (receiveData()){
       
        SetCarMode(receiveArray[OUTPUT_ACTIVE]);
        SetSpeed(receiveArray[THROTTLE_OUTPUT]);
        SetRegen(receiveArray[BRAKE_OUTPUT]);

        ClearTime(TALKTIME);
        ClearTime(SAFETYTIME);
        pendingSend = true;
    }
    
    //Control the RS485 Direction pin based on time and sending
    if (pendingSend && portClosed && GetTime(TALKTIME) > 5) {
        ClearTime(TALKTIME);
        portClosed = false;
        RS485_1_Port = TALK;
    }


    //Respond to the ECU when the portHas been open for a short time
    if (pendingSend && GetTime(TALKTIME) > 1 && !portClosed) {
        ClearTime(TALKTIME);
        respondECU();
        pendingSend = false;
    }
    //Provide safety timer
    commSafety();
}

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
    if (Transmit_stall && (GetTime(TALKTIME) > 5) && (RS485_1_Port == TALK)) {
        RS485_1_Port = LISTEN;
        portClosed = true;
    }
}
