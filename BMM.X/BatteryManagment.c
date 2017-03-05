/*******************************************************************
 * @brief           BatteryManagment.c
 * @brief           Adds easy to use functions to the LTC6804.c
 * @return          EU
 * @note            The lib is writen for US
 *******************************************************************/
#include <math.h>
#include "BatteryManagment.h"
#include "BatteryManagmentPrivate.h"
#include "ADS1015.h"
#include "LT6804.h"
#include "Timers.h"
#include <stdbool.h>
//TODO Need to make a fault status and a use with var
int Battery_Is_Charging_Flag = 0;
int FaultValue = 0;
//Arrays for Cell Voltages
int cell_codes_Bank1[NUMBEROFIC][12];
int cell_codes_Bank2[NUMBEROFIC][12];
double Converted_Cell_Codes_Bank1[NUMBEROFIC][12];
double Converted_Cell_Codes_Bank2[NUMBEROFIC][12];
double Average_cell_codes_Bank1[NUMBEROFIC][12];
double Average_cell_codes_Bank2[NUMBEROFIC][12];

//Arrays for GPIO
int Aux_codes_Bank1[NUMBEROFIC][6];
int Aux_codes_Bank2[NUMBEROFIC][6];
double Converted_Temprature_Bank1[NUMBEROFIC][6];
double Converted_Temprature_Bank2[NUMBEROFIC][6];
double Average_Temprature_Codes_Bank1[NUMBEROFIC][6];
double Average_Temprature_Codes_Bank2[NUMBEROFIC][6];
double Module_Voltage_Value[1][2];
double Module_Average_Temp_Value[1][2];
bool BypassConfigbank1[NUMBEROFIC][12];
bool BypassConfigbank2[NUMBEROFIC][12];
double bankforc = 0;
int qw = 0;
 double Min_Temp[2][3];
 double Max_Temp[2][3];
 double Min_Cell_Voltage[2][3];
 double Max_Cell_Voltage[2][3];
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

int Comm_Start() {

    return 1;
}

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
        
    switch (Type_Of_State) {
        case 0:
          // Fault_Type= Read_GPIO_Bank(Aux_codes_Bank1);
            break;
        case 1:
           //Fault_Type= Read_GPIO_Bank(Aux_codes_Bank2);
            break;
        case 2:
           //Fault_Type= Test_Temp_Sensors(Aux_codes_Bank1, Aux_codes_Bank2, Aux_codes_Bank1[6][0]);
            break;
        case 3:
           //Fault_Type= Test_Temp_Sensors(Aux_codes_Bank1, Aux_codes_Bank2, Aux_codes_Bank1[6][0]);
            break;
        case 4:
           //Fault_Type= Test_Temp_Sensors(Aux_codes_Bank1, Aux_codes_Bank2, Aux_codes_Bank1[6][0]);
            break;
        case 5:
           //Fault_Type= Test_Temp_Sensors(Aux_codes_Bank1, Aux_codes_Bank2, Aux_codes_Bank1[6][0]);
            break;
    }
    //CheckFault();
    
    // Type_Of_State++;
     //if (Type_Of_State==6){
     //Type_Of_State=0;
     
     
