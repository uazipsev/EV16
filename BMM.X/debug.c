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
#include "UART1.h"
#include "BatteryManagment.h"

enum debugStates debugState;
void handleDebugRequests();
int old_debug = 0;
bool stop_state = false;
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
char module = 0;

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
        int counter = 0;
        int ic = 0;
        double temp;
        double voltage;
        //INDICATOR = !INDICATOR;
        switch (debugState) {
            case NO_DEBUG:
                //Don't print ANYTHING!!!!!

                break;

            case TEMPSBAM1:
                printf("\n-----Temp Bank A Mod 1----\n");
                ic = 0;
                counter = 0;
                while (ic < 3) {
                    while (counter < 5) {
                        temp = gettemp(ic, counter, bank_1);
                        //printf("Temp for IC:%i and Sensor #:%i =%f\n", ic, counter, temp);
                        temp = Aux_codes_Bank1[ic][counter]; //TODO for debuging consle get rid of
                        //printf("Temp for IC:%i and Sensor #:%i =%f\n", ic, counter, temp);
                        counter++;
                    }
                    printf("\n");
                    counter = 0;
                    ic++;
                }

                Display_Max_and_Min(Temprature_Array, bank_1);
                break;

            case TEMPSBAM2:
                printf("\n-----Temp Bank A Mod 2----\n");
                ic = 3;
                counter = 0;
                while (ic < 6) {
                    while (counter < 5) {
                        temp = gettemp(ic, counter, bank_1);
                        printf("Temp for IC:%i and Sensor #:%i =%f\n", ic, counter, temp);
                        counter++;
                    }
                    printf("\n");
                    counter = 0;
                    ic++;
                }
                Display_Max_and_Min(Temprature_Array, bank_1);
                break;

            case TEMPSBAM3:
                printf("\n-----Temp Bank A Mod 3----\n");
                ic = 6;
                counter = 0;
                while (ic < 9) {
                    while (counter < 5) {
                        temp = gettemp(ic, counter, bank_1);
                        // temp=Aux_codes_Bank1[ic][counter];
                        printf("Temp for IC:%i and Sensor #:%i =%f\n", ic, counter, temp);
                        counter++;
                    }
                    printf("\n");
                    counter = 0;
                    ic++;
                }
                Display_Max_and_Min(Temprature_Array, bank_1);
                break;

            case TEMPSBBM1:
                printf("\n-----Temp Bank B Mod 1----\n");
                ic = 0;
                counter = 0;
                while (ic < 3) {
                    while (counter < 5) {
                        temp = gettemp(ic, counter, bank_2);
                        printf("Temp for IC:%i and Sensor #:%i =%f\n", ic, counter, temp);
                        counter++;
                    }
                    printf("\n");
                    counter = 0;
                    ic++;
                }
                Display_Max_and_Min(Temprature_Array, bank_2);
                break;

            case TEMPSBBM2:
                printf("\n-----Temp Bank B Mod 2----\n");
                ic = 3;
                counter = 0;
                while (ic < 6) {
                    while (counter < 5) {
                        temp = gettemp(ic, counter, bank_2);
                        printf("Temp for IC:%i and Sensor #:%i =%f\n", ic, counter, temp);
                        counter++;
                    }
                    printf("\n");
                    counter = 0;
                    ic++;
                }
                Display_Max_and_Min(Temprature_Array, bank_2);
                break;

            case TEMPSBBM3:
                printf("\n-----Temp Bank B Mod 3----\n");
                ic = 6;
                counter = 0;
                while (ic < 9) {
                    while (counter < 5) {
                        temp = gettemp(ic, counter, bank_2);
                        printf("Temp for IC:%i and Sensor #:%i =%f\n", ic, counter, temp);
                        counter++;
                    }
                    printf("\n");
                    counter = 0;
                    ic++;
                }
                Display_Max_and_Min(Temprature_Array, bank_2);
                break;

            case VOLTSBAM1:
                printf("\n-----Volt Bank A Mod 1----\n");
                printf("Total Mod Voltage for Module %i is: %f\n", 1, Get_Pack_Voltages(module_0, bank_1));
                ic = 0;
                counter = 0;
                while (ic < 3) {
                    while (counter < 11) {
                        voltage = Get_Pack_Voltages(ic, counter, bank_1);
                        printf("Battery Voltage for IC:%i and Sensor #:%i =%f\n", ic, counter, voltage);
                        counter++;
                    }
                    printf("\n");
                    counter = 0;
                    ic++;
                }
                Display_Max_and_Min(Battery_Array, bank_1);
                break;

            case VOLTSBAM2:
                printf("\n-----Volt Bank A Mod 2----\n");
                printf("Total Mod Voltage for Module %i is: %f\n", 2, Get_Pack_Voltages(module_1, bank_1));
                ic = 3;
                counter = 0;
                while (ic < 6) {
                    while (counter < 11) {
                        voltage = Get_Pack_Voltages(ic, counter, bank_1);
                        printf("Battery Voltage for IC:%i and Sensor #:%i =%f\n", ic, counter, voltage);
                        counter++;
                    }
                    printf("\n");
                    counter = 0;
                    ic++;
                }
                Display_Max_and_Min(Battery_Array, bank_1);
                break;

            case VOLTSBAM3:
                printf("\n-----Volt Bank A Mod 3----\n");
                printf("Total Mod Voltage for Module %i is: %f\n", 3, Get_Pack_Voltages(module_2, bank_1));
                ic = 6;
                counter = 0;
                while (ic < 9) {
                    while (counter < 11) {
                        voltage = Get_Pack_Voltages(ic, counter, bank_1);
                        printf("Battery Voltage for IC:%i and Sensor #:%i =%f\n", ic, counter, voltage);
                        counter++;
                    }
                    printf("\n");
                    counter = 0;
                    ic++;
                }
                Display_Max_and_Min(Battery_Array, bank_1);
                break;

            case VOLTSBBM1:
                printf("\n-----Volt Bank B Mod 1----\n");
                printf("Total Mod Voltage for Module %i is: %f\n", 1, Get_Pack_Voltages(module_0, bank_2));
                ic = 0;
                counter = 0;
                while (ic < 3) {
                    while (counter < 11) {
                        voltage = Get_Pack_Voltages(ic, counter, bank_2);
                        printf("Battery Voltage for IC:%i and Sensor #:%i =%f\n", ic, counter, voltage);
                        counter++;
                    }
                    printf("\n");
                    counter = 0;
                    ic++;
                }
                Display_Max_and_Min(Battery_Array, bank_2);
                break;

            case VOLTSBBM2:
                printf("\n-----Volt Bank B Mod 2----\n");
                printf("Total Mod Voltage for Module %i is: %f\n", 2, Get_Pack_Voltages(module_1, bank_2));
                ic = 3;
                counter = 0;
                while (ic < 6) {
                    while (counter < 11) {
                        voltage = Get_Pack_Voltages(ic, counter, bank_2);
                        printf("Battery Voltage for IC:%i and Sensor #:%i =%f\n", ic, counter, voltage);
                        counter++;
                    }
                    printf("\n");
                    counter = 0;
                    ic++;
                }
                Display_Max_and_Min(Battery_Array, bank_2);
                break;

            case VOLTSBBM3:
                printf("\n-----Volt Bank B Mod 3----\n");
                printf("Total Mod Voltage for Module %i is: %f\n", 3, Get_Pack_Voltages(module_2, bank_2));
                ic = 6;
                counter = 0;
                while (ic < 9) {
                    while (counter < 11) {
                        voltage = Get_Pack_Voltages(ic, counter, bank_2);
                        printf("Battery Voltage for IC:%i and Sensor #:%i =%f\n", ic, counter, voltage);
                        counter++;
                    }
                    printf("\n");
                    counter = 0;
                    ic++;
                }
                Display_Max_and_Min(Battery_Array, bank_2);
                break;

            case CURRENT_PV:
                ClearScreen();
                printf("CS 1 C+ =  %f\n",CurrentGet(1, 1));
                printf("CS 1 C- =  %f\n",CurrentGet(1, 2));
                printf("Voltage 1 =  \n");
                printf("Voltage 2 =  \n");
                printf("ADC 2 - Address = \n");
                printf("CS 1 C+ =  %f\n",CurrentGet(1, 3));
                printf("CS 1 C- =  %f\n",CurrentGet(0, 1));
                printf("CS 1 C+ =  %f\n",CurrentGet(0, 2));
                printf("CS 1 C- =  %f\n",CurrentGet(0, 3));
                break;
            case FAULT:
                printf("Align Error B1\n");
                break;
            case ERRORRATE:
                printf("Align Error B1 \n");
                break;
        }
        if (Menudisplay) {
            ClearScreen();
            MenuPrint(Menu, SubMenu);
        }
        if (MenuClear) {
            ClearScreen();

            MenuPrint(Menu, SubMenu);
            MenuClear = false;
        }
        time_Set(DEBUGTIME, 0);
    }

    if (Receive_available2()) {
        DataIn = Receive_get2();
        if (VerboseEn) {
            printf("%c", DataIn);
        }
        if (DataIn == 'b') {
            debugState = NO_DEBUG;
            if ((SubMenuActive == true) && (SubMenu > 0)) {
                SubMenu = 0;
            } else if ((SubMenuActive == true) && (SubMenu == 0)) {
                SubMenuActive = false;
                Menu = 0;
            }
            Menudisplay = 1;
            stop_state = false;
        } else if (DataIn == 's' && !stop_state) {
            old_debug = debugState;
            debugState = NO_DEBUG;
            //DataIn=0;
            stop_state = true;
        } else if (DataIn == 's' && stop_state) {
            debugState = old_debug;
            //DataIn=0;
            stop_state = false;
        } else if (!FunctionDataGrab) {
            if (SubMenuActive == false) {
                Menu = DataIn - 48;
            } else if (SubMenuActive == true) {
                SubMenu = DataIn - 48;
            }
            Menudisplay = 1;
        } else if (FunctionDataGrab) {
            //Get the Module we want data from
            if (FunctionDataGrab == 1) {
                //Get data of the pipe
                module = DataIn - 48;
                SubMenu = 1;

                //We are done grabbing data off the pipeline
                FunctionDataGrab = false;
            }
            Menudisplay = 1;
        }
    }
}

