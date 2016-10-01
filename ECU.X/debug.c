/*******************************************************************
 * @brief           Debug.c
 * @brief           This lib runs our CLI
 * @return          N/A
 * @note            Created by - Zac and Rick Uses data from around the car to display info on the CLI
 *******************************************************************/
#include "debug.h"
#include <stdio.h>
#include "ADDRESSING.h"
#include "SlaveAddressing.h"
#include "Functions.h"
#include "UART2.h"
#include "StoppedState.h"
#include "EEprom.h"
#include "Timers.h"
#include "PinDef.h"
#include "BMMComms.h"
#include "FastTransfer.h"
#include "FastTransfer1.h"
#include "FastTransfer3.h"
#include "SASComms.h"
#include "ThrottleBrakeControl.h"
#include <errno.h>
#include "SScomms.h"

#define LOW_VOLTAGE_FLAG 1
#define HIGH_TEMPERATURE_FLAG 2
#define COMMUNICATIONS_FAULT 3

double augment[10] = {0.01,-0.04,0.02,0.04,-0.05,0};
int k = 0;

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
               int State_Value =0;
               int StateFault_Value=0;
enum debugStates debugState;
extern int DDS_FAULT_CONDITION, MCS_FAULT_CONDITION, SAS_FAULT_CONDITION, BMM_FAULT_CONDITION, PDU_FAULT_CONDITION, ECU_FAULT_CONDITION;
extern int faultingBattery;
extern int BMMADC[4];
extern int current1, current2, bigVolts;
void handleDebugRequests();

bool VerboseEn = 1;

bool Menudisplay = 0;
char FunctionDataGrab = 0;
char DataIn = 0;
int Menu = 0;
int i = 0;
int SubMenu = 0;
bool FuncIn = 0;
bool SubMenuActive = false;
bool MenuClear = false;
int Data = 0;
char DataHold[10];
char TimeOutMenu = 0;
char next = 0;

/*******************************************************************
 * @brief           write
 * @brief           WTF
 * @return          returns length (how many chars) of data
 * @note            I have no idea what the fuck this is for...may be removed (printf maybe?)
 *******************************************************************/
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

/*******************************************************************
 * @brief           handleDebugRequests
 * @brief           Handels CLI system data   
 * @return          N/A
 * @note            The fcn monitors USART3 for activity and responds.
 *                  The fcn also sends repeat data for viewing.
 *******************************************************************/