Read_GPIO_Bank(Aux_codes_Bank1);
 Test_Temp_Sensors(Aux_codes_Bank1, Aux_codes_Bank2, Aux_codes_Bank1[6][0]);

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
Check_Fault(int fault_name){
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
    int Bank_Select = 0;
    //set values to arrays for max and min
    //Selecting bank 0=bank 1   1=bank 2
    for (Bank_Select; Bank_Select < 2; Bank_Select++) {
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



    ;
}


int Read_Total_Voltage(int cell_codesBank1[][12], int cell_codesBank2[][12]) {
    int Read_Status_INC = 0;
    int Error_Value = 0;
    int FaultNum = 0;
    //Reading the registers
    do {
        Error_Value = Read_Battery(0, cell_codes_Bank1);
        Error_Value = 0; //TODO Get rid of fault detection will break
        if (Error_Value != 0) {
            // printf("Error!!! 1 %i ", Read_Status_INC);
            // Read_Status_INC = Read_Status_INC + 1;
        }
    } while (Error_Value != 0 && Read_Status_INC <= 10);
    //If we cant read the registers 10 times in the row call a fault. 
    if (Read_Status_INC > 10) {
        //printf("Fault!!! 1 %i ");
        FaultNum = ReadVoltRegFault;
    }
    //If we got the data reset for bank 2
    Read_Status_INC = 0;
    do {
        Error_Value = Read_Battery(0, cell_codesBank2);
        Error_Value = 0; //TODO Get rid of fault detection will break
        if (Error_Value != 0) {
            //printf("Error!!! 2 %i ", Read_Status_INC);
            // Read_Status_INC = Read_Status_INC + 1;
        }

    } while (Error_Value != 0 && Read_Status_INC <= 10);
    if (Read_Status_INC > 10) {
        // printf("Fault!!! 2 %i ");
        FaultNum = ReadVoltRegFault;
    }
    //if there is no issues and we got data 
    if (FaultNum == 0) {
        //convert cells to volts.
        Convert_To_Voltage_Cell(cell_codes_Bank1, cell_codes_Bank2);
        //To stop first reading error
        //If this is the first read of the array dont check faults because the frst signal could be bad.
        if (Starting_Samples == true) {
            Update_Average_Array_Cell(Converted_Cell_Codes_Bank1, Converted_Cell_Codes_Bank2);
        } else if (Starting_Samples == false) {
            //Update array then check if the
            Update_Average_Array_Cell(Converted_Cell_Codes_Bank1, Converted_Cell_Codes_Bank2);
            FaultNum = Check_Array_Faults_Cells(Average_cell_codes_Bank1, Average_cell_codes_Bank2);
            if (FaultNum == 0) {
                //Sum the voltage up into each module and ready to be sent.
                Pack_Cell_Voltage_Sum(Average_cell_codes_Bank1, Average_cell_codes_Bank2);
            } else {
                Error_Value = FaultNum;
            }
        }
    }
    return Error_Value;
}


/*******************************************************************
 * @brief           Read_Battery
 * @brief           Reads battery voltage of each cell 
 * @return          none
 * @note            
 *******************************************************************/
int Read_Battery(int BatteryPlacement, int cell_codes[NUMBEROFIC][12]) {
    int Read_Status = 0;
    switch (BatteryPlacement) {
        //The proccess laid out in case 0 should be the same for the other cases.
        //The difference is which set of cells are going to be read where case 0 is all of the cells.
        case 0:
            //Setup the ADC for the request.
            set_adc(MD_FILTERED, DCP_DISABLED, CELL_CH_ALL, AUX_CH_ALL);
            //Alert the LTC6804
            wakeup_idle();
            //Send data
            LTC6804_adcv();
            //Alert the LTC6804
            wakeup_idle();
            //Read data
            Read_Status = LTC6804_rdcv(0, NUMBEROFIC, cell_codes);
            break;
            //Not Sure if these work Check library and see if the 1,3 or 0,NumofCell is correct one is wrong.
        case 1:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_1and7, AUX_CH_ALL);
            wakeup_idle();
            LTC6804_adcv();
            wakeup_idle();
            Read_Status = LTC6804_rdcv(1, 3, cell_codes); //Cell 1
            Read_Status = LTC6804_rdcv(3, 3, cell_codes); //Cell 7
            break;
        case 2:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_2and8, AUX_CH_ALL);
            wakeup_idle();
            LTC6804_adcv();
            wakeup_idle();
            Read_Status = LTC6804_rdcv(0, NUMBEROFIC, cell_codes); // Cell 2
            Read_Status = LTC6804_rdcv(3, NUMBEROFIC, cell_codes); //Cell 8
            break;
        case 3:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_3and9, AUX_CH_ALL);
            LTC6804_adcv();
            wakeup_idle();
            Read_Status = LTC6804_rdcv(0, NUMBEROFIC, cell_codes); // Cell 3
            Read_Status = LTC6804_rdcv(3, NUMBEROFIC, cell_codes); //Cell 9
            break;
        case 4:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_4and10, AUX_CH_ALL);
            LTC6804_adcv();
            wakeup_idle();
            Read_Status = LTC6804_rdcv(2, NUMBEROFIC, cell_codes); // Cell 4
            Read_Status = LTC6804_rdcv(4, NUMBEROFIC, cell_codes); //Cell 10
            break;
        case 5:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_5and11, AUX_CH_ALL);
            LTC6804_adcv();
            wakeup_idle();
            Read_Status = LTC6804_rdcv(2, NUMBEROFIC, cell_codes); // Cell 5
            Read_Status = LTC6804_rdcv(4, NUMBEROFIC, cell_codes); //Cell 11
            break;
        case 6:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_6and12, AUX_CH_ALL);
            LTC6804_adcv();
            wakeup_idle();
            Read_Status = LTC6804_rdcv(2, NUMBEROFIC, cell_codes); // Cell 6
            Read_Status = LTC6804_rdcv(4, NUMBEROFIC, cell_codes); //Cell 12
            break;
        default:
            Read_Status = ReadVoltRegFault;
            break;
    }
    return Read_Status;
}


