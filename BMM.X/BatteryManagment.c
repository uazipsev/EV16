/*******************************************************************
 * @brief           BatteryManagment.c
 * @brief           Adds easy to use functions to the LTC6804.c
 * @return          EU
 * @note            The lib is writen for US
 *******************************************************************/
#include <math.h>
#include "BatteryManagment.h"
#include "BatteryManagmentPrivate.h"
#include "BatteryManagementTemperature.h"
#include "BatteryManagementCells.h"
#include "ADS1015.h"
#include "LT6804.h"
#include "Timers.h"
#include <stdbool.h>
#include "Communications.h"
//TODO Need to make a fault status and a use with var
int Battery_Is_Charging_Flag = 0;
int FaultValue = 0;
bool BypassConfigbank1[NUMBEROFIC][12];
bool BypassConfigbank2[NUMBEROFIC][12];
double bankforc = 0;
int qw = 0;
 int Type_Of_State=0;
//|r_config[0]|r_config[1]|r_config[2]|r_config[3]|r_config[4]|r_config[5]|r_config[6]  |r_config[7] |r_config[8]|r_config[9]|  .....    |
//|-----------|-----------|-----------|-----------|-----------|-----------|-------------|------------|-----------|-----------|-----------|
//|IC1 CFGR0  |IC1 CFGR1  |IC1 CFGR2  |IC1 CFGR3  |IC1 CFGR4  |IC1 CFGR5  |IC1 PEC High |IC1 PEC Low |IC2 CFGR0  |IC2 CFGR1  |  .....    |

/*******************************************************************
 * @brief           Start_BMS
 * @brief           Setup The BMS and set configs
 * @return          none
 * @note            
 *******************************************************************/

//TODO need to get communication protocol setup to run  the appropriate mode



void Start_BMS(int mode) {
    //TODO need to have a mode to make sure all slaves are up in running.

    LTC6804_initialize(); //LT Code to setup up the spi and AtoD configuration for the LTc684
    Configure_LT6804(); //Configure and send pramaters to LTC6804
    ADS1015Begin();
    if (mode == 1) {
            Type_Of_State=0;
    }
    if (mode == 2) {  
        //if in charge mode 
        Battery_Is_Charging_Flag = 1;
    Send_To_Charger(Battery_Is_Charging_Flag, Voltage_Charge, Amps_Charge);
    }

}

void Charge_Mode() {
    
    //If we indicate a bypass has happened. Stop the Charger.
    FaultValue = Run_ByPass(cell_codes_Bank1, cell_codes_Bank2);
    if (FaultValue == 1) {
        //Tell Charger to stop
        Send_To_Charger(0, Voltage_Charge, Amps_Charge);
    }
    // Open_All_ByPass();

}