void handleDebugRequests() {
    static int lastDebugState = 0;
    if (GetTime(DEBUGTIME) > 1000) {
        switch (debugState) {
            case NO_DEBUG:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;

                }
                break;
            case THROTTLE:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("\n-----Throttle Brake Raw Debug----\n");
                printf("Throttle1:      %d\n", GetSASRaw(GETSAST1RAW));
                printf("Throttle2:      %d\n", GetSASRaw(GETSAST2RAW));
                printf("\n-----Throttle Brake Signal Debug----\n");
                printf("Throttle1:      %d\n",  GetThrottleBrakeValue(GETSAST1));
                printf("Throttle2:      %d\n",  GetThrottleBrakeValue(GETSAST2));
                break;
            case BRAKE:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("\n---- Brake Raw Debug----\n");
                printf("Brake1:          %d\n\n", GetSASRaw(GETSASB1RAW));
                printf("Brake2:          %d\n\n", GetSASRaw(GETSASB2RAW));
                printf("\n-----Throttle Brake Signal Debug----\n");
                printf("Brake1:          %d\n",  GetThrottleBrakeValue(GETSASB1));
                printf("Brake2:          %d\n",  GetThrottleBrakeValue(GETSASB2));
                break;
            case BATTERY_DEBUG_VOLTS:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }     
                    printf("\n Battery info:\n");
                    printf("\n Battery Cell high V = %d:\n",GetVolt(6));
                    printf("\n Battery Cell low V = %d:\n",GetVolt(7));
                    //printf("\n Battery STD DIV = %f:\n",0.067+augment[k]);
                    //printf("\n Current A %3.02f B %3.02f C %3.02f \n", 0.00, 0.0, 0.00);
                    printf("\n Temp MAX %d  F MIN %d F AVG %d F",GetTemp(6), GetTemp(7), GetTemp(0));
                    k++;
                    if(k > 5){
                        k = 0;
                    }
                break;
            case BATTERY_DEBUG_TEMPS:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
//                printf("\n----Slave #%d Bat Temp Info---- \n", batterySlaveNumber + 1);
//                printf("B1: %dF B2:  %dF B3:  %dF B4:  %dF\n", temps[batterySlaveNumber][0], temps[batterySlaveNumber][1], temps[batterySlaveNumber][2], temps[batterySlaveNumber][3]);
//                printf("B5: %dF B6:  %dF B7:  %dF B8:  %dF\n", temps[batterySlaveNumber][4], temps[batterySlaveNumber][5], temps[batterySlaveNumber][6], temps[batterySlaveNumber][7]);
//                printf("B9: %dF B10: %dF                  \n", temps[batterySlaveNumber][8], temps[batterySlaveNumber][9]);
//                if (batterySlaveNumber < NUMSLAVES - 1) batterySlaveNumber++;
//                else batterySlaveNumber = 0;

                break;
            case BATTERY_DEBUG_POWER:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("\n----BMM Power Signal Debug----\n");
                printf("Current Pack 1:  %d\n", GetCurrent(1));
                printf("Current Pack 2:  %d\n", GetCurrent(2));
                printf("Current Pack 3:  %d\n", GetCurrent(3));
                break;
            case FAULT_RECOVERY:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
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
                            printf("\n----THROTTLE_SANITY_CHECK----\n");
                            break;
                        case THROTTLE_BRAKE_CHECK:
                            printf("\n----THROTTLE_BRAKE_CHECK----\n");
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
                StateFault_Value=getstatefault();
                printf("State Machine Fault = %d\n", StateFault_Value);
                break;
            case SS_INFO:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                char n = 0;
                printf("The faults = ");
                for(n = 0;n<11;n++){
                    if(GetFaultBool(n)){
                        printf("x ");
                    }
                    else{
                        printf("O ");
                    }
                }
                printf("\n");
                break;
            case FIND_STATE:
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                State_Value=getstate();
                printf("State On ECU State Machine\n");
                printf("The Current State Is %d\n", State_Value);
                break;
            case FAULT:
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }

                break;
            case Reset:
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("The reset value is %d\n", GetResetValue());
                break;
            case comm_on:
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("Comms:\n");
                if(!comms.BMM){
                    printf("No BMM comms\n");
                }
                if(!comms.DDS){
                    printf("No DDS comms\n");
                }
                if(!comms.SAS){
                    printf("No SAS comms\n");
                }
                if(!comms.MCS){
                    printf("No MCS comms\n");
                }
                break;
            case buttons:
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                int i;
                for(i = 0;i<8;i++){
                    printf("Button %d : %d", i,buttonArray[i]);
                }
                break;
            case error_rate:
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                ClearScreen();
                printf("Align Error B1 %u \n",alignError());
                printf("CRC Error B1 %u \n",CRCError());
                printf("Address Error B1 %u \n",addressError());
                printf("Data Error B1 %u \n",dataAddressError());
                printf("Align Error B2 %u \n",alignError1());
                printf("CRC Error B2 %u \n",CRCError1());
                printf("Data Address Error B2 %u \n",addressError1());
                printf("Data Error B2 %u \n",dataAddressError1());
                printf("Align Error B3 %u \n",alignError3());
                printf("CRC Error B3 %u \n",CRCError3());
                printf("Address Error B3 %u \n",addressError3());
                printf("Data Error B3 %u \n",dataAddressError3());
                break;
                
        }
        if(Menudisplay){
            ClearScreen();
            MenuPrint(Menu,SubMenu);
        }
        if(MenuClear){
            ClearScreen();
            
            MenuPrint(Menu,SubMenu);
            MenuClear = false;
        }
        SetTime(DEBUGTIME);
    }

    if (Receive_available2()) {
        if(!FunctionDataGrab){
            DataIn = Receive_get2();
            if(VerboseEn){
                printf("%c",DataIn);
            }
            if(DataIn == 'b'){      
                debugState = NO_DEBUG;
                if((SubMenuActive == true) && (SubMenu > 0)){
                    SubMenu = 0;
                    //SubMenuActive = false;
                }
                else if((SubMenuActive == true) && (SubMenu == 0)){
                    SubMenuActive = false;
                    Menu = 0;
                }

            }
            else if(SubMenuActive == false){
                Menu = DataIn - 48;
            }
            else if(SubMenuActive == true){
                SubMenu = DataIn - 48; 
            }
            Menudisplay = 1;
        }
        if(FunctionDataGrab){
            //Driver Setting
            if(FunctionDataGrab == 4){
                //Get data of the pipe
                DataHold[i] = Receive_get2();
                SetDriver(DataHold[0]-48);
                TimeOutSet(3000);
                SubMenu = 0;
                //ClearScreen();
                //We are done grabbing data off the pipeline
                FunctionDataGrab = false;
                i = 0;
            }
            //Throttle Precent
            if(FunctionDataGrab == 1){
                //Get data of the pipe
                DataHold[i] = Receive_get2();
                i++;
                //We are looking for x chars...
                if(i>1){
                    //We are done grabbing data off the pipeline
                    FunctionDataGrab = false;
                    i = 0;
                }
            }
            //Throttle Setpoint
            else if(FunctionDataGrab == 2){
                //Get data of the pipe
                DataHold[i] = Receive_get2();
                i++;
                //We are looking for x chars...
                if(i>1){
                    //We are done grabbing data off the pipeline
                    FunctionDataGrab = false;
                    i = 0;
                }
            }
            //Brake Setpoint
            else if(FunctionDataGrab == 3){
                //Get data of the pipe
                DataHold[i] = Receive_get2();
                i++;
                //We are looking for x chars...
                if(i>1){
                    //We are done grabbing data off the pipeline
                    FunctionDataGrab = false;
                    i = 0;
                }
            }
            //Add Driver 
            else if(FunctionDataGrab == 5){
                //Get data of the pipe
                //Get driver name 
                if(next == 0){ 
                    DataHold[i] = Receive_get2();
                    i++;
                    //We are looking for 3 chars...
                    if(i>2){
                        //Print Driver name for sanity
                        printf("Driver name = %c%c%c\n",DataHold[0],DataHold[1],DataHold[2]);
                        //We have data and are ready to save it to the car
                        NewDriverNameChar(DataHold[0], 0);
                        NewDriverNameChar(DataHold[1], 1);
                        NewDriverNameChar(DataHold[2], 2);
                        //We are done grabbing data off the pipeline
                        printf("|----Max Throttle---|\n");
                        printf("|------0 to 100-----|\n");
                        printf("|-Must Be 3 digits--|\n");

                        //FunctionDataGrab = 5;
                        i = 0;
                        next++;
                    }
                }
                //Get Max throttle
                else if(next == 1){ 
                    printf("i = %d",i);
                    DataHold[i] = Receive_get2();

                    i++;
                    //We are looking for 3 chars...
                    if(i>2){
                        //convert it to a int
                        sscanf(DataHold, "%d", &Data);
                        //Print value for sanity
                        printf("Driver Max Throttle = %d\n",Data);
                        //We have data and are ready to save it to the car
                        NewDriverMaxThrottle(Data);
                        printf("|-----Max Regen-----|\n");
                        printf("|------0 to 100-----|\n");
                        printf("|-Must Be 3 digits--|\n");

                        FunctionDataGrab = 5;
                        i = 0;
                        next++;
                    }
                }
                //Get master Regen 
                else if(next == 2){ 
                    DataHold[i] = Receive_get2();
                    i++;
                    //We are looking for 3 chars...
                    if(i>2){
                        //convert it to a int
                        sscanf(DataHold, "%d", &Data);
                        //Print value for sanity
                        printf("Driver Max Regen = %d\n",Data);
                        NewDriverMaxMaxRegen(Data);
                        
                        printf("|----LowBatCutoff---|\n");
                        printf("|------0 to 100-----|\n");
                        printf("|-Must Be 3 digits--|\n");

                        FunctionDataGrab = 5;
                        i = 0;
                        next++;
                    }
                }
                //Get Bat low
                else if(next == 3){ 
                    DataHold[i] = Receive_get2();
                    i++;
                    //We are looking for 3 chars...
                    if(i>2){
                        //convert it to a int
                        sscanf(DataHold, "%d", &Data);
                        //Print value for sanity
                        printf("Driver Low Battery = %d\n",Data);
                        NewDriverLowBatCutoff(Data);
                        //We are done grabbing data off the pipeline
                        printf("|--------Ramp-------|\n");
                        printf("|------0 to 100-----|\n");
                        printf("|-Must Be 3 digits--|\n");

                        FunctionDataGrab = 5;
                        i = 0;
                        next++;
                    }
                }
                //Get driver ramp
                else if(next == 4){ 
                    DataHold[i] = Receive_get2();
                    i++;
                    //We are looking for 3 chars...
                    if(i>2){
                        //convert it to a int
                        sscanf(DataHold, "%d", &Data);
                        //Print value for sanity
                        printf("Driver Ramp = %d\n",Data);
                        NewDriverRamp(Data);
                        //We are done grabbing data off the pipeline
                        printf("|---Fault Allowed---|\n");
                        printf("|------Debug En-----|\n");
                        printf("|RegenInput & FW/RV-|\n");
                        printf("What faults are allowed?\n");

                        FunctionDataGrab = 5;
                        i = 0;
                        next++;
                    }
                }
                //Get Faults allowed
                else if(next == 5){ 
                    DataHold[0] = Receive_get2();
                    //Get data array to int
                    sscanf(DataHold, "%d", &Data);
                    //We have data and are ready to save it to the car
                    printf("Faults allowed = %d\n",Data);
                    NewDriverFalt(Data);
                    next++;
                    //We are done grabbing data off the pipeline
                    FunctionDataGrab = 5;
                    //TimeOutSet(1500);
                    printf("Debugging allowed? (1 = yes 0 = no\n");
                    i = 0;
                }
                //Get Debug allowed
                else if(next == 6){ 
                    DataHold[0] = Receive_get2();
                    //Get data array to int
                    sscanf(DataHold, "%d", &Data);
                    //We have data and are ready to save it to the car
                    printf("Debugging = ");
                    if(Data == 1){
                        printf("yes\n");
                        NewDriverDebugEn(true);
                    }
                    else{
                        printf("no\n");
                        NewDriverDebugEn(false);
                    }
                    next++;
                    //We are done grabbing data off the pipeline
                    FunctionDataGrab = 5;
                    printf("FW-RV allowed? (1 = yes 0 = no)\n");
                    //TimeOutSet(1500);
                    i = 0;
                }
                //Brake Light Setpoint
                else if(next == 7){ 
                    DataHold[0] = Receive_get2();
                    //Get data array to int
                    sscanf(DataHold, "%d", &Data);
                    //We have data and are ready to save it to the car
                    printf("FW-RV = ");
                    if(Data == 1){
                        printf("yes\n");
                        NewDriverFW_RW_EN(true);
                    }
                    else{
                        printf("no\n");
                        NewDriverFW_RW_EN(false);
                    }
                    next++;
                    //We are done grabbing data off the pipeline
                    FunctionDataGrab = 5;
                    printf("Regen source (1 = brake 0 = throttle)\n");
                    i = 0;
                }
                //Get Regen info
                else if(next == 8){  
                    DataHold[0] = Receive_get2();
                    //Get data array to int
                    sscanf(DataHold, "%d", &Data);
                    //We have data and are ready to save it to the car
                    printf("Regen source = ");
                    if(Data == 1){
                        printf("Brake\n");
                        NewDriverRegenInput(true);
                    }
                    else{
                        printf("Throttle\n");
                        NewDriverRegenInput(false);
                    }
                    next++;
                    //We are done grabbing data off the pipeline
                    FunctionDataGrab = false;
                    SubMenu = 0;
                    NewDriverSave();
                    printf("New Driver Saved!\n");
                    TimeOutSet(5000);
                    i = 0;
                    next = 0;
                }
            }
            //Config data for Brake light
            else if(FunctionDataGrab == 6){
                //Get data of the pipe
                DataHold[i] = Receive_get2();
                i++;
                //We are looking for 3 chars...
                if(i>2){
                    //Get data array to int
                    sscanf(DataHold, "%d", &Data);
                    //We are done grabbing data off the pipeline
                    FunctionDataGrab = false;
                    SubMenu = 0;
                    TimeOutSet(3000);
                    i = 0;
                    MenuBrakeLightValue(1);
                }
            }
            //Config data for Driver Max Throttle 
            else if(FunctionDataGrab == 7){
                //Get data of the pipe
                DataHold[i] = Receive_get2();
                i++;
                //We are looking for 3 chars...
                if(i>2){
                    //Get data array to int
                    sscanf(DataHold, "%d", &Data);
                    //We have data and are ready to save it to the car
                    printf("New Max throttle = %d",Data);
                    //We are done grabbing data off the pipeline
                    FunctionDataGrab = false;
                    SubMenu = 0;
                    TimeOutSet(3000);
                    i = 0;
                }
            }
            //Config data for Driver Max Regen 
            else if(FunctionDataGrab == 8){
                //Get data of the pipe
                DataHold[i] = Receive_get2();
                i++;
                //We are looking for 3 chars...
                if(i>2){
                    //Get data array to int
                    sscanf(DataHold, "%d", &Data);
                    //We have data and are ready to save it to the car
                    printf("New Max Regen = %d",Data);
                    //We are done grabbing data off the pipeline
                    FunctionDataGrab = false;
                    SubMenu = 0;
                    TimeOutSet(3000);
                    i = 0;
                }
            }
            //Config data for Driver Max Regen0
            else if(FunctionDataGrab == 9){
                //Get data of the pipe
                DataHold[i] = Receive_get2();
                i++;
                //We are looking for 3 chars...
                if(i>2){
                    //Get data array to int
                    sscanf(DataHold, "%d", &Data);
                    //We have data and are ready to save it to the car
                    printf("New LowBatCutoff = %d",Data);
                    //We are done grabbing data off the pipeline
                    FunctionDataGrab = false;
                    SubMenu = 0;
                    TimeOutSet(3000);
                    i = 0;
                }
            }
            //Config data for Driver Max LowBatCutoff 
            else if(FunctionDataGrab == 10){
                //Get data of the pipe
                DataHold[i] = Receive_get2();
                i++;
                //We are looking for 3 chars...
                if(i>2){
                    //Get data array to int
                    sscanf(DataHold, "%d", &Data);
                    //We have data and are ready to save it to the car
                    printf("New Ramp = %d",Data);
                    //We are done grabbing data off the pipeline
                    FunctionDataGrab = false;
                    SubMenu = 0;
                    TimeOutSet(3000);
                    i = 0;
                }
            }
            //Config data for Driver Ramp
            else if(FunctionDataGrab == 11){
                //Get data of the pipe
                if(next == 0){
                    
                    DataHold[0] = Receive_get2();
                    //Get data array to int
                    sscanf(DataHold, "%d", &Data);
                    //We have data and are ready to save it to the car
                    printf("Faults allowed = %d\n",Data);
                    next++;
                    //We are done grabbing data off the pipeline
                    FunctionDataGrab = 11;
                    //TimeOutSet(1500);
                    printf("Debugging allowed? (1 = yes 0 = no\n");
                    i = 0;
                }
                else if(next == 1){
                    
                    DataHold[0] = Receive_get2();
                    //Get data array to int
                    sscanf(DataHold, "%d", &Data);
                    //We have data and are ready to save it to the car
                    printf("Debugging = ");
                    if(Data == 1){
                        printf("yes\n");
                    }
                    else printf("no\n");
                    next++;
                    //We are done grabbing data off the pipeline
                    FunctionDataGrab = 11;
                    printf("FW-RV allowed? (1 = yes 0 = no\n");
                    //TimeOutSet(1500);
                    i = 0;
                }
                else if(next == 2){
                    
                    DataHold[0] = Receive_get2();
                    //Get data array to int
                    sscanf(DataHold, "%d", &Data);
                    //We have data and are ready to save it to the car
                    printf("FW-RV = ");
                    if(Data == 1){
                        printf("yes\n");
                    }
                    else printf("no\n");
                    next++;
                    //We are done grabbing data off the pipeline
                    FunctionDataGrab = 11;
                    printf("Regen source (1 = brake 0 = throttle\n");
                    i = 0;
                }
                else if(next == 3){
                    
                    DataHold[0] = Receive_get2();
                    //Get data array to int
                    sscanf(DataHold, "%d", &Data);
                    //We have data and are ready to save it to the car
                    printf("Regen source = ");
                    if(Data == 1){
                        printf("Brake\n");
                    }
                    else printf("Throttle\n");
                    next++;
                    //We are done grabbing data off the pipeline
                    FunctionDataGrab = false;
                    SubMenu = 0;
                    TimeOutSet(3000);
                    i = 0;
                    next = 0;
                }
                
            }
        }
    }
}

