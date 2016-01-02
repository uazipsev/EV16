#include "SlaveCommunications.h"
#include "PinDef.h"
#define LOW_VOLTAGE 2000
#define LOW_VOLTAGE_FLAG 1
#define HIGH_TEMPERATURE 200
#define HIGH_TEMPERATURE_FLAG 2
#define COMMUNICATIONS_FAULT 3

int faultingBattery;
void sendSlavePacket(int slave);
int BVolts[NUMSLAVES][BATTPERSLAVE];
int BTemps[NUMSLAVES][TEMPPERSLAVE];
int faultCount[NUMSLAVES];
extern int faultFlag;
bool pendingSend1 = true, portTalk = false;
void updateSlaveCommunications();
void checkSlaveCommDirection();

void updateSlaveCommunications() {
    static int slaveaddr = 1;

    if (pendingSend1 && (slaveTime > 15) && !portTalk) {
        RS485_SLAVE_Port = !TALK;
        RS485_SLAVE_Port1 = !TALK;
        portTalk = true;
    }
    if (pendingSend1 && (slaveTime > 17) && portTalk) {
        sendSlavePacket(slaveaddr);
        pendingSend1 = false;
        slaveTime = 0;
    }


    if (receiveData1()) {
        INDICATOR = !INDICATOR;
        static bool wrongReturn = false;
        //Received when expecting it
        //        if (!pendingSend1) {
        if (slaveaddr == receiveArray1[RESPONSE_ADDRESS]) {
            //----------------- Handle the faulting -----------------
            if (receiveArray1[BATTERYFAULT]) {
                faultCount[slaveaddr - 1] = NUM_FAILS_TO_FAULT + 1;
            }
            faultCount[slaveaddr - 1] = 0;
            wrongReturn = false;
            //-----------------   Store the data  -----------------
            int i = 0;
            for (i = 0; i < BATTPERSLAVE; i++) {
                BVolts[receiveArray1[RESPONSE_ADDRESS] - 1][i] = receiveArray1[BATTERYV + i];
                if (BVolts[receiveArray1[RESPONSE_ADDRESS] - 1][i] < LOW_VOLTAGE) {
                    faultFlag = LOW_VOLTAGE_FLAG;                    
                    faultingBattery=((slaveaddr-1)* BATTPERSLAVE) + i;
                }
            }
            for (i = 0; i < BATTPERSLAVE; i++) {
                BTemps[receiveArray1[RESPONSE_ADDRESS] - 1][i] = receiveArray1[BATTERYT + i];
                if (BTemps[receiveArray1[RESPONSE_ADDRESS] - 1][i] > HIGH_TEMPERATURE) {
                    faultFlag = HIGH_TEMPERATURE_FLAG;
                    faultingBattery=((slaveaddr-1)* BATTPERSLAVE) + i;
                }
            }
            //Increment to the next slave
//            if (slaveaddr < NUMSLAVES1) {
//                slaveaddr++;
//            } else if (slaveaddr == NUMSLAVES1) {
//                slaveaddr++;
//                //send to slave set 2
//                S1 = 1;
//            } else if (slaveaddr < NUMSLAVES) {
//                slaveaddr++;
//            } else {
//                slaveaddr = 1;
//                //Back to slave set 1
//                S1 = 0;
//            }
            if(slaveaddr < NUMSLAVES1)
                slaveaddr++;
            else
                slaveaddr=1;
            //            }//Else you heard from the wrong address -- try a resend
            //            else if (!wrongReturn) {
            //                wrongReturn = true;
            //                pendingSend1 = true;
            //            } else {
            //                //Addressing issue (twice you heard from the wrong address)
            //                slaveaddr++;
            //                wrongReturn = false;
            //                //FAULT?
            //            }

            slaveTime = 0;
            pendingSend1 = true;
        }
        //else {
        //            //Received when not expecting it
        //            //FAULT?
        //        }
    } else {
        //You didnt receive after sending
        if (!pendingSend1) {
            if (slaveTime > 200) { //if timed out
                slaveTime = 0; //reset timer
                pendingSend1 = true; //set to send to the next slave

                faultCount[slaveaddr - 1]++;
                if (faultCount[slaveaddr - 1] >= NUM_FAILS_TO_FAULT) {
                    //FAULT?
                    int i = 0;
                    for (i = 0; i < BATTPERSLAVE; i++) { //wipe current slave data to indicate a loss
                        //BVolts[slaveaddr - 1][i] = 0;
                        //BTemps[slaveaddr - 1][i] = 0;
                    }
                    faultFlag=COMMUNICATIONS_FAULT;
                    faultingBattery=slaveaddr;
                }
                //Increment to the next slave
//                if (slaveaddr < NUMSLAVES1) {
//                    slaveaddr++;
//                } else if (slaveaddr == NUMSLAVES1) {
//                    slaveaddr++;
//                    //send to slave set 2
//                    S1 = 1;
//                } else if (slaveaddr < NUMSLAVES) {
//                    slaveaddr++;
//                } else {
//                    slaveaddr = 1;
//                    //Back to slave set 1
//                    S1 = 0;
//                }
            if(slaveaddr <  NUMSLAVES1)
                slaveaddr++;
            else
                slaveaddr=1;
            }
        }
    }

}

void sendSlavePacket(int slave) {
    slaveTime = 0;
    ToSend1(RESPONSE_ADDRESS, BMM_ADDRESS);
    sendData1(slave);
}

void checkSlaveCommDirection() {
    //you have finished send and time has elapsed.. start listen
    if (Transmit_stall1 && (slaveTime > 3) && ((RS485_SLAVE_Port == !TALK) || (RS485_SLAVE_Port1 == !TALK)) && !pendingSend1 && portTalk) {
        RS485_SLAVE_Port = !LISTEN;
        RS485_SLAVE_Port1 = !LISTEN;
        portTalk = false;
    }
}