//Function to check all the voltage thresholds in the pack. And assigning minimum and maximum values.
int Check_All_Cell_Thresholds(int test, int IC, double cell_codes_bank1[][12], double cell_codes_bank2[][12]) {
    int CurrentIC = 0;
    int cell = 0;
    int Error_Value = 0;
    int bank = 0;
    //Going through every bank, IC and cell
    while (bank < 2) {
        while (CurrentIC < IC) {
            while (cell < 12) {
                if (bank == 0) {
                    Error_Value = CheckThresholds(test, cell_codes_bank1[CurrentIC][cell]);
                    //Checking if the cell has the lowest voltage in the pack
                    if (cell_codes_bank1[CurrentIC][cell] < Min_Cell_Voltage[bank][Data_Value]) {
                    // Gathering location of the lowest IC.
                        Min_Cell_Voltage[bank][Data_Value] = cell_codes_bank1[CurrentIC][cell];
                        Min_Cell_Voltage[bank][IC_LOCATION] = CurrentIC;
                        Min_Cell_Voltage[bank][SENSOR_LOCATION] = cell;
                    }
                    //Checking if the cell has the highest voltage in the pack
                    else if (cell_codes_bank1[CurrentIC][cell] > Max_Cell_Voltage[bank][Data_Value]) {
                        // Gathering location of the Highest IC.
                        Max_Cell_Voltage[bank][Data_Value] = cell_codes_bank1[CurrentIC][cell];
                        Max_Cell_Voltage[bank][IC_LOCATION] = CurrentIC;
                        Max_Cell_Voltage[bank][SENSOR_LOCATION] = cell;
                    }
                    if (Error_Value != 0) {
                        return Error_Value;
                    }
                    cell = cell + 1;
                }
                //Have to repeat even though its redundant because of cell_codes_bank2
                else if (bank == 1) {
                    Error_Value = CheckThresholds(test, cell_codes_bank2[CurrentIC][cell]);
                    if (cell_codes_bank2[CurrentIC][cell] < Min_Cell_Voltage[bank][Data_Value]) {

                        Min_Cell_Voltage[bank][Data_Value] = cell_codes_bank2[CurrentIC][cell];
                        Min_Cell_Voltage[bank][IC_LOCATION] = CurrentIC;
                        Min_Cell_Voltage[bank][SENSOR_LOCATION] = cell;
                    } else if (cell_codes_bank2[CurrentIC][cell] > Max_Cell_Voltage[bank][Data_Value]) {

                        Max_Cell_Voltage[bank][Data_Value] = cell_codes_bank2[CurrentIC][cell];
                        Max_Cell_Voltage[bank][IC_LOCATION] = CurrentIC;
                        Max_Cell_Voltage[bank][SENSOR_LOCATION] = cell;
                    }
                    if (Error_Value != 0) {
                        return Error_Value;
                    }
                }
                cell = cell + 1;
            }

            cell = 0;
            CurrentIC = CurrentIC + 1;
        }
        cell=0;
        CurrentIC = 0;
        bank++;
    }
    return Error_Value;
}
//Checking if any of the voltages are critically low or high which would need to create a fault.
int CheckThresholds(int test, double data) {
    int FaultIndicator = 0;
    switch (test) {
        case OverVoltageFault:
            if (data >= Over_Voltage_Value)
                FaultIndicator = OverVoltageFault;
            break;
        case UnderVoltageFault:
            if (data <= Under_Voltage_Value) {
                FaultIndicator = UnderVoltageFault;
            }
            break;
    }
    return FaultIndicator;
}

int Check_Array_Faults_Cells(double cell_codes_Bank1[][12], double cell_codes_Bank2[][12]) {
    int Error_Value;
    Error_Value = Check_All_Cell_Thresholds(OverVoltageFault, NUMBEROFIC, Average_cell_codes_Bank1, Average_cell_codes_Bank2);
    if (Error_Value != 0) {
        return Error_Value;
    }
    Error_Value = Check_All_Cell_Thresholds(UnderVoltageFault, NUMBEROFIC, Average_cell_codes_Bank1, Average_cell_codes_Bank2);
    return Error_Value;

}

/*******************************************************************
 * @brief           Convert_Voltage
 * @brief           Convert each reading from a battery to volts. 
 * @return          none
 * @note            
 *******************************************************************/
//TODO make sure this is possible to have a array of 12 go into a array of 6

void Convert_To_Voltage_Cell(int Array_Bank1[][12], int Array_Bank2[][12]) {
    int ic = 0;
    int cell = 0;
    int Temp_ValB1 = 0;
    int Temp_ValB2 = 0;
    while (ic < NUMBEROFIC) {
        while (cell < Cell_Per_Bank) {
            Temp_ValB1 = Array_Bank1[ic][cell]*.0001;
            Temp_ValB2 = Array_Bank2[ic][cell]*.0001;
            Converted_Cell_Codes_Bank1[ic][cell] = Temp_ValB1;
            Converted_Cell_Codes_Bank2[ic][cell] = Temp_ValB2;
            cell++;
        }
        cell=0;
        ic++;
    }
}

//Making weighted average

void Update_Average_Array_Cell(double Array_Bank1[][12], double Array_Bank2[][12]) {
    int Ic = 0;
    int cell = 0;
    //If first sample there is no weighted needed because it is the first sample.

    if (Starting_Samples == true) {
        while (Ic < NUMBEROFIC) {
            while (cell < 12) {

                //Cell Voltages
                Average_cell_codes_Bank1[Ic][cell] = Array_Bank1[Ic][cell];
                Average_cell_codes_Bank2[Ic][cell] = Array_Bank2[Ic][cell];
                cell = cell + 1;
            }
            cell = 0;
            Ic = Ic + 1;
        }
        cell = 0;
        Ic = 0;
    } 
    else if (Starting_Samples == false) {
        while (Ic < NUMBEROFIC) {
            while (cell < 12) {

                Average_cell_codes_Bank1[Ic][cell] = (.8 * (Average_cell_codes_Bank1[Ic][cell])+ (.2 * Array_Bank1[Ic][cell]));
                Average_cell_codes_Bank2[Ic][cell] = (.8 * (Average_cell_codes_Bank2[Ic][cell]) +(.2 * Array_Bank2[Ic][cell]));
                cell = cell++;
            }
            cell = 0;
            Ic = Ic++;
        }
    }

}