void Run_Mode(bool Start_Setup) {
    //This is used to start the process of the switch statement.
    if  (Start_Setup==true){
    
        
    Type_Of_State=0;
    }
    

    wakeup_idle();
    
    int Fault_Type=0;
    //Read_Total_Voltage(cell_codes_Bank1, cell_codes_Bank2);

    //Read_Total_GPIO(Aux_codes_Bank1,Aux_codes_Bank2);
       if (0) {
    switch (Type_Of_State) {
        case 0:
           Fault_Type= Read_GPIO_Bank(Aux_codes_Bank1);
            break;
        case 1:
           Fault_Type= Read_GPIO_Bank(Aux_codes_Bank2);
            break;
        case 2:
           Fault_Type= Convert_To_Temp_Total(Aux_codes_Bank1, Aux_codes_Bank2);
            break;
        case 3:
          Fault_Type= Read_Cell_Voltage_Bank(cell_codes_Bank1);
            break;
        case 4:
          Fault_Type= Read_Cell_Voltage_Bank(cell_codes_Bank2);
            break;
        case 5:
          Fault_Type= Insert_Cell_Data_Total(cell_codes_Bank1,cell_codes_Bank2);
            break;
        case 6:
            Pack_Cell_Voltage_Sum();
            Pack_Temperature_Sum();
            break;
        case 7:
            Pack_Cell_Voltage_Sum();
            Pack_Temperature_Sum();
            break;
         case 8:
            Pack_Cell_Voltage_Sum();
            Pack_Temperature_Sum();
            break;    
    }
       }
    //Report_Fault(Fault_Type);
    //CheckFault();
    
    // Type_Of_State++;
     //if (Type_Of_State==6){
     //Type_Of_State=0;
     //Read_Total_Temperature(Aux_codes_Bank1, Aux_codes_Bank2);
     Send_Read_GPIO_Command(0, Aux_codes_Bank1);
//Read_GPIO_Bank(Aux_codes_Bank1);
 //Convert_To_Temp_Total(Aux_codes_Bank1, Aux_codes_Bank2);

    //    FaultValue=Startuptests(Stat_codes_Bank1);
    //    FaultValue=Startuptests(Stat_codes_Bank2);
    //    if (FaultValue!=0){
    //        CheckFault();
    //    }
    //    else {
    //        Run_GPIO_Temp_ColumbCounting_Timer();
    //    }
}

     
     void Run_Mode_debug(bool Start_Setup) {
    //This is used to start the process of the switch statement.
    if  (Start_Setup==true){
    
        
    Type_Of_State=0;
    }
    

    wakeup_idle();
    
    int Fault_Type=0;
    //Read_Total_Voltage(cell_codes_Bank1, cell_codes_Bank2);

    //Read_Total_GPIO(Aux_codes_Bank1,Aux_codes_Bank2);
       if (0) {
    switch (Type_Of_State) {
        case 0:
           Fault_Type= Read_GPIO_Bank(Aux_codes_Bank1);
            break;
        case 1:
           Fault_Type= Read_GPIO_Bank(Aux_codes_Bank2);
            break;
        case 2:
           Fault_Type= Convert_To_Temp_Total(Aux_codes_Bank1, Aux_codes_Bank2);
            break;
        case 3:
          // Fault_Type= Convert_To_Temp_Total(Aux_codes_Bank1, Aux_codes_Bank2);
            break;
        case 4:
           //Fault_Type= Test_Temp_Sensors(Aux_codes_Bank1, Aux_codes_Bank2, Aux_codes_Bank1[6][0]);
            break;
        case 5:
           //Fault_Type= Test_Temp_Sensors(Aux_codes_Bank1, Aux_codes_Bank2, Aux_codes_Bank1[6][0]);
            break;
    }
       }
    //CheckFault();
    
    // Type_Of_State++;
     //if (Type_Of_State==6){
     //Type_Of_State=0;
     //Read_Total_Temperature(Aux_codes_Bank1, Aux_codes_Bank2);
     Send_Read_GPIO_Command(0, Aux_codes_Bank1);
//Read_GPIO_Bank(Aux_codes_Bank1);
 //Convert_To_Temp_Total(Aux_codes_Bank1, Aux_codes_Bank2);

    //    FaultValue=Startuptests(Stat_codes_Bank1);
    //    FaultValue=Startuptests(Stat_codes_Bank2);
    //    if (FaultValue!=0){
    //        CheckFault();
    //    }
    //    else {
    //        Run_GPIO_Temp_ColumbCounting_Timer();
    //    }

}



void Run_GPIO_Temp_ColumbCounting_Timer() {
    initTimerTwo();
}
void Check_Fault(int fault_name){
    switch(fault_name){
    
        case 0:
            break;
    
    
    }
    
    
 if (FaultValue != 0) {   ;
    Saftey_Relay_Set = 1;
    //TODO Need Delay
    Saftey_Relay_Set=0;
    }
//    FaultValueHistory=FaultValue;
    FaultValue=0;
   }




/*******************************************************************
 * Funcion Name     Configure_LT6804
 * @Parameters      N/A
 * @return          N/A
 * 
 * @note            Sets and changes the values of the LTC6804_DATA_ConfigBanks.
 *                  This is meant to be sent to each LTC6804 config register
 *                  to setup each LTC6804 correctly to get data.         
 *******************************************************************/

