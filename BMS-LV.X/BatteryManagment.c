/*******************************************************************
 * @brief           BatteryManagment.c
 * @brief           Adds easy to use functions to the LTC6804.c
 * @return          EU
 * @note            The lib is writen for US
 *******************************************************************/
#include <math.h>
#include <xc.h>
#include "Functions.h"
#include "mcc_generated_files/adc.h"
#include "BatteryManagment.h"
#include "BatteryManagmentPrivate.h"
#include "mcc_generated_files/pin_manager.h"
#include "LT6804.h"
#include <stdbool.h>
#include <stdio.h>
//TODO Need to make a fault status and a use with var
int Read_Status_INC = 0;

//|r_config[0]|r_config[1]|r_config[2]|r_config[3]|r_config[4]|r_config[5]|r_config[6]  |r_config[7] |r_config[8]|r_config[9]|  .....    |
//|-----------|-----------|-----------|-----------|-----------|-----------|-------------|------------|-----------|-----------|-----------|
//|IC1 CFGR0  |IC1 CFGR1  |IC1 CFGR2  |IC1 CFGR3  |IC1 CFGR4  |IC1 CFGR5  |IC1 PEC High |IC1 PEC Low |IC2 CFGR0  |IC2 CFGR1  |  .....    |

/*******************************************************************
 * @brief           Start_BMS
 * @brief           Setup The BMS and set configs
 * @return          none
 * @note            
 *******************************************************************/

void Start_BMS() {
  
    //Run_Mode();
    Initalize_LT6804b();
}

void Charge_Mode(int command) {
    //if in charge mode 
    //Run_ByPass(cell_codes_Bank1, cell_codes_Bank2);

}

void Run_Mode() {
      Read_Battery(0,cell_codes_Bank);
      int k = 0;
      for(k;k<12;k++){
        printf(" Cell %d Voltage: %1.2f \n",k, cell_codes_Bank[0][k]*0.00001);
      }
      RunBypass_Set(1,0,cell_codes_Bank);
      
      TempRun();  //Calculate Temps 
      for(k;k<6;k++){
        printf(" Cell %d temp: %1.2f \n",k, Tempeture_Get(k));
      }
      Temp_Fault(); //Fault Detect on high temp 
      
}

void Initalize_LT6804b() {
    int IC = 0;
 
    CFGR0=0xFE;
    CFGR1=0;
    CFGR2=0;
    CFGR3=0;
    CFGR4=0;
    CFGR5=0;
    
    
        while (IC < NUMBEROFIC) {
            Set_REFON_Pin(IC, 1);
            Set_ADC_Mode(IC, 0);
            Set_DCC_Mode_OFF(IC);
            Set_DCTO_Mode_OFF(IC);
            SetTempEnable(IC, 0);
            //SetUnderOverVoltage(Under_Voltage_Value, Over_Voltage_Value,  IC);
            IC++;
        };
    
    //wakeup_sleep();
    UpdateLT6804();
    
    //UpdateLT6804(1);
}

//TODO figure out fault function of bank 1 and 2

void Run_ByPass(int cell_codesBank1[][12], int cell_codesBank2[][12]) {
    //To detect error values
    int Error_Value = 0;
    //Bank1
    do {
        Error_Value = Read_Battery(0, cell_codes_Bank);
        if (Error_Value != 0) {
            Read_Status_INC = Read_Status_INC + 1;
        }
    } while (Error_Value != 0);
    //RunBypass_Set(bank_1,NUMBEROFIC,cell_codes_Bank1);

    //Bank2
    do {
        Error_Value = Read_Battery(0, cell_codes_Bank);
        if (Error_Value != 0) {
            Read_Status_INC = Read_Status_INC + 1;
        }
    } while (Error_Value != 0);
    // RunBypass_Set(bank_2,NUMBEROFIC,cell_codesBank2);

}

void CheckFault(int FaultValue) {
    if (FaultValue != 0) {
        addressFault(FaultValue);
    }
}

int addressFault(int FaultNum) {
    //need to determine the fault number
    //TODO Check if this is accurate this may break the board. (This will, needs toggled - RJ)
    SET_SetHigh();
    Delay(120);
    SET_SetLow();
    //Once the error has been addressed the error is then cleared. 
    FaultNum = 0;
    return 1; //If success return a 1
}
//TODO Finish Up setup Test