/*******************************************************************
 * @brief           MenuPrint
 * @brief           Menu control  
 * @return          N/A
 * @note            The fcn prints the menus and controls submenus
 *******************************************************************/
void MenuPrint(char Menuloc, char Subloc) {
    switch (Menuloc) {
        case 0:
            printf("|-----Main Menu------| \n");
            printf("1) Address on Buss A & B\n");
            printf("2) Current and Pack Voltage\n");
            printf("3) Temp\n");
            printf("4) Voltage - Bypass\n");
            printf("5) Errors\n");
            printf("6) Max statistics");
            break;
        case 1:
            AddressMenu(Subloc);
            break;
        case 2:
            CurrentAndVoltageMenu(Subloc);
            break;
        case 3:
            TempModuleMenu(Subloc);
            break;
        case 4:
            VoltageModuleMenu(Subloc);
            break;
        case 5:
            ErrorMenu(Subloc);
        case 6:
            MaxMenu(Subloc);
            break;
        default:
            printf("******NO Match*****\n");
            Menu = 0;
            break;
    }
    Menudisplay = 0;
}

/*******************************************************************
 * @brief           AddressMenu
 * @brief           Sub Menu address response
 * @return          N/A
 * @note            The fcn prints address responding on Buss A&B
 *******************************************************************/