void Configure_LT6804() {
    int IC = 0;
    int bank = 1;
    int Bank_Select;
    //set values to arrays for max and min
    //Selecting bank 0=bank 1   1=bank 2
    for (Bank_Select=0; Bank_Select < 2; Bank_Select++) {
        Min_Temp[Bank_Select][Data_Value] = 100;
        Max_Temp[Bank_Select][Data_Value] =0;
        Min_Cell_Voltage[Bank_Select][Data_Value] = 100;
        Max_Cell_Voltage[Bank_Select][Data_Value] = 0;
    }

    //      for ( i = 0; i<NUMBEROFIC; i++)  {
    //      LTC6804_DATA_ConfigBank1[i][0]= CFGR0 | }
    while (bank < NUMBEROFCH) {
        while (IC < NUMBEROFIC) {
            Set_REFON_Pin(bank, IC, 1);
            Set_ADC_Mode(bank, IC, 0);
            Set_DCC_Mode_OFF(bank, IC);
            Set_DCTO_Mode_OFF(bank, IC);
            //SetTempEnable(bank, IC, 1);
            SetUnderOverVoltage(Under_Voltage_Value_LTC, Over_Voltage_Value_LTC, bank, IC);
            //This is hardcoded need to see if this can be implemented.
            LTC6804_DATA_ConfigBank1[IC][0] = 0xFE;
            LTC6804_DATA_ConfigBank2[IC][0] = 0xFE;
            IC++;
        };
        bank++;
    }
    UpdateLT6804(1);
    //UpdateLT6804(2);
}

//TODO Finish Up setup Test
int Startuptests(int Stat_codes[NUMBEROFIC][6]) {
    int ReadErrorValue = 0; //If there is a error reading the statregister
    int ErrorCount = 0; //How many times in a row was there a error this can indicate a loop that is stuck.
    int CriticalReadError = 0; // If over 10 Send a Critical Error to be dealt with. 
    Set_Stat(MD_NORMAL, All_Stats);
    do {
        LTC6804_ADSTAT();
        ReadErrorValue = LTC6804_rdStat(0, NUMBEROFIC, Stat_codes);// This sends 2 bytes and combines them. 
        if (ReadErrorValue != 0) {                                 // Instead of one thus you only have 6 registers for 12 bytes.
            ErrorCount = ErrorCount + 1;
        }
    }    while (ReadErrorValue != 0 && ErrorCount < 10); //Do ten time if not critical error
//If over 10 times report critical error
    if (ErrorCount >= 10) { 
        CriticalReadError = ReadstatRegFault;
        return CriticalReadError;
    }
    //Else data sent was good check data.
    if (ReadErrorValue == 0) {
        FaultValue = CheckTestReading(Stat_codes);
        return FaultValue;
    }
    //This should never get down here.
    return -1; // If this happends something wrong happened in the function.
}