int Startuptests(int Stat_codes[NUMBEROFIC][6]) {
    int ReadErrorValue = 0; //If there is a error reading the statregister
    int ErrorCount = 0; //How many times in a row was there a error this can indicate a loop that is stuck.
    int CriticalReadError = 0; // If over 10 Send a Critical Error to be dealt with. 
    int FaultError = 0; // in the test if there is a fault it will be read here
    Set_Stat(MD_NORMAL, All_Stats);
    LTC6804_ADSTAT();
    ReadErrorValue = LTC6804_rdStat(0, NUMBEROFIC, Stat_codes);

    while (ReadErrorValue == -1 && ErrorCount < 10) {
        LTC6804_ADSTAT();
        ReadErrorValue = LTC6804_rdStat(0, NUMBEROFIC, Stat_codes);
    }
    if (ErrorCount >= 10) {
        CriticalReadError = ReadstatRegFault;
    }

    if (ReadErrorValue == 0) {
        CheckTestReading(Stat_codes);
        return FaultError;
    }
    if (ErrorCount > 10) {
        return CriticalReadError;
    }

}

int CheckTestReading(int Stat_codes[NUMBEROFIC][6]) {
    int TestError = 0;
    int IC = 0;
    while (IC < NUMBEROFIC) {

        //Sum_Of_Cells
        int soc = 0;
        int Sum_Of_Cells = 0;
        soc = Stat_codes[NUMBEROFIC][0];
        Sum_Of_Cells = (soc * (100 * pow(10, -6))*20);
        //Vminus Pin ask Richard what this means

        //Internal Die Temprature
        int itmp = 0;
        double Internal_Die_Temprature = 0;
        itmp = Stat_codes[NUMBEROFIC][1];
        Internal_Die_Temprature = (itmp * ((100 * pow(10, -6)) / (7.5 * pow(10, -3))) - 273);
        //TODO ask Richard what the temprature needs to be.

        //Analog Power Supply 
        int va = 0;
        int Analog_Supply_Power = 0;
        va = Stat_codes[NUMBEROFIC][2];
        Analog_Supply_Power = (soc * (100 * pow(10, -6)));
        if ((Analog_Supply_Power < 4.5) || (Analog_Supply_Power > 5.5)) {
            TestError = AnalogPowerSupplyFault;
        }

        //Digital Power Supply 
        int vd = 0;
        int Digital_Supply_Power = 0;
        vd = Stat_codes[NUMBEROFIC][3];
        Digital_Supply_Power = (soc * (100 * pow(10, -6)));
        if ((Digital_Supply_Power < 2.7) || (Digital_Supply_Power > 3.6)) {
            TestError = DigitalPowerSupplyFault;
        }

        //Under and Over Voltage errors
        int BoolValues = 0; // Bools values of the cells to indicate if there is a over/under voltage fault.
        BoolValues = Stat_codes[NUMBEROFIC][4];
        //Going through each bit and determining a fault. 
        int incrementer = 0;
        while (incrementer <= 15) {
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
            CheckValue = 0;
        }

        //Under and Over Voltage errors and muxFail and THSD
        BoolValues = 0; // Bools values of the cells to indicate if there is a over/under voltage or other faults
        BoolValues = Stat_codes[NUMBEROFIC][4];
        //Going through each bit and determining a fault. 
        incrementer = 0;
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
            CheckValue = 0;
        }
        IC = IC + 1;
    }
    return TestError;



    ;
}
int CheckThresholdsBank(int test,int IC, int cell_codes[][12]) {
    int CurrentIC = 0;
    int cell = 0;
    int Error_Value = 0;
    while (CurrentIC < IC) {
        while (cell < 12) {

            Error_Value = CheckThresholds(test, cell_codes[CurrentIC][cell]);
            if (Error_Value != 0) {
                return Error_Value;
            }
            cell = cell + 1;
        }

        cell = 0;
        CurrentIC = CurrentIC + 1;
    }
    return Error_Value;
}
int CheckThresholds(int test, int data) {
    int FaultIndicator = 0;
    switch (test) {
        case OverVoltageFault:
            if (data > Over_Voltage_Value)
                FaultIndicator = OverVoltageFault;
            break;
        case UnderVoltageFault:
            if (data < Under_Voltage_Value) {
                FaultIndicator = UnderVoltageFault;
            }
            break;
    }
    return FaultIndicator;
}