//This function is to sum up the voltage of each cell(12) and each ltc6804(3) into a array for each module to be sent to the ECU
void Pack_Cell_Voltage_Sum(double Array_Bank1[][12], double Array_Bank2[][12]) {

    int ic = 0, sense_num = 0, Bank_Num = 0;
    //For both Banks
    while (Bank_Num < 2) {
        while (ic < 9) {
            switch (ic) {
                    //Each Module has 3 LTC6804 with 12 voltage cells a piece. Summing the total voltage for each module.
                case 0:
                case 1:
                case 2:
                    while (sense_num < 12) {
                        if (Bank_Num == 0) {
                            Module_Voltage_Value[Bank_Num][0] = Array_Bank1[ic][sense_num] + Module_Voltage_Value[Bank_Num][0];
                        }
                        if (Bank_Num == 1) {
                            Module_Voltage_Value[Bank_Num][0] = Array_Bank2[ic][sense_num] + Module_Voltage_Value[Bank_Num][0];
                        }
                        sense_num++;
                    }
                    sense_num = 0;
                    break;
                case 3:
                case 4:
                case 5:
                    while (sense_num < 12) {
                        if (Bank_Num == 0) {
                            Module_Voltage_Value[Bank_Num][1] = Array_Bank1[ic][sense_num] + Module_Voltage_Value[Bank_Num][1];
                        }
                        if (Bank_Num == 1) {
                            Module_Voltage_Value[Bank_Num][1] = Array_Bank2[ic][sense_num] + Module_Voltage_Value[Bank_Num][1];
                        }
                        sense_num++;
                    }
                    sense_num = 0;
                    break;
                case 6:
                case 7:
                case 8:
                    while (sense_num < 12) {
                        if (Bank_Num == 0) {
                            Module_Voltage_Value[Bank_Num][2] = Array_Bank1[ic][sense_num] + Module_Voltage_Value[Bank_Num][2];
                        }
                        if (Bank_Num == 1) {
                            Module_Voltage_Value[Bank_Num][2] = Array_Bank2[ic][sense_num] + Module_Voltage_Value[Bank_Num][2];
                        }
                        sense_num++;
                    }
                    sense_num = 0;
                    break;
            }
            ic++;
        }
        ic = 0;
        Bank_Num++;
    }
}

double Get_Cell_Voltages(int ic, int num, int bank) {
    if (bank == 1) {
        return Average_cell_codes_Bank1[ic][num];
    }
    if (bank == 2) {
        return Average_cell_codes_Bank2[ic][num];
    }
}

double Get_Pack_Voltages(int module, int bank) {
    if (module == 0) {
        if (bank == 1) {
            //TODO have to change the bank number to be uniform
            return Module_Voltage_Value[0][module_0];
        }
        if (bank == 2) {
            return Module_Voltage_Value[1][module_0];
        }
    }
    if (module == 1) {
        if (bank == 1) {
            return Module_Voltage_Value[0][module_1];
        }
        if (bank == 2) {
            return Module_Voltage_Value[1][module_1];
        }
    }
    if (module == 2) {
        if (bank == 1) {
            return Module_Voltage_Value[0][module_2];
        }
        if (bank == 2) {
            return Module_Voltage_Value[1][module_2];
        }
    }
}
//This function gets a attribute of the extreme voltage.
//Where type equal what extreme, Parm equals what property of that extreme (location,data etc.) and bank is what bank we are looking at.
double Get_Extreme_Voltage(int type, int parm, int bank) {
    //If we want to pick the minium voltage.
    if (type == min_select) {
        switch (parm) {
            //If we want Data
            case Data_Value:
                if (bank = bank_1) {
                    return Min_Cell_Voltage[Bank1_Array_Indicator][Data_Value];
                } else if (bank = bank_2) {
                    return Min_Cell_Voltage[Bank2_Array_Indicator][Data_Value];
                }
                break;
                //If we want location
            case IC_LOCATION:
                if (bank = bank_1) {
                    return Min_Cell_Voltage[Bank1_Array_Indicator][IC_LOCATION];
                } else if (bank = bank_2) {
                    return Min_Cell_Voltage[Bank2_Array_Indicator][IC_LOCATION];
                }
                break;
                //If we want sensor location.
            case SENSOR_LOCATION:
                if (bank = bank_1) {
                    return Min_Cell_Voltage[Bank1_Array_Indicator][SENSOR_LOCATION];
                } else if (bank = bank_2) {
                    return Min_Cell_Voltage[Bank2_Array_Indicator][SENSOR_LOCATION];
                }
                break;
        }
    } else if (type == max_select) {
        //If we want Max voltage the parm is the same as the min.
        switch (parm) {
            case Data_Value:
                if (bank = bank_1) {
                    return Max_Cell_Voltage[Bank1_Array_Indicator][Data_Value];
                } else if (bank = bank_2) {
                    return Max_Cell_Voltage[Bank2_Array_Indicator][Data_Value];
                }
                break;
            case IC_LOCATION:
                if (bank = bank_1) {
                    return Max_Cell_Voltage[Bank1_Array_Indicator][IC_LOCATION];
                } else if (bank = bank_2) {
                    return Max_Cell_Voltage[Bank2_Array_Indicator][IC_LOCATION];
                }
                break;
            case SENSOR_LOCATION:
                if (bank = bank_1) {
                    return Max_Cell_Voltage[Bank1_Array_Indicator][SENSOR_LOCATION];
                } else if (bank = bank_2) {
                    return Max_Cell_Voltage[Bank2_Array_Indicator][SENSOR_LOCATION];
                }
                break;
        }
    }

}