void AddressMenu(char menuitem) {
    char e = 0;
    SubMenuActive = true;
    printf("|----Address on Buss A & B----|\n");
    printf("Bank A: \n");
    for (; e < 9; e++) {
        printf("Address %d = NO\n", e);
    }
    printf("Bank B:\n");
    for (e = 0; e < 9; e++) {
        printf("Address %d = NO\n", e);
    }
    SubMenu = 0;
}

/*******************************************************************
 * @brief           CurrentAndVoltageMenu
 * @brief           Sub Menu for I2C ADC 
 * @return          N/A
 * @note            The fcn prints ADC values from iso I2C
 *******************************************************************/
void CurrentAndVoltageMenu(char menuitem) {
    SubMenuActive = true;
    printf("|----C and V Print----|\n");
    debugState = CURRENT_PV;
}

/*******************************************************************
 * @brief           VoltageModuleMenu
 * @brief           Sub Menu for voltage print
 * @return          N/A
 * @note            The fcn prints voltage values from modules 
 *******************************************************************/
void VoltageModuleMenu(char menuitem) {
    SubMenuActive = true;
    if (menuitem == 0) {
        printf("|----V Module Print----|\n");
        printf("|--What Module (1-6)--|\n");
        FunctionDataGrab = 1;
    } else {
        printf("Module %d is active!", module);
        switch (module) {
            case 1:
                debugState = VOLTSBAM1;
                break;
            case 2:
                debugState = VOLTSBAM2;
                break;
            case 3:
                debugState = VOLTSBAM3;
                break;
            case 4:
                debugState = VOLTSBBM1;
                break;
            case 5:
                debugState = VOLTSBBM2;
                break;
            case 6:
                debugState = VOLTSBBM3;
                break;
        }
    }
}