int Read_Total_Voltage(int cell_codesBank[][12]) {
int Read_Status_INC = 0;
    int Error_Value = 0;
    int FaultNum=0;
    do {
        Error_Value = Read_Battery(0, cell_codesBank);
        if (Error_Value != 0) {
            Read_Status_INC = Read_Status_INC + 1;
        }
    } while (Error_Value != 0 && Read_Status_INC <= 10);
    if (Read_Status_INC > 10) {
        FaultNum = ReadVoltRegFault;
    }
    else if (Error_Value == 0) {
        Error_Value=CheckThresholdsBank( OverVoltageFault,NUMBEROFIC , cell_codesBank);
        if (Error_Value != 0){return Error_Value;}
        Error_Value=CheckThresholdsBank( UnderVoltageFault, NUMBEROFIC, cell_codesBank);
        if (Error_Value != 0){return Error_Value;}
        Error_Value=CheckThresholdsBank( OverVoltageFault, NUMBEROFIC, cell_codesBank);
        if (Error_Value != 0){return Error_Value;}
       Error_Value=CheckThresholdsBank( UnderVoltageFault, NUMBEROFIC, cell_codesBank);
    }
    return Error_Value;
}
/*******************************************************************
 * @brief           Read_Battery
 * @brief           Reads battery voltage of each cell 
 * @return          none
 * @note            
 *******************************************************************/
//TODO Need to Reference the Bat array
int getcell(){
    return cell_codes_Bank;
;}

int Read_Battery(int BatteryPlacement, int cell_codes[NUMBEROFIC][12]) {
    int Read_Status = 0;

    switch (BatteryPlacement) {
        case 0:
            set_adc(MD_FILTERED, DCP_DISABLED, CELL_CH_ALL, AUX_CH_ALL);
            LTC6804_adcv();
            Delay(10);
            Read_Status = LTC6804_rdcv(0, NUMBEROFIC, cell_codes);
            break;
        case 1:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_1and7, AUX_CH_ALL);
            LTC6804_adcv();
            Delay(10);
            Read_Status = LTC6804_rdcv(1, 3, cell_codes); //Cell 1
            Read_Status = LTC6804_rdcv(3, 3, cell_codes); //Cell 7
            break;
        case 2:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_2and8, AUX_CH_ALL);
            LTC6804_adcv();
            Delay(10);
            Read_Status = LTC6804_rdcv(0, NUMBEROFIC, cell_codes); // Cell 2
            Read_Status = LTC6804_rdcv(3, NUMBEROFIC, cell_codes); //Cell 8
            break;
        case 3:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_3and9, AUX_CH_ALL);
            LTC6804_adcv();
            Delay(10);
            Read_Status = LTC6804_rdcv(0, NUMBEROFIC, cell_codes); // Cell 3
            Read_Status = LTC6804_rdcv(3, NUMBEROFIC, cell_codes); //Cell 9
            break;
        case 4:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_4and10, AUX_CH_ALL);
            LTC6804_adcv();
            Read_Status = LTC6804_rdcv(2, NUMBEROFIC, cell_codes); // Cell 4
            Read_Status = LTC6804_rdcv(4, NUMBEROFIC, cell_codes); //Cell 10
            break;
        case 5:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_5and11, AUX_CH_ALL);
            LTC6804_adcv();
            Delay(10);
            Read_Status = LTC6804_rdcv(2, NUMBEROFIC, cell_codes); // Cell 5
            Read_Status = LTC6804_rdcv(4, NUMBEROFIC, cell_codes); //Cell 11
            break;
        case 6:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_6and12, AUX_CH_ALL);
            LTC6804_adcv();
            Delay(10);
            Read_Status = LTC6804_rdcv(2, NUMBEROFIC, cell_codes); // Cell 6
            Read_Status = LTC6804_rdcv(4, NUMBEROFIC, cell_codes); //Cell 12
            break;
        default:
            break;
    }
    return Read_Status;
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
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_ALL);
            LTC6804_adax();
            // What Cells to read,amount of IC,Data
            Read_Status = LTC6804_rdaux(0, NUMBEROFIC, aux_codes); // All GPIO and Ref

            break;
        case 1:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO1);
            LTC6804_adax();
            Read_Status = LTC6804_rdaux(1, NUMBEROFIC, aux_codes); //GPIO 1
            break;
        case 2:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO2);
            LTC6804_adax();
            Read_Status = LTC6804_rdaux(1, NUMBEROFIC, aux_codes); //GPIO 2
            break;
        case 3:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO3);
            LTC6804_adax();
            Read_Status = LTC6804_rdaux(1, NUMBEROFIC, aux_codes); //GPIO 3
            break;
        case 4:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO4);
            LTC6804_adax();
            Read_Status = LTC6804_rdaux(2, NUMBEROFIC, aux_codes); //GPIO 4
            break;
        case 5:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO5);
            LTC6804_adax();
            Read_Status = LTC6804_rdaux(2, NUMBEROFIC, aux_codes); //GPIO 5
            break;
        case 6:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_VREF2);
            LTC6804_adax();
            Read_Status = LTC6804_rdaux(2, NUMBEROFIC, aux_codes); //GPIO 6
            break;
        default:
            break;
    }

    return Read_Status;
}