int CheckTestReading(int Stat_codes[NUMBEROFIC][6]) {
    int TestError = 0; //This error will bring up the first error it sees. 
    int IC = 0;
    while (IC < NUMBEROFIC) {

        //Sum_Of_Cells
        int soc = 0;
        int Sum_Of_Cells = 0;
        soc = Stat_codes[NUMBEROFIC][0]; 
        Sum_Of_Cells = (soc * (100 * pow(10, -6))*20); 
        
        
        //Vminus Pin ask Richard what this means
        if (TestError == 0) {
            //Internal Die Temprature
            int itmp = 0;
            double Internal_Die_Temprature = 0;
            itmp = Stat_codes[NUMBEROFIC][1];
            Internal_Die_Temprature = (itmp * ((100 * pow(10, -6)) / (7.5 * pow(10, -3))) - 273);
            //TODO ask Richard what the temprature needs to be.
        }
        if (TestError == 0) {
            //Analog Power Supply 
            int va = 0;
            int Analog_Supply_Power = 0;
            va = Stat_codes[NUMBEROFIC][2];
            Analog_Supply_Power = (soc * (100 * pow(10, -6)));
            if ((Analog_Supply_Power < 4.5) || (Analog_Supply_Power > 5.5)) {
                TestError = AnalogPowerSupplyFault;
            }
        }
        if (TestError == 0) {
            //Digital Power Supply 
            int vd = 0;
            int Digital_Supply_Power = 0;
            vd = Stat_codes[NUMBEROFIC][3];
            Digital_Supply_Power = (soc * (100 * pow(10, -6))); //TODO CHECK WHY THERE IS SOC
            if ((Digital_Supply_Power < 2.7) || (Digital_Supply_Power > 3.6)) {
                TestError = DigitalPowerSupplyFault;
            }
        }
        if (TestError == 0) {
            //Under and Over Voltage errors
            
            //This is crazy we need to improve this idea. Probably use a % operation.
            int BoolValues = 0; // Bools values of the cells to indicate if there is a over/under voltage fault.
            BoolValues = Stat_codes[NUMBEROFIC][4];
            //Going through each bit and determining a fault. 
            int incrementer = 0;
            while (incrementer <= 15) {
                bool CheckValue = BoolValues && ((0x1) << incrementer); //Check << if this is power 
                switch (incrementer) {
                    case 0:
                        if (CheckValue == 1) {
                            TestError = UnderVoltageFault;
                        }
                        break;
                    case 1: if (CheckValue == 1) {
                            TestError = OverVoltageFault;
                        }
                        break;
                    case 2: if (CheckValue == 1) {
                            TestError = UnderVoltageFault;
                        }
                        break;
                    case 3: if (CheckValue == 1) {
                            TestError = OverVoltageFault;
                        }
                        break;
                    case 4: if (CheckValue == 1) {
                            TestError = UnderVoltageFault;
                            ;
                        }
                        break;
                    case 5: if (CheckValue == 1) {
                            TestError = OverVoltageFault;
                        }
                        break;
                    case 6: if (CheckValue == 1) {
                            TestError = UnderVoltageFault;
                            ;
                        }
                        break;
                    case 7: if (CheckValue == 1) {
                            TestError = OverVoltageFault;
                        }
                        break;
                    case 8:
                        if (CheckValue == 1) {
                            TestError = UnderVoltageFault;
                        }
                        break;
                    case 9: if (CheckValue == 1) {
                            TestError = OverVoltageFault;
                        }
                        break;
                    case 10: if (CheckValue == 1) {
                            TestError = UnderVoltageFault;
                        }
                        break;
                    case 11: if (CheckValue == 1) {
                            TestError = OverVoltageFault;
                        }
                        break;
                    case 12: if (CheckValue == 1) {
                            TestError = UnderVoltageFault;
                            ;
                        }
                        break;
                    case 13: if (CheckValue == 1) {
                            TestError = OverVoltageFault;
                        }
                        break;
                    case 14: if (CheckValue == 1) {
                            TestError = UnderVoltageFault;
                            ;
                        }
                        break;
                    case 15: if (CheckValue == 1) {
                            TestError = OverVoltageFault;
                        }
                        break;

                }
                incrementer = incrementer + 1;
                if (CheckValue == 1) {
                    return TestError;
                }
                CheckValue = 0;
            }
        }
        if (TestError == 0) {
            //Under and Over Voltage errors and muxFail and THSD
            int BoolValues = 0; // Bools values of the cells to indicate if there is a over/under voltage or other faults
            BoolValues = Stat_codes[NUMBEROFIC][5];
            //Going through each bit and determining a fault. 
            int incrementer = 0;
            while (incrementer <= 8) {
                bool CheckValue = BoolValues && ((0x1) << incrementer);

                switch (incrementer) {
                    case 0:
                        if (CheckValue == 1) {
                            TestError = UnderVoltageFault;
                        }
                        break;
                    case 1: if (CheckValue == 1) {
                            TestError = OverVoltageFault;
                        }
                        break;
                    case 2: if (CheckValue == 1) {
                            TestError = UnderVoltageFault;
                        }
                        break;
                    case 3: if (CheckValue == 1) {
                            TestError = OverVoltageFault;
                        }
                        break;
                    case 4: if (CheckValue == 1) {
                            TestError = UnderVoltageFault;
                            ;
                        }
                        break;
                    case 5: if (CheckValue == 1) {
                            TestError = OverVoltageFault;
                        }
                        break;
                    case 6: if (CheckValue == 1) {
                            TestError = UnderVoltageFault;
                            ;
                        }
                        break;
                    case 7: if (CheckValue == 1) {
                            TestError = OverVoltageFault;
                        }
                        break;
                        // Thermal ShutDown Value
                    case 8:
                        if (CheckValue == 1) {
                            TestError = ThermalShutdownFault;
                        }
                        break;
                        //MUX FAIL
                    case 9: if (CheckValue == 1) {
                            TestError = Muxfailfault;
                        }
                        break;

                }
                incrementer = incrementer + 1;
                if (CheckValue == 1) {
                    return TestError;
                }
                CheckValue = 0;
            }
        }
        IC = IC + 1;
        if (TestError != 0) {
            return TestError;
        }
    }
    return TestError;
}



