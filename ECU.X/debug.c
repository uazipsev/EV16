#include "debug.h"
#include <stdio.h>
#include "ADDRESSING.h"
#include "SlaveAddressing.h"
#include "Functions.h"

#define LOW_VOLTAGE_FLAG 1
#define HIGH_TEMPERATURE_FLAG 2
#define COMMUNICATIONS_FAULT 3


//SAS
#define THROTTLE_SANITY_CHECK 1
#define THROTTLE_BRAKE_CHECK  2

enum BMM {
    BATTERY_FAULT = 0,
    BATTERY_VOLTS = 1,
    BATTERY_TEMPS = 2,
    BATTERY_POWER = 3
};

struct commsStates {
    bool DDS;
    bool MCS;
    bool SAS;
    bool BMM;
    bool PDU;
    int DDS_SEND;
    int MCS_SEND;
    int SAS_SEND;
    enum BMM BMM_SEND;
    int PDU_SEND;
};
extern struct commsStates comms;
 extern unsigned int t1Raw, t2Raw, bRaw;
               extern int State_Value =0;
               extern int StateFault_Value=0;
enum debugStates debugState;
extern int DDS_FAULT_CONDITION, MCS_FAULT_CONDITION, SAS_FAULT_CONDITION, BMM_FAULT_CONDITION, PDU_FAULT_CONDITION, ECU_FAULT_CONDITION;
extern int faultingBattery;
extern int BMMADC[4];
extern int milliVolts[NUMSLAVES][BATTPERSLAVE];
extern int temps[NUMSLAVES][BATTPERSLAVE];
extern int current1, current2, bigVolts;
void handleDebugRequests();

int write(int handle, void *buffer, unsigned int len) {
    int i;
    switch (handle) {
        case 0: // handle 0 corresponds to stdout
        case 1: // handle 1 corresponds to stdin
        case 2: // handle 2 corresponds to stderr
        default:
            for (i = 0; i < len; i++)
                Send_put2(*(char*) buffer++);
    }
    return (len);
}