/*******************************************************************
 * @brief           MenuPrint
 * @brief           Menu control  
 * @return          N/A
 * @note            The fcn prints the menus and controls submenus
 *******************************************************************/
void MenuPrint(char Menuloc, char Subloc){
    switch (Menuloc){
        case 0: 
          printf("|-----Main Menu------| \n");
          printf("1) Throttle Menu\n");
          printf("2) Brake Menu\n");
          printf("3) Settings Menu\n");
          printf("4) Battery Info\n");
          printf("5) ComBus Info\n");
          printf("6) Driver Config\n");
          break;
       case 1:
          ThrottleMenu(Subloc);
          break;
       case 2:
          BrakeMenu(Subloc);
          break;   
       case 3:
          SettingMenu(Subloc);
          break;
       case 4:
          BatteryMenu(Subloc);
          break;
       case 5:
          ComMenu(Subloc);
          break;
       case 6:
          DriverMenu(Subloc);
          break;
       default:
          printf("******NO Match*****\n");
          Menu = 0;
          TimeOutSet(3000);
          break;
    }
    Menudisplay = 0;
}

/*******************************************************************
 * @brief           ThrottleMenu
 * @brief           Sub Menu throttle
 * @return          N/A
 * @note            The fcn prints and control throttle 
 *******************************************************************/