/*******************************************************************
 * @brief           Set_Bypass
 * @brief           sets bypass for a cell on the stack
 * @return          none
 * @note            
 *******************************************************************/

//Clears the Max and Min values for every run.

void Re_Initialize_Extreme_Values() {
    int Bank_Select;
    for (Bank_Select=0; Bank_Select < 2; Bank_Select++) {
        Min_Temp[Bank_Select][Data_Value] = 100;
        Max_Temp[Bank_Select][Data_Value] = 0;
        Min_Cell_Voltage[Bank_Select][Data_Value] = 100;
        Max_Cell_Voltage[Bank_Select][Data_Value] = 0;
    }
    ;
}




int Run_ByPass(int cell_codesBank1[][12], int cell_codesBank2[][12]) {
    //int bypass_flag = 0;
    while (Battery_Is_Charging_Flag == 1) {
        Battery_Is_Charging_Flag = 0; // If this flag is tripped that means there is a cell that need more voltage. 
        int Read_Status_INC = 0;
        //To detect error values
        int Error_Value = 0;
        //Bank1
        do {
            Error_Value = Send_Read_CellV_Command(0, cell_codes_Bank1);
            if (Error_Value != 0) {
                Read_Status_INC = Read_Status_INC + 1;
            }
        } while (Error_Value != 0 && Read_Status_INC < 10);
        if (Read_Status_INC >= 10) {
            return ReadVoltRegFault;
        }
        else if (Read_Status_INC < 10) {
            Read_Status_INC = 0;
        }
        //Bank2
        do {
            Error_Value = Send_Read_CellV_Command(0, cell_codesBank2);
            if (Error_Value != 0) {
                Read_Status_INC = Read_Status_INC + 1;
            }
        } while (Error_Value != 0 && Read_Status_INC < 10);

        if (Read_Status_INC >= 10) {
            return ReadVoltRegFault;
        }
        //Convert_To_Voltage_Cell(cell_codesBank1, cell_codesBank2);
        //RunBypass

       // bypass_flag = RunBypass_Set(bank_1, Converted_Cell_Codes_Bank1);
       // bypass_flag = RunBypass_Set(bank_2, Converted_Cell_Codes_Bank2);
    }
    T3CONbits.TON = 0;
    //hold LED HIGH that indicates charging
    return 0;

}

/*******************************************************************
 * @brief           RunBypass
 * @brief           Controls bypass algorithm for pack
 * @return          it returns a value indicating that there is a bypass that is still enabled.
 * @note            
 *******************************************************************/
int RunBypass_Set(int bank, double Conv_Cell_Codes[][12]) {
    int cellbyp = 0;
    int batvolt = 0;
    int Ic; // Increment for IC
    int Cell; // Increment for Cells
    // Want to make a function for all Batterys Right now it works with just 1 IC
    // Need to understand how he Bank IC and Cell system works 

    for (Ic = 0; Ic < NUMBEROFIC; Ic++) {

        for (Cell = 0; Cell < Cell_Per_Bank; Cell++) // runs threw num of batteries
        {
            batvolt = TestThreshold(OverVoltageFault, Conv_Cell_Codes[Ic][Cell]);
            if (batvolt == 0) // if bypass needs enabled..
            {
                SetBypass(bank, Ic, Cell, false); // sets bypass off
                Battery_Is_Charging_Flag = 1;
            }
            if (batvolt == OverVoltageFault) 
            {
                SetBypass(bank, Ic, Cell, true); // sets bypass on
                cellbyp = 1;
            }
        }
    }
    UpdateLT6804(bank);
    return cellbyp;
}