/*******************************************************************
 * @brief           Set_Bypass
 * @brief           sets bypass for a cell on the stack
 * @return          none
 * @note            
 *******************************************************************/

//Update

int SetBypass(int bank, int ic, int cell, bool value) {
    int fault_value = 0;
    if (value) {
        if (cell < 8) {
            CFGR4 = CFGR4 | (1 << cell); //This sets the cell on the stack to on when less than 8 
        } else {
            CFGR5 = CFGR5 | (1 << (cell - 8)); //This sets the cell on the stack to on when > 8
        }
    } else {
        if (cell < 8) {
            CFGR4 = CFGR4 & ~(1 << cell); //This sets the cell on the stack to off when less than 8
        } else {
            CFGR5 = CFGR5 & ~(1 << (cell - 8)); //This sets the cell on the stack to off when > 8
        }
    }
    if (bank == 1) {
        LTC6804_DATA_ConfigBank[ic][4] = CFGR4 & 0xFF; //First  8 Bits of DCC
        LTC6804_DATA_ConfigBank[ic][5] = (CFGR5) + (DCTO << 4);
    }// Combined DCTO and the Last 4 bits of DCC
    else if (bank == 2) {
        LTC6804_DATA_ConfigBank[ic][4] = CFGR4 & 0xFF; //First  8 Bits of DCC
        LTC6804_DATA_ConfigBank[ic][5] = (CFGR5) + (DCTO << 4);
    }// Combined DCTO and the Last 4 bits of DCC}
    else {
        fault_value = NoBankselected;
    }
    return fault_value;
}

/*******************************************************************
 * @brief           RunBypass
 * @brief           Controls bypass algorithm for pack
 * @return          none
 * @note            
 *******************************************************************/
int RunBypass_Set(int bank, int ic, int cell_codes[][12]) {
    int cellbyp = 0;
    int voltstat = 0;
    int batvolt = 0;
    int i; // Increment for IC
    int c; // Increment for Cells
    // Want to make a function for all Batterys Right now it works with just 1 IC
    // Need to understand how he Bank IC and Cell system works 

    for (i = 0; i <= NUMBEROFIC; i++) {

        for (c = 0; c <= Cell_Per_Bank; c++) // runs threw num of batteries
        {
            //voltstat = CheckUnderOverVoltageFlag();
            if (voltstat == 0) {
                if (batvolt >= Bypass_High_Limit) // if bypass needs enabled..
                {
                    SetBypass(bank, ic, c, true); // sets bypass on
                    cellbyp = 1;
                }
                if (batvolt <= Bypass_Low_Limit) //if bypass needs turned off...
                {
                    SetBypass(bank, ic, c, false); // sets bypass off
                }
            }
        }
    }
    UpdateLT6804();
    return cellbyp;
}

/*******************************************************************
 * @brief           SetTempEnable
 * @brief           This enables the power to the temp measurements
 * @return          none
 * @note            
 *******************************************************************/


int SetTempEnable( int ic, bool value) {
    int fault_value = 0;
    if (value) {
        CFGR0 = CFGR0 | (1 << 7); //Turn on GPIO 5
    } else {
        CFGR0 = CFGR0 & ~(1 << 7); //Turn off GPIO 5
    }

        LTC6804_DATA_ConfigBank[ic][0] = CFGR0;
  

    return fault_value;
}

/*******************************************************************
 * @brief           CheckUnderOverVoltageFlag
 * @brief           This will respond (true?)if there is a OV/UV 
 * @return          The flag true if there is a fault
 * @note            
 *******************************************************************/

int CheckUnderOverVoltageFlag() {
    return 1;
}

/*******************************************************************
 * @brief           SetUnderOverVoltage
 * @brief           This will set the UV and OV for all the IC's and banks
 * @return          none
 * @note            
 *******************************************************************/

