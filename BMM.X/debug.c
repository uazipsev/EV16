/*******************************************************************
 * @brief           Debug.c
 * @brief           This lib runs our CLI
 * @return          N/A
 * @note            Created by - Zac and Rick Uses data from around the car to display info on the CLI
 *******************************************************************/
#include "debug.h"
#include "Timers.h"
#include <stdio.h>
#include <string.h>

enum debugStates debugState;
void handleDebugRequests();

bool VerboseEn = 1;
char m = 0;
bool Menudisplay = 0;
char FunctionDataGrab = 0;
char DataIn = 0;
int Menu = 0;
int SubMenu = 0;
bool FuncIn = 0;
bool SubMenuActive = false;
bool MenuClear = false;
int Data = 0;
char DataHold[10];
char TimeOutMenu = 0;
char next = 0;

///*******************************************************************
// * @brief           write
// * @brief           WTF
// * @return          returns length (how many chars) of data
// * @note            I have no idea what the fuck this is for...may be removed (printf maybe?)
// *******************************************************************/
//int write(int handle, void *buffer, unsigned int len) {
//    int m;
//    switch (handle) {
//        case 0: // handle 0 corresponds to stdout
//        case 1: // handle 1 corresponds to stdin
//        case 2: // handle 2 corresponds to stderr
//        default:
//            for (m = 0; m < len; m++){}
//                //Send_put2(*(char*) buffer++);
//    }
//    return (len);
//}

/*******************************************************************
 * @brief           handleDebugRequests
 * @brief           Handels CLI system data   
 * @return          N/A
 * @note            The fcn monitors USART3 for activity and responds.
 *                  The fcn also sends repeat data for viewing.
 *******************************************************************/
void handleDebugRequests() {
    static int lastDebugState = 0;

    if (time_get(DEBUGTIME) > 1000) {
        switch (debugState) {
            case NO_DEBUG:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;

                }
                break;
            case TEMPSBAM1:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("\n-----Throttle Brake Raw Debug----\n");
                break;
            case TEMPSBAM2:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("\n---- Brake Raw Debug----\n");
                break;
            case TEMPSBAM3:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }     
                printf("\n Battery info:\n");
                break;
            case TEMPSBBM1:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("\n----Slave Bat Temp Info---- \n");
                break;
            case TEMPSBBM2:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("\n----BMM Power Signal Debug----\n");
                break;
            case TEMPSBBM3:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("\n----Fault Reporting/Recovery Mode----\n");
                break;
            case VOLTSBAM1:
                //This is the first time through the loop
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                break;
            case VOLTSBAM2:
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("State On ECU State Machine\n");
                break;
            case VOLTSBAM3:
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("State On ECU State Machine\n");
                break;
            case VOLTSBBM1:
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("The reset value is \n");
                break;
            case VOLTSBBM2:
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("Comms:\n");
                break;
            case VOLTSBBM3:
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                int i;
                for(i = 0;i<8;i++){
                    printf("Button ");
                }
                break;
            case CURRENT_PV:
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("Align Error B1 \n");
                break;
            case FAULT:
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("Align Error B1\n");
                break;
            case ERRORRATE:
                if (lastDebugState != debugState) {
                    lastDebugState = debugState;
                }
                printf("Align Error B1 \n");
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
        time_Set(DEBUGTIME,0);
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
        else if(FunctionDataGrab){
            //Throttle Precent
            if(FunctionDataGrab == 1){
                //Get data of the pipe
                DataHold[m] = Receive_get2();
                m++;
                //We are looking for x chars...
                if(m>1){
                    //We are done grabbing data off the pipeline
                    FunctionDataGrab = false;
                    m = 0;
                }
            }
            //Config data for Driver Ramp
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
          break;
       case 2:
          break;   
       case 3:
          break;
       case 4:
          break;
       case 5:
          break;
       case 6:
          break;
       default:
          printf("******NO Match*****\n");
          Menu = 0;
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
        //debugState = THROTTLE;
    }
    else if(menuitem == 2){
        FunctionDataGrab = 1;
    }
    else if(menuitem == 3){
        FunctionDataGrab = 2;
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