void ThrottleMenu(char menuitem){
    SubMenuActive = true;
    printf("|---Throttle Menu----|\n");
    printf("1) Throttle Display\n");
    printf("2) Throttle Trip Set\n");
    printf("3) Throttle Mismatch\n");
    if(menuitem == 1){
        debugState = THROTTLE;
    }
    else if(menuitem == 2){
        FunctionDataGrab = 1;
    }
    else if(menuitem == 3){
        FunctionDataGrab = 2;
    }
}

/*******************************************************************
 * @brief           BrakeMenu
 * @brief           Sub Menu brake
 * @return          N/A
 * @note            The fcn prints and control brake 
 *******************************************************************/
void BrakeMenu(char menuitem){
    SubMenuActive = true;
    printf("|-----Brake Menu-----|\n");
    printf("1) Brake Display\n");
    printf("2) Brake Max Set\n");
    if(menuitem == 1){
        debugState = BRAKE;
    }
    else if(menuitem == 2){
        FunctionDataGrab = 3;
    }
}

/*******************************************************************
 * @brief           SettingMenu
 * @brief           Sub Menu setting
 * @return          N/A
 * @note            The fcn prints and control Settings 
 *******************************************************************/
void SettingMenu(char menuitem){
    SubMenuActive = true;
    printf("|---Settings Menu----|\n");
    printf("1) Verbose\n");
    printf("2) Reset Value\n");
    printf("3) About\n");
    printf("4) Brake Light Threshold\n");
    printf("5) Car State\n");
    printf("6) Car Fault\n");
    printf("7) Car Fault\n");
    if(menuitem == 1){
        VerboseEn ^= VerboseEn;
        SubMenu = 0;
    }
    else if(menuitem == 2){
        printf("The reset value is %d\n", GetResetValue());
        SubMenu = 0;
    }
    else if(menuitem == 3){
        ClearScreen();
        Display();
        TimeOutSet(5000);
        SubMenu = 0;      
    }
    else if(menuitem == 4){
        ClearScreen();
        MenuBrakeLightValue(0);
        SubMenu = 0;      
    }
    else if(menuitem == 5){
        ClearScreen();
        debugState = FIND_STATE;
        SubMenu = 0;      
    }
    else if(menuitem == 6){
        ClearScreen();
        debugState = FAULT_RECOVERY;
        SubMenu = 0;      
    }
    else if(menuitem == 7){
        ClearScreen();
        debugState = SS_INFO;
        SubMenu = 0;      
    }
}

