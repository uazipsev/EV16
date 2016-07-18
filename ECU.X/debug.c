#include "debug.h"
#include <stdio.h>
#include "ADDRESSING.h"
#include "SlaveAddressing.h"
#include "Functions.h"
#include "UART2.h"
#include "StoppedState.h"

#include <errno.h>

#define LOW_VOLTAGE_FLAG 1
#define HIGH_TEMPERATURE_FLAG 2
#define COMMUNICATIONS_FAULT 3


//SAS
#define THROTTLE_SANITY_CHECK 1
#define THROTTLE_BRAKE_CHECK  2

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
 extern unsigned int t1Raw, t2Raw, bRaw;
               int State_Value =0;
               int StateFault_Value=0;
enum debugStates debugState;
extern int DDS_FAULT_CONDITION, MCS_FAULT_CONDITION, SAS_FAULT_CONDITION, BMM_FAULT_CONDITION, PDU_FAULT_CONDITION, ECU_FAULT_CONDITION;
extern int faultingBattery;
extern int BMMADC[4];
extern int milliVolts[NUMSLAVES][BATTPERSLAVE];
extern int temps[NUMSLAVES][BATTPERSLAVE];
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

char DataHold[10];

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
//                if (comms.BMM) {
////                    //printf("\n---Slave #%d Bat Voltage Info---\n", batterySlaveNumberV + 1);
////                    printf("B1: %dV B2: %dV B3: %dV B4: %dV\n", milliVolts[batterySlaveNumberV][0], milliVolts[batterySlaveNumberV][1], milliVolts[batterySlaveNumberV][2], milliVolts[batterySlaveNumberV][3]);
////                    printf("B5: %dV B6: %dV B7: %dV B8: %dV\n", milliVolts[batterySlaveNumberV][4], milliVolts[batterySlaveNumberV][5], milliVolts[batterySlaveNumberV][6], milliVolts[batterySlaveNumberV][7]);
////                    printf("B9: %dV B10:%dV                \n", milliVolts[batterySlaveNumberV][8], milliVolts[batterySlaveNumberV][9]);
////                    if (batterySlaveNumberV < NUMSLAVES - 1) batterySlaveNumberV++;
////                    else batterySlaveNumberV = 0;
//                } else
                    //printf("\nComms with BMM are no longer online\n");
                    
                    printf("\n Battery info:\n");
                    printf("\n Battery Cell high %d V = %f:\n",140,3.89+augment[k]);
                    printf("\n Battery Cell low %d V = %f:\n",45,3.82+augment[k]);
                    printf("\n Battery STD DIV = %f:\n",0.067+augment[k]);
                    printf("\n Current A %3.02f B %3.02f C %3.02f \n", 0.00, 0.0, 0.00);
                    printf("\n Temp MAX %f  F MIN %f F AVG %f F",120-augment[k+2], 110+augment[k-1], 115-augment[k+1]);
                    k++;
                    if(k > 5){
                        k = 0;
                    }
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
//                if (batterySlaveNumber < NUMSLAVES - 1) batterySlaveNumber++;
//                else batterySlaveNumber = 0;

                break;
            case BATTERY_DEBUG_POWER:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                    //comms.BMM_SEND = BATTERY_POWER;
                }
                printf("\n----BMM Power Signal Debug----\n");