/*******************************************************************
 * @brief           Set Bypass
 * @brief           Sets the bypass for the conifg register
 * @return          Return the constant NoBankselected if there is a error in sending a invalid bank 
 * @note            
 *******************************************************************/
int SetBypass(int bank, int ic, int cell, bool value) {
    int fault_value = 0;
    if (value) {
        if (cell < 8) {
            CFGR4 = CFGR4 | (1 << cell); //This sets the cell on the stack to on when less than 8 
        } else {
            CFGR5 = CFGR5 | (1 << (cell - 8)); //This sets the cell on the stack to on when > 8
        }
    }
    else {
        if (cell < 8) {
            CFGR4 = CFGR4 & ~(1 << cell); //This sets the cell on the stack to off when less than 8
        } else {
            CFGR5 = CFGR5 & ~(1 << (cell - 8)); //This sets the cell on the stack to off when > 8
        }
    }
    if (bank == 0) {
        LTC6804_DATA_ConfigBank1[ic][4] = CFGR4; //First  8 Bits of DCC
        LTC6804_DATA_ConfigBank1[ic][5] = (CFGR5) + (DCTO << 4);
    }// Combined DCTO and the Last 4 bits of DCC
    else if (bank == 1) {
        LTC6804_DATA_ConfigBank2[ic][4] = CFGR4; //First  8 Bits of DCC
        LTC6804_DATA_ConfigBank2[ic][5] = (CFGR5) + (DCTO << 4);
    }// Combined DCTO and the Last 4 bits of DCC}
    else {
        fault_value = NoBankselected;
    }
    return fault_value;
}

void Open_All_ByPass()//This function is to open all ByPasses
{
    int Ic = 0; // Increment for IC
    int Cell = 0; // Increment for Cells
    int bank = 0;
    for (bank = 1; bank < 2; bank++) {
        for (Ic = 0; Ic < NUMBEROFIC; Ic++) {

            for (Cell = 0; Cell < Cell_Per_Bank; Cell++) // runs threw num of batteries
            {
                SetBypass(bank, Ic, Cell, false); // sets bypass off
            }
        }
    }
}

/*******************************************************************
 * @brief           SetTempEnable
 * @brief           This enables the power to the temp measurements
 * @return          none
 * @note            
 *******************************************************************/


int SetTempEnable(int bank, int ic, bool value) {
    int fault_value = 0;
    if (value) {
        CFGR0 = CFGR0 | (1 << 7); //Turn on GPIO 5
    } else {
        CFGR0 = CFGR0 & ~(1 << 7); //Turn off GPIO 5
    }

    if (bank == 1) {
        LTC6804_DATA_ConfigBank1[ic][0] = CFGR0;
    } else if (bank == 2) {
        LTC6804_DATA_ConfigBank2[ic][0] = CFGR0;
    } else {
        return fault_value = NoBankselected;
    }

    return fault_value;
}

/*******************************************************************
 * @brief           SetUnderOverVoltage
 * @brief           This will set the UV and OV for all the IC's and banks
 * @return          none
 * @note            
 *******************************************************************/

//Update Under and over voltages. 

int SetUnderOverVoltage(int VUV, int VOV, int bank, int ic) {
    int fault_value = 0;
    //LTC6804 - PG: 49 
    CFGR1 = VUV & 0xFF; // Ands with the First 8 bits
    CFGR2 = ((VUV & 0xF00) >> 8)+ ((VOV & 0x0F) << 4); // Finish Last bits of VUV start with VOV
    CFGR3 = (VOV & 0xFF0) >> 4; // Finish VOV setup

    // load up static reg
    if (bank == 1) {
        LTC6804_DATA_ConfigBank1[ic][1] = CFGR1;
        LTC6804_DATA_ConfigBank1[ic][2] = CFGR2;
        LTC6804_DATA_ConfigBank1[ic][3] = CFGR3;
    } else if (bank == 2) {
        LTC6804_DATA_ConfigBank2[ic][1] = CFGR1;
        LTC6804_DATA_ConfigBank2[ic][2] = CFGR2;
        LTC6804_DATA_ConfigBank2[ic][3] = CFGR3;
    } else {
        fault_value = NoBankselected;
    }
    return fault_value;
}