int Read_Total_GPIO(int Aux_codes_Bank1t[][6], int Aux_codes_Bank2t[][6]) {
    int Read_Status_INC = 0;
    int Error_Value = 0;
    int FaultNum = 0;

    //LATBbits.LATB6 = 1;
    Error_Value = Read_GPIO(0, Aux_codes_Bank1t);
    //Error_Value = LTC6804_rdaux(0, NUMBEROFIC, Aux_codes_Bank1); // All GPIO and Ref
    Read_GPIO(0, Aux_codes_Bank2t);
    //Error_Value = LTC6804_rdaux(0, NUMBEROFIC, Aux_codes_Bank2); // All GPIO and Ref
    //LATBbits.LATB6 = 0;


    //  Read_Status_INC = 0;
    //    do { 
    //        Read_GPIO(0, Aux_codes_Bank2);
    //       Error_Value = LTC6804_rdaux(0, NUMBEROFIC, Aux_codes_Bank2); // All GPIO and Ref
    //        if (Error_Value != 0) {
    //            Read_Status_INC = Read_Status_INC + 1;
    //        }
    //
    //   } while (Error_Value != 0 && Read_Status_INC <= 10);
    //   if (Read_Status_INC > 10) {
    //        FaultNum = ReadAuxRegFault;
    //    }
    //   else if (Error_Value == 0) {
    //
    //        
    //LATBbits.LATB6 = 1;
    FaultNum = Test_Temp_Sensors(Aux_codes_Bank1t, Aux_codes_Bank2t, Aux_codes_Bank1t[6][0]);
    //   }
    //LATBbits.LATB6 = 0;
    return FaultNum;
}

/*******************************************************************
 * @brief           Read_GPIO
 * @brief           Reads GPIO for the Temp sensors 
 * @return          none
 * @note            We may need to add some voltage to temp convert
 *******************************************************************/\
//TODO Need to Reference the Aux array

int Read_GPIO(int BatteryPlacement, int aux_codes[NUMBEROFIC][6]) {
    int Read_Status = 0;
    switch (BatteryPlacement) {
        case 0:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_ALL);
            LTC6804_adax();
            wakeup_idle();
            Read_Status = LTC6804_rdaux(0, NUMBEROFIC, Aux_codes_Bank1); // All GPIO and Ref
            //Delay(100);
            break;
        case 1:
            wakeup_idle();
            set_adc(MD_FILTERED, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO1);
            LTC6804_adax();
            set_adc(MD_FILTERED, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO2);
            LTC6804_adax();
            set_adc(MD_FILTERED, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO3);
            LTC6804_adax();
            wakeup_idle();
            Read_Status = LTC6804_rdaux(1, NUMBEROFIC, aux_codes); //GPIO 1
            Read_Status = LTC6804_rdaux(2, NUMBEROFIC, aux_codes); //GPIO 1
            break;
        case 2:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO2);
            LTC6804_adax();
            wakeup_idle();
            break;
        case 3:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO3);
            LTC6804_adax();
            wakeup_idle();
            break;
        case 4:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO4);
            LTC6804_adax();
            wakeup_idle();
            //Read_Status = LTC6804_rdaux(2, NUMBEROFIC, aux_codes); //GPIO 4
            break;
        case 5:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO5);
            LTC6804_adax();
            wakeup_idle();
            break;
        case 6:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_VREF2);
            LTC6804_adax();
            wakeup_idle();
            break;
        default:
            Read_Status = ReadAuxRegFault;
            break;
    }
    return Read_Status;
}
int Test_Temp_Sensors(int Aux_codes_Bank1t[][6], int Aux_codes_Bank2[][6], int x) {
    int Fault = 0;
    Convert_To_Voltage_Temp(Aux_codes_Bank1t, Aux_codes_Bank2); //Converting reading to proper voltage value.
    CalculateTemp(bank_1, Converted_Temprature_Bank1); //Convert voltage reading to a temp in C
    CalculateTemp(bank_2, Converted_Temprature_Bank2); //Convert voltage reading to a temp in C
    Update_Average_Array_Temp(TempCBank1, TempCBank2); //Updates the average of all of th eC 
    Check_Array_Faults_Temp(Average_Temprature_Codes_Bank1,Average_Temprature_Codes_Bank2);

    // TODO need to check values.

    return Fault;
}