//              printf("BMMADC[0]:      %d\n", BMMADC[0]);
//              printf("BMMADC[1]:      %d\n", BMMADC[1]);
//              printf("BMMADC[2]:      %d\n", BMMADC[2]);
//              printf("BMMADC[3]:      %d\n", BMMADC[3]);
                printf("Current Pack 1:  %d\n", current1);
                printf("Current Pack 2:  %d\n", current2);
                printf("Current Pack 3:  %d\n", current2);
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
                
        }
        if(Menudisplay){
            ClearScreen();
            MenuePrint(Menu,SubMenu);
        }
        DebugTimer = 0;
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
                DataHold[i] = Receive_get2();
                i++;
                if(i>1){
                    SelectDriver();
                    FunctionDataGrab = false;
                    i = 0;
                }
            }
            //Throttle Precent
            if(FunctionDataGrab == 1){
                DataHold[i] = Receive_get2();
                i++;
                if(i>1){
                    SelectDriver();
                    FunctionDataGrab = false;
                    i = 0;
                }
            }
            //Throttle Setpoint
            if(FunctionDataGrab == 2){
                DataHold[i] = Receive_get2();
                i++;
                if(i>1){
                    SelectDriver();
                    FunctionDataGrab = false;
                    i = 0;
                }
            }
            //Brake Setpoint
            if(FunctionDataGrab == 3){
                DataHold[i] = Receive_get2();
                i++;
                if(i>1){
                    SelectDriver();
                    FunctionDataGrab = false;
                    i = 0;
                }
            }
            //Brake Light Setpoint
            if(FunctionDataGrab == 5){
                DataHold[i] = Receive_get2();
                i++;
                if(i>2){
                    SelectDriver();
                    FunctionDataGrab = false;
                    i = 0;
                }
            }
        }
    }
}

void MenuePrint(char Menuloc, char Subloc){
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
          break;
    }
    Menudisplay = 0;
}

void ThrottleMenu(char menuitem){
    SubMenuActive = true;
    printf("|---Throttle Menu----|\n");
    printf("1) Throttle Display\n");
    printf("2) Throttle Trip Set\n");
    printf("3) Throttle Mismatch\n");
    if(menuitem == 1){
        debugState = THROTTLE_BRAKE;
    }
    else if(menuitem == 2){
        FunctionDataGrab = 1;
    }
    else if(menuitem == 3){
        FunctionDataGrab = 2;
    }
}

void BrakeMenu(char menuitem){
    SubMenuActive = true;
    printf("|-----Brake Menu-----|\n");
    printf("1) Brake Display\n");
    printf("2) Brake Max Set\n");
    if(menuitem == 1){
        debugState = THROTTLE_BRAKE;
    }
    else if(menuitem == 2){
        FunctionDataGrab = 3;
    }
}

void SettingMenu(char menuitem){
    SubMenuActive = true;
    printf("|---Settings Menu----|\n");
    printf("1) Verbose\n");
    printf("2) Reset Value\n");
    printf("3) About");
    printf("4) Brake Light Threshold");
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
        SubMenu = 0;      
    }
    else if(menuitem == 4){
        ClearScreen();
        SetBrakeLightValue();
        SubMenu = 0;      
    }
}

void BatteryMenu(char menuitem){
    SubMenuActive = true;
    printf("|---Battery Info---|\n");
    printf("1) Voltage\n");
    printf("2) Current\n");
    printf("3) Temp\n");
    printf("4) Sat's\n");
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
    
    }
    else if(menuitem == 3){
        
    }
}

void DriverMenu(char menuitem){
    SubMenuActive = true;
    printf("|---Driver Config---|\n");
    printf("1) Driver Select\n");
    printf("2) Driver Config\n");
    if(menuitem == 1){
        printf("|---Driver List---|\n");
        int i;
        for(i = 1;i < DriverCount();i++){
            printf("%d) Driver %d - %s\n",i,i,DriverName(i));
        }
        FunctionDataGrab = 4;
    }
    else if(menuitem == 2){
        printf("|--Select a Driver--|\n");
        printf("|-----To Config-----|\n");
        int i;
        for(i = 1;i < DriverCount();i++){
            printf("%d) Driver %d - %s\n",i,i,DriverName(i));
        }
        FunctionDataGrab = 5;
    }
}

void SelectDriver(){
    ClearScreen();
    SetDriver(DataHold[0]-48);
    SubMenu = 0;
}

void SetBrakeLightValue(){
    printf("|--Brake Light Threshold--|");
    printf("|---Give the value as  ---|");
    printf("|---------0 to 100--------|");
}

void ClearScreen()
{
  printf("\033[2J");
  printf("\033[H");
}