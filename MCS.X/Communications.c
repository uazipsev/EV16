#include "Communications.h"
#include "Timers.h"
#include "MotorControler.h"
#include "PinDef.h"
int throttleOut = 0, brakeOut = 0;
bool pendingSend = false;
bool portClosed = true;
//static bool started=false;

void commSafety();
void updateComms() {
    checkCommDirection();
    
    //If a new packet has arrived
    if (receiveData()) {
        
        static bool carActive = false; 
        //If the packet says that the car should be active
        //INDICATOR ^= 1;
        if (receiveArray[OUTPUT_ACTIVE]||carActive) {
            //if we havent made a record of this being active yet
            if(!carActive){
                //reset the bootTimer to 0
                bootTime=0;   
                //Enable the motor
                MotorMode(set);
                //Store a flag that the car has been processed as active
                carActive=receiveArray[OUTPUT_ACTIVE];
            }
            else if(receiveArray[OUTPUT_ACTIVE]){
                //flag for timerOverride after timer completes
                 
                    MotorMode(run);
                    
                    if (throttleOut != receiveArray[THROTTLE_OUTPUT]) {
                        //INDICATOR ^= 1;
                        throttleOut = receiveArray[THROTTLE_OUTPUT];
                        SetSpeed(throttleOut);
                   }
                        
                    //if the current output is not what we received, set it correctly 
                    if (brakeOut != receiveArray[BRAKE_OUTPUT]) {
                        brakeOut = receiveArray[BRAKE_OUTPUT];
                        SetRegen(brakeOut);
                    }
                //}
            }
        }
        //else carActive is false
        else{
            //if brake is non-zero, wipe it
            MotorMode(stoping);
            //Turn of motor contoller
            //MotorDisable();
            carActive=false;
            //Relay control.
            //LATAbits.LATA0=0;
            bootTime=0;
            
        }
        talkTime = 0;
        safetyTime = 0;
        pendingSend = true;
    }
    
    
    //Control the RS485 Direction pin based on time and sending
    if (pendingSend && portClosed && talkTime > 5) {
        talkTime = 0;
        portClosed = false;
        RS485_1_Port = TALK;
        
    }
    
    
    //Respond to the ECU when the portHas been open for a short time
    if (pendingSend && talkTime > 1 && !portClosed) {
        talkTime = 0;
        respondECU();
        pendingSend = false;
    }
    
    
    //Provide safety timer
    commSafety();
}

//If the safety timer overruns 200 then shut off outputs and set DACs to 0
void commSafety() {
    if (safetyTime > 1000) {
        MotorMode(stoping);
    }
}
//Shoot a packet to the ECU
void respondECU() {
    ToSend(RESPONSE_ADDRESS, MCS_ADDRESS);
    sendData(ECU_ADDRESS);
    talkTime = 0;
}

void checkCommDirection() {
    //you have finished send and time has elapsed.. start listen
    if (Transmit_stall && (talkTime > 5) && (RS485_1_Port == TALK)) {
        RS485_1_Port = LISTEN;
        portClosed = true;
    }
}