void Convert_To_Voltage_Temp(int Array_Bank1[][6], int Array_Bank2[][6]) {
    int ic = 6;
    int cell = 0;
    int Temp_ValB1 = 0;
    int Temp_ValB2 = 0;
    while (ic < 9) {
        while (cell < 6) {
            //Have to convert to float from int first than mutiply the floating number gave me errors otherwise.
            Temp_ValB1 = Array_Bank1[ic][cell]; //*0.0001;
            Temp_ValB2 = Array_Bank2[ic][cell];
            Converted_Temprature_Bank1[ic][cell] = Temp_ValB1 * 0.0001;
            Converted_Temprature_Bank2[ic][cell] = Temp_ValB2 * 0.0001;
            cell++;
        }
        cell = 0;
        ic++;
    }
}

void CalculateTemp(int bank, double Conv_Temp[][6]) {
    float TempC = 0;
    int ic = 0; //The IC we are currently reading
    int sensenum = 0; //The senesor we are currently reading.
    while (ic < 9) {
        while (sensenum < 6) {
            float Volt_Of_GPIO = 0;
            float Resist_Of_GPIO = 0;
            float Voltage_diff = 0;
            Volt_Of_GPIO = Conv_Temp[ic][sensenum]; //v2 vin v1 rgpio thermo r2  r1 10k
            Resist_Of_GPIO = (Volt_Of_GPIO * 10000); //TOTAL EQUATION R2=(VO*R1)/(Vin-Vo)   CHECK DEBUG ADDING ARTifact
            Voltage_diff = (Vin - Volt_Of_GPIO);
            Resist_Of_GPIO = Resist_Of_GPIO / Voltage_diff; //Through Voltage Divider  TOTAL EQUATION R2=(VO*R1)/(Vin-Vo)
            TempK = (To + ((Inverse_B_Constant) * (log(Resist_Of_GPIO / 10000))));
            TempK = (1 / TempK);
            TempC = TempK - 273.15;
            if (bank == 1) {
                TempCBank1[ic][sensenum] = TempC;
            } else if (bank == 2) {
                TempCBank2[ic][sensenum] = TempC;
            }
            sensenum = sensenum + 1;
        }
        sensenum = 0;
        ic = ic + 1;
    }
}
void Update_Average_Array_Temp(double Array_Bank1[][6], double Array_Bank2[][6]) {
    int Ic = 0;
    int cell = 0;
    //If first sample there is no weighted needed becuase it is the first sample.
    if (Starting_Samples == true) {
        while (Ic < NUMBEROFIC) {
            while (cell < 6) {
                //GPIO Values
                Average_Temprature_Codes_Bank1[Ic][cell] = Array_Bank1[Ic][cell];
                Average_Temprature_Codes_Bank2[Ic][cell] = Array_Bank2[Ic][cell];
                cell = cell + 1;
            }
            cell = 0;
            Ic = Ic + 1;
        }
        cell = 0;
        Ic = 0;
    } else if (Starting_Samples == false) {
        while (Ic < NUMBEROFIC) {
            while (cell < 6) {
                Average_Temprature_Codes_Bank1[Ic][cell] = (.8 * (Average_Temprature_Codes_Bank1[Ic][cell])+ (.2 * Array_Bank1[Ic][cell]));
                Average_Temprature_Codes_Bank2[Ic][cell] = (.8 * (Average_Temprature_Codes_Bank2[Ic][cell]) +(.2 * Array_Bank2[Ic][cell]));
                cell = cell++;
            }
            cell = 0;
            Ic = Ic++;
        }
    }

}