/*******************************************************************
 * @brief           BatteryMenu
 * @brief           Sub Menu Battery
 * @return          N/A
 * @note            The fcn prints and control Battery 
 *******************************************************************/
void BatteryMenu(char menuitem){
    SubMenuActive = true;
    printf("|---Battery Info---|\n");
    printf("1) Voltage\n");
    printf("2) Current\n");
    printf("3) Temp\n");
    printf("4) Stats\n");
    if(menuitem == 1){
        debugState = BATTERY_DEBUG_VOLTS;
    }
    else if(menuitem == 2){
        debugState = BATTERY_DEBUG_POWER;
    }
    else if(menuitem == 3){
        debugState = BATTERY_DEBUG_TEMPS;
    }
    else if(menuitem == 4){
        printf("Battery state\n");
        printf("- Boards OK\n");
        printf("- Comm's UP\n");
    }
}

/*******************************************************************
 * @brief           ComMenu
 * @brief           Sub Menu Communications
 * @return          N/A
 * @note            The fcn prints and control Communications 
 *******************************************************************/
void ComMenu(char menuitem){
    SubMenuActive = true;
    printf("|---ComBus Info---|\n");
    printf("1) Boards On\n");
    printf("2) Error Rate\n");
    printf("3) Data Rate\n");
    if(menuitem == 1){
        debugState = comm_on;
    }
    else if(menuitem == 2){
        debugState = error_rate;
    }
    else if(menuitem == 3){
        
    }
}