void handleDebugRequests() {
    static int lastDebugState = 0;
    static int batterySlaveNumberV;
    static int batterySlaveNumber;
    if (DebugTimer > 1000) {
        switch (debugState) {
            case NO_DEBUG:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                   // comms.BMM_SEND = BATTERY_FAULT;

                }
                break;
            case THROTTLE_BRAKE:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                    //comms.BMM_SEND = BATTERY_FAULT;
                }
                printf("\n-----Throttle Brake Raw Debug----\n");
                printf("Throttle1:      %d\n", t1Raw);
                printf("Throttle2:      %d\n", t2Raw);
                printf("Brake:          %d\n\n", bRaw);
                printf("\n-----Throttle Brake Signal Debug----\n");
                printf("Throttle1:      %d\n", throttle1);
                printf("Throttle2:      %d\n", throttle2);
                printf("Brake:          %d\n", brake);
                break;
            case BATTERY_DEBUG_VOLTS:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                    //comms.BMM_SEND = BATTERY_VOLTS;
                    batterySlaveNumberV = 0;
                }
                if (comms.BMM) {
                    printf("\n---Slave #%d Bat Voltage Info---\n", batterySlaveNumberV + 1);
                    printf("B1: %dV B2: %dV B3: %dV B4: %dV\n", milliVolts[batterySlaveNumberV][0], milliVolts[batterySlaveNumberV][1], milliVolts[batterySlaveNumberV][2], milliVolts[batterySlaveNumberV][3]);
                    printf("B5: %dV B6: %dV B7: %dV B8: %dV\n", milliVolts[batterySlaveNumberV][4], milliVolts[batterySlaveNumberV][5], milliVolts[batterySlaveNumberV][6], milliVolts[batterySlaveNumberV][7]);
                    printf("B9: %dV B10:%dV                \n", milliVolts[batterySlaveNumberV][8], milliVolts[batterySlaveNumberV][9]);
                    if (batterySlaveNumberV < NUMSLAVES - 1) batterySlaveNumberV++;
                    else batterySlaveNumberV = 0;
                } else
                    printf("\nComms with BMM are no longer online\n");

                break;
            case BATTERY_DEBUG_TEMPS:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                    //comms.BMM_SEND = BATTERY_TEMPS;
                    batterySlaveNumber = 0;
                }
                printf("\n----Slave #%d Bat Temp Info---- \n", batterySlaveNumber + 1);
                printf("B1: %dF B2:  %dF B3:  %dF B4:  %dF\n", temps[batterySlaveNumber][0], temps[batterySlaveNumber][1], temps[batterySlaveNumber][2], temps[batterySlaveNumber][3]);
                printf("B5: %dF B6:  %dF B7:  %dF B8:  %dF\n", temps[batterySlaveNumber][4], temps[batterySlaveNumber][5], temps[batterySlaveNumber][6], temps[batterySlaveNumber][7]);
                printf("B9: %dF B10: %dF                  \n", temps[batterySlaveNumber][8], temps[batterySlaveNumber][9]);
                if (batterySlaveNumber < NUMSLAVES - 1) batterySlaveNumber++;
                else batterySlaveNumber = 0;

                break;
            case BATTERY_DEBUG_POWER:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                    //comms.BMM_SEND = BATTERY_POWER;
                }
                printf("\n----BMM Power Signal Debug----\n");
                printf("BMMADC[0]:      %d\n", BMMADC[0]);
                printf("BMMADC[1]:      %d\n", BMMADC[1]);
                printf("BMMADC[2]:      %d\n", BMMADC[2]);
                printf("BMMADC[3]:      %d\n", BMMADC[3]);
                //                printf("Current Pack 1:  %d\n", current1);
                //                printf("Current Pack 2:  %d\n", current2);
                //                printf("HV pack voltage: %d\n", bigVolts);
                break;
            case FAULT_RECOVERY:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                    comms.BMM_SEND = BATTERY_FAULT;
                }
                printf("\n----Fault Reporting/Recovery Mode----\n");
                if (MCS_FAULT_CONDITION) {
                    printf("\n----MCS FALUT----\n");
                }
                if (BMM_FAULT_CONDITION) {
                    switch (BMM_FAULT_CONDITION) {
                        case 0:
                            break;
                        case LOW_VOLTAGE_FLAG:
                            printf("Low Voltage Fault on BMM\n");
                            printf("Faulting Battery is: %d\n", faultingBattery);
                            break;
                        case HIGH_TEMPERATURE_FLAG:
                            printf("High Temperature Fault on BMM\n");
                            printf("Faulting Battery is: %d\n", faultingBattery);
                            break;
                        case COMMUNICATIONS_FAULT:
                            printf("Communications Fault on BMM\n");
                            printf("Faulting Module is: %d\n", faultingBattery);
                            break;
                    }
                }
                if (SAS_FAULT_CONDITION) {
                    printf("\n----SAS FALUT----\n");
                    switch (SAS_FAULT_CONDITION){
                        case THROTTLE_SANITY_CHECK:

                            break;
                        case THROTTLE_BRAKE_CHECK:
                            break;
                    }
                }
                if (DDS_FAULT_CONDITION) {
                    printf("\n----DDS FALUT----\n");

                }
                if (PDU_FAULT_CONDITION) {
                    printf("\n----PDU FALUT----\n");

                }
                if (ECU_FAULT_CONDITION) {
                }
                break;
            case NUM_DEBUG_STATES:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                break;
            case Find_State:
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                State_Value=getstate();
                printf("State On ECU State Machine\n");
                printf("The Current State Is %d\n", State_Value);
                break;
            case State_fault:
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                StateFault_Value=getstatefault();
                printf("Fault Value On State Machine\n");
                printf("The Current Fault On The State Machine Is %d\n", StateFault_Value);
                break;
            case Reset:
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("The reset value is %d\n", GetResetValue());
                break;
        }
        DebugTimer = 0;
    }
    //Generic packet format is
    //[0x06 0x85 0x01 0x09 0x03 0x00 0x01 0x00 0xC4]
    if (receiveData2()) {
        //          sendData2(DEBUG_ADDRESS);     ToSend2(RESPONSE_ADDRESS, ECU_ADDRESS);
        //
        if (debugState < NUM_DEBUG_STATES - 1)
            debugState++;
        else debugState = 0;
    }
}