/*******************************************************************
 * @brief           Set_ADC_Mode
 * @brief           This will set the UV and OV for all the IC's and banks
 * @return          none
 * @note            
 *******************************************************************/

//Not Sure how this  LTC6804_DATA works however will copy for consistency 

int Set_ADC_Mode(int bank, int ic, bool ADCOPT_Mode) {
    int fault_value = 0;
    if (ADCOPT_Mode) {
        CFGR0 = CFGR0 | ADC_MODE_BIT_14k_3k_2k;
    } else {
        CFGR0 = CFGR0 & ~ADC_MODE_BIT_14k_3k_2k; //ADC_MODE_BIT_27k_7k_26
    }
    if (bank == 1) {
        LTC6804_DATA_ConfigBank1[ic][0] = CFGR0;
    } else if (bank == 2) {
        LTC6804_DATA_ConfigBank2[ic][0] = CFGR0;
    } else {
        fault_value = NoBankselected;
    }
    return fault_value;
}

int Set_DCC_Mode_OFF(int bank, int ic) {
    int fault_value = 0;
    CFGR4 = 0;
    CFGR5 = CFGR5 &~(0xF);
    if (bank == 1) {
        LTC6804_DATA_ConfigBank1[ic][4] = CFGR4;
        LTC6804_DATA_ConfigBank1[ic][5] = CFGR5;
    } else if (bank == 2) {
        LTC6804_DATA_ConfigBank2[ic][4] = CFGR4;
        LTC6804_DATA_ConfigBank2[ic][5] = CFGR5;
    } else {
        fault_value = NoBankselected;
    }
    return fault_value;
}

int Set_DCTO_Mode_OFF(int bank, int ic) {
    int fault_value = 0;
    CFGR5 = CFGR5 &~(0xF0);
    if (bank == 1) {
        LTC6804_DATA_ConfigBank1[ic][5] = CFGR5;
    } else if (bank == 2) {
        LTC6804_DATA_ConfigBank2[ic][5] = CFGR5;
    } else {
        fault_value = NoBankselected;
    }
    return fault_value;
}

/******************************************************************************
 * Funcion Name     Set_REFON_Pin
 * @Parameters      bank (int)          -To select the correct bank to update
 *                                       the write configuration registers.
 * 
 *                  ic (int)            -To update the right LTC6804 IC in the 
 *                                       configuration registers. 
 * 
 *                  REFON_Mode (bool)   -To update the right LTC6804 IC in the 
 *                                       configuration registers.                         
 * @return          N/A
 * 
 * @note            Sets and changes the bit for the reference voltage of a 
 *                  LTC6804. This is meant to be sent to each LTC6804 config 
 *                  register.
 *                          
 *******************************************************************************/
int Set_REFON_Pin(int bank, int ic, bool REFON_Mode) {
    int fault_value = 0;
    if (REFON_Mode) {
        CFGR0 = CFGR0 | REFON_TURN_ON;
    } else {
        CFGR0 = CFGR0 & ~REFON_TURN_ON; //REFOFF_TURN_OFF
    }
    if (bank == 1) {
        LTC6804_DATA_ConfigBank1[ic][0] = CFGR0;
    } else if (bank == 2) {
        LTC6804_DATA_ConfigBank2[ic][0] = CFGR0;
    } else {
        fault_value = NoBankselected;
    }
    return fault_value;
}

int UpdateLT6804(int bank) {
    int fault_value = 0;
    if (bank == 1) {
        LTC6804_wrcfg(NUMBEROFIC, LTC6804_DATA_ConfigBank1);
    } else if (bank == 2) {
        LTC6804_wrcfg(NUMBEROFIC, LTC6804_DATA_ConfigBank2);
    } else {
        fault_value = NoBankselected;
    }
    return fault_value;
}