/*******************************************************************
 * @brief           DriverMenu
 * @brief           Sub Menu Driver
 * @return          N/A
 * @note            The fcn prints and control Driver stuff 
 *******************************************************************/
void DriverMenu(char menuitem){
    SubMenuActive = true;
    printf("|---Driver Config---|\n");
    printf("1) Driver Select\n");
    printf("2) New Driver Config\n");
    printf("3) Driver Max Throttle \n");
    printf("4) Driver Max Regen \n");
    printf("5) Driver LowBatCutoff \n");
    printf("6) Driver Ramp \n");
    printf("7) Driver ETC\n");
    printf("------%s IS ACTIVE-------\n",CurrentDriverName());
    if(menuitem == 1){
        printf("|---Driver List---|\n");
        int i;
        for(i = 1;i < DriverCount()+1;i++){ //added the offset of driver count to offset the i = 1
            printf("%d) Driver %d - ",i,i);
            DriverNamePrint(i);
        }
        FunctionDataGrab = 4;
    }
    else if(menuitem == 2){
        printf("|--Add a Driver--|\n");
        printf("|--Drivers initals--|\n");
        printf("|--Max three chars--|\n");
        FunctionDataGrab = 5;
    }
    else if(menuitem == 3){
        printf("|----Max Throttle---|\n");
        printf("|------0 to 100-----|\n");
        printf("|-Must Be 3 digits--|\n");
        FunctionDataGrab = 7;
    }
    else if(menuitem == 4){
        printf("|-----Max Regen-----|\n");
        printf("|------0 to 100-----|\n");
        printf("|-Must Be 3 digits--|\n");
        FunctionDataGrab = 8;
    }
    else if(menuitem == 5){
        printf("|----LowBatCutoff---|\n");
        printf("|------0 to 100-----|\n");
        printf("|-Must Be 3 digits--|\n");
        FunctionDataGrab = 9;
    }
    else if(menuitem == 6){
        printf("|--------Ramp-------|\n");
        printf("|------0 to 100-----|\n");
        printf("|-Must Be 3 digits--|\n");
        FunctionDataGrab = 10;
    }
    else if(menuitem == 7){
        printf("|---Fault Allowed---|\n");
        printf("|------Debug En-----|\n");
        printf("|RegenInput & FW/RV-|\n");
        printf("What faults are allowed?\n");
        FunctionDataGrab = 11;
    }
}

/*******************************************************************
 * @brief           MenuBrakeLightValue
 * @brief           Sub Sub Menu Brake light
 * @return          N/A
 * @note            The fcn gets the info to save the brake light trip point 
 *******************************************************************/
void MenuBrakeLightValue(char cont){
    if(cont == 0){
        printf("|--Brake Light Threshold--|\n");
        printf("|---Give the value as  ---|\n");
        printf("|---------0 to 100--------|\n");
        FunctionDataGrab = 6;
    }
    if(cont == 1){
        SaveBrakeLightTrigger(Data);
        printf(" Brake Light Set to %d",Data);
        TimeOutSet(3000);
    }
}

/*******************************************************************
 * @brief           menuclear
 * @brief           timeout
 * @return          N/A
 * @note            The fcn makes a timer based delay for time outs on the CLI
 *******************************************************************/
void MenuClearFlag(){
    MenuClear = true;
}

/*******************************************************************
 * @brief           ClearScreen
 * @brief           ANSI Clear 
 * @return          N/A
 * @note            The fcn prints the clear command
 *******************************************************************/
void ClearScreen()
{
  printf("\033[2J");
  printf("\033[H");
}