int Check_Array_Faults_Temp(double cell_codes_bank1[][6], double cell_codes_bank2[][6]) {
    int IC_Counter, TempSense_Counter, Fault;
    for (IC_Counter = 0; IC_Counter < NUMBEROFIC; IC_Counter++) {
        for (TempSense_Counter = 0; TempSense_Counter < 6; TempSense_Counter++) {
            //Checking for max or min values to send to ECU
            //Min Bank 1
            if (TempCBank1[IC_Counter][TempSense_Counter] < Min_Temp[Bank1_Array_Indicator][Data_Value]) {
                Min_Temp[Bank1_Array_Indicator][Data_Value] = TempCBank1[IC_Counter][TempSense_Counter];
                Min_Temp[Bank1_Array_Indicator][IC_LOCATION] = IC_Counter;
                Min_Temp[Bank1_Array_Indicator][SENSOR_LOCATION] = TempSense_Counter;

            }                //Max Bank 1
             if (TempCBank1[IC_Counter][TempSense_Counter] > Max_Temp[Bank1_Array_Indicator][Data_Value]) {

                Max_Temp[Bank1_Array_Indicator][Data_Value] = TempCBank1[IC_Counter][TempSense_Counter];
                Max_Temp[Bank1_Array_Indicator][IC_LOCATION] = IC_Counter;
                Max_Temp[Bank1_Array_Indicator][SENSOR_LOCATION] = TempSense_Counter;
            }  
            
            //Min Bank 2
             if (TempCBank2[IC_Counter][TempSense_Counter] < Min_Temp[Bank2_Array_Indicator][Data_Value]) {

                Min_Temp[Bank2_Array_Indicator][Data_Value] = TempCBank2[IC_Counter][TempSense_Counter];
                Min_Temp[Bank2_Array_Indicator][IC_LOCATION] = IC_Counter;
                Min_Temp[Bank2_Array_Indicator][SENSOR_LOCATION] = TempSense_Counter;
                //Max Bank 2
            }  if (TempCBank2[IC_Counter][TempSense_Counter] > Max_Temp[Bank2_Array_Indicator][Data_Value]) {

                Max_Temp[Bank2_Array_Indicator][Data_Value] = TempCBank2[IC_Counter][TempSense_Counter];
                Max_Temp[Bank2_Array_Indicator][IC_LOCATION] = IC_Counter;
                Max_Temp[Bank2_Array_Indicator][SENSOR_LOCATION] = TempSense_Counter;
            }
            
            if (TempCBank1[IC_Counter][TempSense_Counter] >= Over_Temp_Value) {
                Fault = OverTempratureThreshold;
                //If any of the temps are over this threshold exit out of loop and report.
                TempSense_Counter = 6;
                IC_Counter = NUMBEROFIC;
            }
            //For Bank 2
            //If there is no fault for Bank1
            if (Fault != OverTempratureThreshold) {
                if (TempCBank2[IC_Counter][TempSense_Counter] >= Over_Temp_Value) {
                    Fault = OverTempratureThreshold;
                    //If any of the temps are over this threshold exit out of loop and report.
                    TempSense_Counter = 6;
                    IC_Counter = NUMBEROFIC;
                }
            }

        }
    }
}


double Get_Extreme_Temprature(int type, int parm, int bank) {
    //TODO need to fix the output so it displays the value and not a constant like I have for testing.
    if (type == min_select) {
        switch (parm) {
            case Data_Value:
                if (bank = bank_1) {
                    return Min_Temp[Bank1_Array_Indicator][Data_Value];
                } else if (bank = bank_2) {
                    return Min_Temp[Bank2_Array_Indicator][Data_Value];
                }
                break;
            case IC_LOCATION:
                if (bank = bank_1) {
                    return Min_Temp[Bank1_Array_Indicator][IC_LOCATION];
                } else if (bank = bank_2) {
                    return Min_Temp[Bank2_Array_Indicator][IC_LOCATION];
                }
                break;
            case SENSOR_LOCATION:
                if (bank = bank_1) {
                    return Min_Temp[Bank1_Array_Indicator][SENSOR_LOCATION];
                } else if (bank = bank_2) {
                    return Min_Temp[Bank2_Array_Indicator][SENSOR_LOCATION];
                }
                break;
        }
    } else if (type == max_select) {
        switch (parm) {
            case Data_Value:
                if (bank = bank_1) {
                    printf("Data %f",Max_Temp[Bank1_Array_Indicator][Data_Value]);
                    return 52.555;//Max_Temp[Bank1_Array_Indicator][Data_Value];
                    printf("\n\n\n HI");
                } else if (bank = bank_2) {
                    return Max_Temp[Bank2_Array_Indicator][Data_Value];
                }
                break;
            case IC_LOCATION:
                if (bank = bank_1) {
                    printf("IC %f",Max_Temp[Bank1_Array_Indicator][IC_LOCATION]);
                    return 55.6663;//Max_Temp[Bank1_Array_Indicator][IC_LOCATION];
                    
                } else if (bank = bank_2) {
                    return Max_Temp[Bank2_Array_Indicator][IC_LOCATION];
                }
                break;
            case SENSOR_LOCATION:
                if (bank = bank_1) {
                    printf("Sen %f",Max_Temp[Bank1_Array_Indicator][SENSOR_LOCATION]);
                    return 72.56578;//Max_Temp[Bank1_Array_Indicator][SENSOR_LOCATION];
                } else if (bank = bank_2) {
                    return Max_Temp[Bank2_Array_Indicator][SENSOR_LOCATION];
                }
                break;
        }
    }
}