//Update Under and over voltages. 

int SetUnderOverVoltage(int VUV, int VOV, int ic) {
    int fault_value = 0;
    //LTC6804 - PG: 49 
    CFGR1 = VUV & 0xFF; // Ands with the First 8 bits
    CFGR2 = ((VUV & 0xF00) >> 8)+ ((VOV & 0x0F) << 4); // Finish Last bits of VUV start with VOV
    CFGR3 = (VOV & 0xFF0) >> 4; // Finish VOV setup

    // load up static reg
        LTC6804_DATA_ConfigBank[ic][1] = CFGR1;
        LTC6804_DATA_ConfigBank[ic][2] = CFGR2;
        LTC6804_DATA_ConfigBank[ic][3] = CFGR3;
        LTC6804_DATA_ConfigBank[ic][1] = CFGR1;
        LTC6804_DATA_ConfigBank[ic][2] = CFGR2;
        LTC6804_DATA_ConfigBank[ic][3] = CFGR3;
  
}

/*******************************************************************
 * @brief           Set_ADC_Mode
 * @brief           This will set the UV and OV for all the IC's and banks
 * @return          none
 * @note            
 *******************************************************************/

//Not Sure how this  LTC6804_DATA works however will copy for consistency 

int Set_ADC_Mode(int ic, bool ADCOPT_Mode) {
    int fault_value = 0;
    if (ADCOPT_Mode) {
        CFGR0 = CFGR0 | ADC_MODE_BIT_14k_3k_2k;
    } else {
        CFGR0 = CFGR0 & ~ADC_MODE_BIT_14k_3k_2k; //ADC_MODE_BIT_27k_7k_26
    }
   
        LTC6804_DATA_ConfigBank[ic][0] = CFGR0;
    
    return fault_value;
}

void Set_DCC_Mode_OFF(int ic) {
    int fault_value = 0;
    CFGR4 = 0;
    CFGR5 = CFGR5 &~(0xF);
        LTC6804_DATA_ConfigBank[ic][4] = CFGR4;
        LTC6804_DATA_ConfigBank[ic][5] = CFGR5;
    
    
}

int Set_DCTO_Mode_OFF(int ic) {
    int fault_value = 0;
    CFGR5 = CFGR5 &~(0xF0);
        LTC6804_DATA_ConfigBank[ic][5] = CFGR5;
    return fault_value;
}

//Not Sure how this  LTC6804_DATA works however will copy for consistency 

int Set_REFON_Pin(int ic, bool REFON_Mode) {
    int fault_value = 0;
    if (REFON_Mode) {
        CFGR0 = CFGR0 | REFON_TURN_ON;
    } else {
        CFGR0 = CFGR0 & ~REFON_TURN_ON; //REFOFF_TURN_OFF
    }
    
        LTC6804_DATA_ConfigBank[ic][0] = CFGR0;
    return fault_value;
}

void UpdateLT6804() {
  
        LTC6804_wrcfg(NUMBEROFIC, LTC6804_DATA_ConfigBank);
   
}

/*******************************************************************
 * @brief           ReadCurrentVolt
 * @brief           Reads in the ADC counts from the current sense PCB
 * @return          none
 * @note            This populates the array with raw ADC values
 *******************************************************************/

void ReadCurrentVolt() {
    int i;
    //TODO: Need to check this.....
    for(i=6;i<1;i--){
       CVolt[i] = CVolt[i-1];
    }
    CVolt[0] = ADC_GetConversion(CURRENT);
    ReadVoltToCurrent(); //Converts ADC counts to amps
}

/*******************************************************************
 * @brief           ReadVolt
 * @brief           Reads in the ADC counts and converts to voltages 
 * @return          none
 * @note            Gets it ready for a traditional getter
 *******************************************************************/

void ReadVolt() {
    Volt1 = (ADC_GetConversion(VEXT) / ADCBIT)*5 * VOLTAGERATIO;
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
       // Current[k] = (((CVolt[k] / ADCBIT)*5) SHUNTOHMS/CURRENTGAIN) + CurrentOffset[k];
    }
}

/*******************************************************************
 * @brief           ChargerEN
 * @brief           Tells the BMS system that the charger is connected
 * @return          none
 * @note            Sets flag for reading
 *******************************************************************/

void ChargerEN() {
    CarOn = 0;
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

int CurrentGet() {
    return -1;
}