/*******************************************************************
 * @brief           ReadCurrentVolt
 * @brief           Reads in the ADC counts from the current sense PCB
 * @return          none
 * @note            This populates the array with raw ADC values
 *******************************************************************/
void ReadCurrentVolt() {
    CVolt[0] = ADS1015readADC_SingleEnded(0, 0x49); //Set channel and IC
    CVolt[1] = ADS1015readADC_SingleEnded(1, 0x49);
    CVolt[2] = ADS1015readADC_SingleEnded(2, 0x49);
    CVolt[3] = ADS1015readADC_SingleEnded(3, 0x49);
    CVolt[4] = ADS1015readADC_SingleEnded(0, 0x48);
    CVolt[5] = ADS1015readADC_SingleEnded(1, 0x48);
    ReadVoltToCurrent(); //Converts ADC counts to amps
    ReadVolt();
}

/*******************************************************************
 * @brief           ReadVolt
 * @brief           Reads in the ADC counts and converts to voltages 
 * @return          none
 * @note            Gets it ready for a traditional getter
 *******************************************************************/

void ReadVolt() {
    Volt1 = ADS1015readADC_SingleEnded(2, 0x48);
    Volt2 = ADS1015readADC_SingleEnded(3, 0x48);
    Volt1 = (Volt1*(0.125*158)/1000);
    Volt2 = (Volt2*(0.125*158)/1000);
}

/*******************************************************************
 * @brief           ReadVoltToCurrent
 * @brief           converts ADC counts to amps
 * @return          none
 * @note            Gets it ready for a traditional getter
 *******************************************************************/
// FIXME Need to simplify the ADC convert 1 ADC count = 1mV

void ReadVoltToCurrent() {
    for (k = 0; k < 5; k++) {
        //TODO: Remove for production firmware
        Current[k] = ((CVolt[k] / ADCBIT)*5); ///SHUNTOHMS/CURRENTGAIN) + CurrentOffset[k];
    }
}


/*******************************************************************
 * @brief           ChargerEN
 * @brief           Tells the BMS system that the charger is connected
 * @return          none
 * @note            Sets flag for reading
 *******************************************************************/

void ChargerEN() {

    CarOn = 1;
}

bool ChargerVal() {
    return CarOn;
}

/*******************************************************************
 * @brief           CurrentCoulombCount
 * @brief           This function "should" get us a coulomb count (I hope)
 * @return          none
 * @note            This fcn is controlled by a timer for a true CC (timer 2) 
 *******************************************************************/

void CurrentCoulombCount(int tme) {
    if (CarOn) { //Positive charing current
        CC1 = CC1 - (Current[0] * tme);
        CC2 = CC2 - (Current[2] * tme);
        CC3 = CC3 - (Current[4] * tme);
    } else { //negative discharging current  
        CC1 = CC1 + (Current[1] * tme);
        CC2 = CC2 + (Current[3] * tme);
        CC3 = CC3 + (Current[5] * tme);
    }
}

/*******************************************************************
 * @brief           CurrentGet
 * @brief           getter
 * @return          none
 * @note            This can give you a different response depending on input
 *******************************************************************/

double CurrentGet(bool total, char channel) {
//    if (total) {
//        if (CarOn) {
//            return Current[0] + Current[2] + Current[4];
//        } else {
//            return Current[1] + Current[3] + Current[5];
//        }
//    } else {
        if (total) {
            switch (channel) {
                case 1:
                    return Current[0];
                    break;
                case 2:
                    return Current[2];
                    break;
                case 3:
                    return Current[4];
                    break;
            }
        } else {
            switch (channel) {
                case 1:
                    return Current[1];
                    break;
                case 2:
                    return Current[3];
                    break;
                case 3:
                    return Current[5];
                    break;
            }
        //}

    }
    return -1;
}

/*******************************************************************
 * @brief           VoltGet
 * @brief           getter
 * @return          none
 * @note            This can give you a different response depending on input
 *******************************************************************/

double VoltGet(char channel) {
    if (channel) {
        return Volt1;
    }
    else {
        return Volt2;
    }
}