/*******************************************************************
 * @brief           TempModuleMenu
 * @brief           Sub Menu for Temp print
 * @return          N/A
 * @note            The fcn prints temps values from modules 
 *******************************************************************/
void TempModuleMenu(char menuitem) {
    SubMenuActive = true;
    if (menuitem == 0) {
        printf("|----T Module Print----|\n");
        printf("|--What Module (1-6)--|\n");
        FunctionDataGrab = 1;
    } else {
        printf("Module %d is active!", module);
        switch (module) {
            case 1:
                debugState = TEMPSBAM1;
                break;
            case 2:
                debugState = TEMPSBAM2;
                break;
            case 3:
                debugState = TEMPSBAM3;
                break;
            case 4:
                debugState = TEMPSBBM1;
                break;
            case 5:
                debugState = TEMPSBBM2;
                break;
            case 6:
                debugState = TEMPSBBM3;
                break;
        }
    }
}

/*******************************************************************
 * @brief           TempModuleMenu
 * @brief           Sub Menu for Temp print
 * @return          N/A
 * @note            The fcn prints temps values from modules 
 *******************************************************************/
void ErrorMenu(char menuitem) {
    SubMenuActive = true;
    printf("|---Fucking Errors----|\n");
    printf("|--WTF happened.....--|\n");
}
//CODE NOT DONE HAVE TO WORK ON INPUT COMMANDS give max Temperature
void MaxMenu(char menuitem) {
     printf("|----Extreme Temperature----|\n");
     //debugState = MAXTEMP_EM;
//    printf("|----Extreme Values----|\n");
//    printf("1) Max Voltage \n");
//    printf("2) Min Voltage \n");
//    printf("3) Max Temperature \n");
//    printf("4) Min Temperature \n");
//    if (menuitem == 0) {
//        FunctionDataGrab = 1;
//    } 
//    else if (menuitem == 1) {
//        printf("|----Max Voltage Modules---|\n");
//        printf("0) All Modules \n");
//        printf("1) Module 1 \n");
//        printf("2) Module 2 \n");
//        printf("3) Module 3 \n");
//        printf("4) Module 4 \n");
//        printf("5) Module 5 \n");
//        printf("6) Module 6 \n");
//         FunctionDataGrab = 1;
//    } else if (menuitem == 2) {
//        printf("|----Min Voltage Modules----|\n");
//        printf("0) All Modules \n");
//        printf("1) Module 1 \n");
//        printf("2) Module 2 \n");
//        printf("3) Module 3 \n");
//        printf("4) Module 4 \n");
//        printf("5) Module 5 \n");
//        printf("6) Module 6 \n");
//         FunctionDataGrab = 1;
//    } else if (menuitem == 3) {
//        printf("|----Max Temperature Modules---|\n");
//        printf("0) All Modules \n");
//        printf("1) Module 1 \n");
//        printf("2) Module 2 \n");
//        printf("3) Module 3 \n");
//        printf("4) Module 4 \n");
//        printf("5) Module 5 \n");
//        printf("6) Module 6 \n");
//         FunctionDataGrab = 1;
//    } else if (menuitem == 4) {
//        printf("|----Min Temperature Modules----|\n");
//        printf("0) All Modules \n");
//        printf("1) Module 1 \n");
//        printf("2) Module 2 \n");
//        printf("3) Module 3 \n");
//        printf("4) Module 4 \n");
//        printf("5) Module 5 \n");
//        printf("6) Module 6 \n");
//         FunctionDataGrab = 1;
//    }
//    else {
//        printf("Module %d is active!", module);
//        switch (module) {
//            case 0:
//                debugState = TEMPSBAM1;
//            case 1:
//                debugState = TEMPSBAM1;
//                break;
//            case 2:
//                debugState = TEMPSBAM2;
//                break;
//            case 3:
//                debugState = TEMPSBAM3;
//                break;
//            case 4:
//                debugState = TEMPSBBM1;
//                break;
//            case 5:
//                debugState = TEMPSBBM2;
//                break;
//            case 6:
//                debugState = TEMPSBBM3;
//                break;
//        }
}