void Pack_Temprature_Sum(double Array_Bank1[][6], double Array_Bank2[][6]) {
    int ic = 0, sense_num = 0, Bank_Num = 0;
    //For both Banks
    while (Bank_Num < 2) {
        while (ic < 9) {
            switch (ic) {
                    //Each Module has 3 LTC6804 with 12 voltage cells a piece. Summing that up for each module.
                case 0:
                case 1:
                case 2:
                    while (sense_num < 5) { //We are doing 5 because the 6th is a voltage regulator and that is not a temprature
                        if (Bank_Num == 0) {
                            Module_Average_Temp_Value[Bank_Num][0] = Array_Bank1[ic][sense_num] + Module_Average_Temp_Value[Bank_Num][0];
                        }
                        if (Bank_Num == 1) {
                            Module_Average_Temp_Value[Bank_Num][0] = Array_Bank2[ic][sense_num] + Module_Average_Temp_Value[Bank_Num][0];
                        }
                        sense_num++;
                    }
                    sense_num = 0;
                    break;
                case 3:
                case 4:
                case 5:
                    while (sense_num < 5) { //We are doing 5 because the 6th is a voltage regulator and that is not a temprature
                        if (Bank_Num == 0) {
                            Module_Average_Temp_Value[Bank_Num][1] = Array_Bank1[ic][sense_num] + Module_Average_Temp_Value[Bank_Num][1];
                        }
                        if (Bank_Num == 1) {
                            Module_Average_Temp_Value[Bank_Num][1] = Array_Bank2[ic][sense_num] + Module_Average_Temp_Value[Bank_Num][1];
                        }
                        sense_num++;
                    }
                    sense_num = 0;
                    break;
                case 6:
                case 7:
                case 8:
                    while (sense_num < 5) { //We are doing 5 because the 6th is a voltage regulator and that is not a temprature
                        if (Bank_Num == 0) {
                            Module_Average_Temp_Value[Bank_Num][2] = Array_Bank1[ic][sense_num] + Module_Average_Temp_Value[Bank_Num][2];
                        }
                        if (Bank_Num == 1) {
                            Module_Average_Temp_Value[Bank_Num][2] = Array_Bank2[ic][sense_num] + Module_Average_Temp_Value[Bank_Num][2];
                        }
                        sense_num++;
                    }
                    sense_num = 0;
                    break;
            }
            ic++;
        }
        //      Once one bank is finished I am taking the 3 modules from this bank 
        //      and dividing it by the total amount of sensors per bank (15) to get average temp of the module. We might want total temp if that is the case we will need to delete these functions.
        Module_Average_Temp_Value[Bank_Num][0] = (Module_Average_Temp_Value[Bank_Num][0] / Num_TempSense_Per_Module);
        Module_Average_Temp_Value[Bank_Num][1] = (Module_Average_Temp_Value[Bank_Num][1] / Num_TempSense_Per_Module);
        Module_Average_Temp_Value[Bank_Num][2] = (Module_Average_Temp_Value[Bank_Num][2] / Num_TempSense_Per_Module);

        ic = 0;
        sense_num = 0;
        Bank_Num++;
    }

}


//Not sure if function is needed i think I have this for debug purposes.
int Read_GPIO_Bank(int Aux_codes_Bank[][6]) {
    int Error_Value = 0;
    LATBbits.LATB6 = 1;
    Error_Value = Read_GPIO(0, Aux_codes_Bank);
    LATBbits.LATB6 = 0;
}

//Clears the Max and Min values for every run.

void Re_Initialize_Extreme_Values() {
    int Bank_Select = 0;
    for (Bank_Select; Bank_Select < 2; Bank_Select++) {
        Min_Temp[Bank_Select][Data_Value] = 100;
        Max_Temp[Bank_Select][Data_Value] = 0;
        Min_Cell_Voltage[Bank_Select][Data_Value] = 100;
        Max_Cell_Voltage[Bank_Select][Data_Value] = 0;
    }
    ;
}



/*******************************************************************
 * @brief           Set_Bypass
 * @brief           sets bypass for a cell on the stack
 * @return          none
 * @note            
 *******************************************************************/





//Not sure what the purpose of this is. Purposing to remove this.
double getbigc() {
    if (qw == 0) {
        bankforc = TempCBank1[7][1];
        qw = 1;
    } else {
        bankforc = ((.8 * bankforc)+ (.2 * TempCBank1[7][1]));
    }


    return bankforc;
}
//Get the temp of a indvidual value might need this for debuging or something no being used.
double gettemp(int ic, int num, int bank) {
    if (bank == 1) {
        return TempCBank1[ic][num];
    }
    if (bank == 2) {
        return TempCBank2[ic][num];
    }
}

int Run_ByPass(int cell_codesBank1[][12], int cell_codesBank2[][12]) {
    int bypass_flag = 0;
    while (Battery_Is_Charging_Flag == 1) {
        Battery_Is_Charging_Flag = 0; // If this flag is tripped that means there is a cell that need more voltage. 
        int Read_Status_INC = 0;
        //To detect error values
        int Error_Value = 0;
        //Bank1
        do {
            Error_Value = Read_Battery(0, cell_codes_Bank1);
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
            Error_Value = Read_Battery(0, cell_codesBank2);
            if (Error_Value != 0) {
                Read_Status_INC = Read_Status_INC + 1;
            }
        } while (Error_Value != 0 && Read_Status_INC < 10);

        if (Read_Status_INC >= 10) {
            return ReadVoltRegFault;
        }
        Convert_To_Voltage_Cell(cell_codesBank1, cell_codesBank2);
        //RunBypass

        bypass_flag = RunBypass_Set(bank_1, Converted_Cell_Codes_Bank1);
        bypass_flag = RunBypass_Set(bank_2, Converted_Cell_Codes_Bank2);
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
            batvolt = CheckThresholds(OverVoltageFault, Conv_Cell_Codes[Ic][Cell]);
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

float CurrentGet(bool total, char channel) {
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

float VoltGet(char channel) {
    if (channel) {
        return Volt1;
    }
    else {
        return Volt2;
    }
}