/*******************************************************************
 * @brief           menuclear
 * @brief           timeout
 * @return          N/A
 * @note            The fcn makes a timer based delay for time outs on the CLI
 *******************************************************************/
void MenuClearFlag() {
    MenuClear = true;
}

/*******************************************************************
 * @brief           ClearScreen
 * @brief           ANSI Clear 
 * @return          N/A
 * @note            The fcn prints the clear command
 *******************************************************************/
void ClearScreen() {
    printf("\033[2J");
    printf("\033[H");
}

void Display_Max_and_Min(int select, int bank) {
    double Data = 0;
    double IC_Loc = 0;
    double Sens_Loc = 0;

    if (select == Battery_Array) {
        if (bank == bank_1) {
            Data = Get_Extreme_Voltage(min_select, 0, bank_1);
            IC_Loc = Get_Extreme_Voltage(min_select, 1, bank_1);
            Sens_Loc = Get_Extreme_Voltage(min_select, 2, bank_1);

            printf("\nThe Minimum Voltage in this bank is: %f at IC %f and sensor %f\n", Data, IC_Loc, Sens_Loc);

            Data = Get_Extreme_Voltage(max_select, 0, bank_1);
            IC_Loc = Get_Extreme_Voltage(max_select, 1, bank_1);
            Sens_Loc = Get_Extreme_Voltage(max_select, 2, bank_1);

            printf("The Maximum Voltage in this bank is: %f at IC %f and sensor %f\n\n", Data, IC_Loc, Sens_Loc);
        }
        else if (bank == bank_2) {
            Data = Get_Extreme_Voltage(min_select, 0, bank_2);
            IC_Loc = Get_Extreme_Voltage(min_select, 1, bank_2);
            Sens_Loc = Get_Extreme_Voltage(min_select, 2, bank_2);

            printf("\nThe Minimum Voltage in this bank is: %f at IC %f and sensor %f\n", Data, IC_Loc, Sens_Loc);

            Data = Get_Extreme_Voltage(max_select, 0, bank_2);
            IC_Loc = Get_Extreme_Voltage(max_select, 1, bank_2);
            Sens_Loc = Get_Extreme_Voltage(max_select, 2, bank_2);

            printf("The Maximum Voltage in this bank is: %f at IC %f and sensor %f\n\n", Data, IC_Loc, Sens_Loc);
        }
    } else if (select == Temprature_Array) {

        if (bank == bank_1) {


            Data = Get_Extreme_Temprature(min_select, 0, bank_1);
            IC_Loc = Get_Extreme_Temprature(min_select, 1, bank_1);
            Sens_Loc = Get_Extreme_Temprature(min_select, 2, bank_1);

            printf("\nThe Minimum Temperature in this bank is: %f at IC %f and sensor %f\n", Data, IC_Loc, Sens_Loc);
// GET_EXTREME TEMP is not working  need to check if it is workoing in BM file or just a issue when it is passing it to another file.
            Data = Max_Temp[0][0];
            IC_Loc = Max_Temp[0][1];
            Sens_Loc = Max_Temp[0][2];
            printf("The Maximum Temperature in this bank is: %f at IC %f and sensor %f\n\n", Data, IC_Loc, Sens_Loc);
        }
        else if (bank == bank_2) {
            Data = Get_Extreme_Temprature(min_select, 0, bank_2);
            IC_Loc = Get_Extreme_Temprature(min_select, 1, bank_2);
            Sens_Loc = Get_Extreme_Temprature(min_select, 2, bank_2);

            printf("\nThe Minimum Temperature in this bank is: %f at IC %f and sensor %f\n", Data, IC_Loc, Sens_Loc);

            Data = Get_Extreme_Temprature(max_select, 0, bank_2);
            IC_Loc = Get_Extreme_Temprature(max_select, 1, bank_2);
            Sens_Loc = Get_Extreme_Temprature(max_select, 2, bank_2);

            printf("The Maximum Temperature in this bank is: %f at IC %f and sensor %f\n\n", Data, IC_Loc, Sens_Loc);
        }

    }

}