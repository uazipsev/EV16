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
int Battery_Is_Charging_Flag=0;
int FaultValue=0;
 int cell_codes_Bank1[NUMBEROFIC][12];
 int cell_codes_Bank2[NUMBEROFIC][12];
 int Aux_codes_Bank1[NUMBEROFIC][6];
 int Aux_codes_Bank2[NUMBEROFIC][6];
//|r_config[0]|r_config[1]|r_config[2]|r_config[3]|r_config[4]|r_config[5]|r_config[6]  |r_config[7] |r_config[8]|r_config[9]|  .....    |
//|-----------|-----------|-----------|-----------|-----------|-----------|-------------|------------|-----------|-----------|-----------|
//|IC1 CFGR0  |IC1 CFGR1  |IC1 CFGR2  |IC1 CFGR3  |IC1 CFGR4  |IC1 CFGR5  |IC1 PEC High |IC1 PEC Low |IC2 CFGR0  |IC2 CFGR1  |  .....    |

/*******************************************************************
 * @brief           Start_BMS
 * @brief           Setup The BMS and set configs
 * @return          none
 * @note            
 *******************************************************************/

void Start_BMS(int mode) {
    //TODO need to have a mode to make sure all slaves are up in running.
    LTC6804_initialize();
    ADS1015Begin();
    if (mode ==1){
        Run_Mode();
            initTimerThree(mode);
    }
    else if (mode==2){
        Charge_Mode();
            initTimerThree(mode);
    }
}

void Charge_Mode() {
    //if in charge mode 
     Initalize_LT6804b();
    Battery_Is_Charging_Flag=1;
    FaultValue=Run_ByPass(cell_codes_Bank1, cell_codes_Bank2);
    Open_All_ByPass();

}

void Run_Mode() {
    Initalize_LT6804b();
    
//    FaultValue=Startuptests(Stat_codes_Bank1);
//    FaultValue=Startuptests(Stat_codes_Bank2);
//    if (FaultValue!=0){
//        CheckFault();
//    }
//    else {
//        Run_GPIO_Temp_ColumbCounting_Timer();
//    }
    
}
void Run_GPIO_Temp_ColumbCounting_Timer(){
    initTimerTwo();
    }
void Initalize_LT6804b() {
    int IC = 0;
    int bank = 1;
    while (bank <= NUMBEROFCH) {
        while (IC < NUMBEROFIC) {
            Set_REFON_Pin(bank, IC, 0);
            Set_ADC_Mode(bank, IC, 1);
            Set_DCC_Mode_OFF(bank, IC);
            Set_DCTO_Mode_OFF(bank, IC);
            SetTempEnable(bank, IC, 0);
            SetUnderOverVoltage(Under_Voltage_Value, Over_Voltage_Value, bank, IC);
            IC++;
        };
        bank++;
    }

    UpdateLT6804(1);
    UpdateLT6804(2);
}

int Run_ByPass(int cell_codesBank1[][12], int cell_codesBank2[][12]) {
    while (Battery_Is_Charging_Flag==1){
        Battery_Is_Charging_Flag=0;// If this flag is tripped that means there is a cell that need more voltage. 
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
    //RunBypass
    RunBypass_Set(bank_1, cell_codes_Bank1);
    RunBypass_Set(bank_2,cell_codesBank2);
    Delay(1000); //Delay a second this is not accurate
    }
    T3CONbits.TON = 0;
    //hold LED HIGH that indicates charging
     return 0;

}

void Open_All_ByPass()//This function is to open all ByPasses
{
    int Ic = 0; // Increment for IC
    int Cell = 0; // Increment for Cells
    int bank = 0;
    for (bank = 1; bank < 3; bank++) {
        for (Ic = 0; Ic < NUMBEROFIC; Ic++) {

            for (Cell = 0; Cell < Cell_Per_Bank; Cell++) // runs threw num of batteries
            {
                SetBypass(bank, Ic, Cell, false); // sets bypass off
            }
        }
    }
}


//TODO Finish Up setup Test

int Startuptests(int Stat_codes[NUMBEROFIC][6]) {
    int ReadErrorValue = 0; //If there is a error reading the statregister
    int ErrorCount = 0; //How many times in a row was there a error this can indicate a loop that is stuck.
    int CriticalReadError = 0; // If over 10 Send a Critical Error to be dealt with. 
    Set_Stat(MD_NORMAL, All_Stats);
     do {
        LTC6804_ADSTAT();
        ReadErrorValue = LTC6804_rdStat(0, NUMBEROFIC, Stat_codes);
        if (ReadErrorValue != 0){
        ErrorCount=ErrorCount+1;}
    }
    while (ReadErrorValue != 0 && ErrorCount < 10);
    
    if (ErrorCount >= 10) {
        CriticalReadError = ReadstatRegFault;
        return CriticalReadError; 
    }
    if (ReadErrorValue == 0) {
       FaultValue= CheckTestReading(Stat_codes);
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
        if (TestError==0){
        //Internal Die Temprature
        int itmp = 0;
        double Internal_Die_Temprature = 0;
        itmp = Stat_codes[NUMBEROFIC][1];
        Internal_Die_Temprature = (itmp * ((100 * pow(10, -6)) / (7.5 * pow(10, -3))) - 273);
        //TODO ask Richard what the temprature needs to be.
        }
        if (TestError==0){
        //Analog Power Supply 
        int va = 0;
        int Analog_Supply_Power = 0;
        va = Stat_codes[NUMBEROFIC][2];
        Analog_Supply_Power = (soc * (100 * pow(10, -6)));
        if ((Analog_Supply_Power < 4.5) || (Analog_Supply_Power > 5.5)) {
            TestError = AnalogPowerSupplyFault;
        }
        }
        if (TestError==0){
        //Digital Power Supply 
        int vd = 0;
        int Digital_Supply_Power = 0;
        vd = Stat_codes[NUMBEROFIC][3];
        Digital_Supply_Power = (soc * (100 * pow(10, -6))); //TODO CHECK WHY THERE IS SOC
        if ((Digital_Supply_Power < 2.7) || (Digital_Supply_Power > 3.6)) {
            TestError = DigitalPowerSupplyFault;
        }
        }
        if (TestError==0){
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
            if (CheckValue==1){
            return TestError;}
            CheckValue = 0;
        }
        }
if (TestError==0){
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
            if (CheckValue==1){
            return TestError;}
            CheckValue = 0;
        }
}
        IC = IC + 1;
        if (TestError!=0){
        return TestError;
        }
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

int Read_Total_Voltage(int cell_codesBank1[][12], int cell_codesBank2[][12]) {
int Read_Status_INC = 0;
    int Error_Value = 0;
    int FaultNum=0;
    do {
        Error_Value = Read_Battery(0, cell_codes_Bank1);
        if (Error_Value != 0) {
            Read_Status_INC = Read_Status_INC + 1;
        }
    } while (Error_Value != 0 && Read_Status_INC <= 10);
        if (Read_Status_INC > 10) {
        FaultNum = ReadVoltRegFault;
    }
    Read_Status_INC = 0;
    do {
        Error_Value = Read_Battery(0, cell_codesBank2);
        if (Error_Value != 0) {
            Read_Status_INC = Read_Status_INC + 1;
        }

    } while (Error_Value != 0 && Read_Status_INC <= 10);
    if (Read_Status_INC > 10) {
        FaultNum = ReadVoltRegFault;
    }
    else if (Error_Value == 0) {
        Error_Value=CheckThresholdsBank( OverVoltageFault,NUMBEROFIC , cell_codes_Bank1);
        if (Error_Value != 0){return Error_Value;}
        Error_Value=CheckThresholdsBank( UnderVoltageFault, NUMBEROFIC, cell_codes_Bank1);
        if (Error_Value != 0){return Error_Value;}
        Error_Value=CheckThresholdsBank( OverVoltageFault, NUMBEROFIC, cell_codesBank2);
        if (Error_Value != 0){return Error_Value;}
       Error_Value=CheckThresholdsBank( UnderVoltageFault, NUMBEROFIC, cell_codesBank2);
    }
    return Error_Value;
}




int Read_Total_GPIO(int Aux_codes_Bank1[][6], int Aux_codes_Bank2[][6]) {
int Read_Status_INC = 0;
    int Error_Value = 0;
    int FaultNum=0;
    do {
        Error_Value = Read_GPIO(0, Aux_codes_Bank1);
        if (Error_Value != 0) {
            Read_Status_INC = Read_Status_INC + 1;
        }
    } while (Error_Value != 0 && Read_Status_INC <= 10);
        if (Read_Status_INC > 10) {
        FaultNum = ReadAuxRegFault;
    }
    Read_Status_INC = 0;
    do {
        Error_Value = Read_GPIO(0, Aux_codes_Bank2);
        if (Error_Value != 0) {
            Read_Status_INC = Read_Status_INC + 1;
        }

    } while (Error_Value != 0 && Read_Status_INC <= 10);
    if (Read_Status_INC > 10) {
        FaultNum = ReadAuxRegFault;
    }
    else if (Error_Value == 0) {
        FaultNum=Test_Temp_Sensors( Aux_codes_Bank1,Aux_codes_Bank2);
    }
    return FaultNum;
}

/*******************************************************************
 * @brief           Read_Battery
 * @brief           Reads battery voltage of each cell 
 * @return          none
 * @note            
 *******************************************************************/
//TODO Need to Reference the Bat array

int Read_Battery(int BatteryPlacement, int cell_codes[NUMBEROFIC][12]) {
    int Read_Status = 0;

    switch (BatteryPlacement) {
        case 0:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_ALL);
            LTC6804_adcv();
            Read_Status = LTC6804_rdcv(0, NUMBEROFIC, cell_codes);
            break;
        case 1:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_1and7, AUX_CH_ALL);
            LTC6804_adcv();
            Read_Status = LTC6804_rdcv(1, 3, cell_codes); //Cell 1
            Read_Status = LTC6804_rdcv(3, 3, cell_codes); //Cell 7
            break;
        case 2:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_2and8, AUX_CH_ALL);
            LTC6804_adcv();
            Read_Status = LTC6804_rdcv(0, NUMBEROFIC, cell_codes); // Cell 2
            Read_Status = LTC6804_rdcv(3, NUMBEROFIC, cell_codes); //Cell 8
            break;
        case 3:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_3and9, AUX_CH_ALL);
            LTC6804_adcv();
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
            Read_Status = LTC6804_rdcv(2, NUMBEROFIC, cell_codes); // Cell 5
            Read_Status = LTC6804_rdcv(4, NUMBEROFIC, cell_codes); //Cell 11
            break;
        case 6:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_6and12, AUX_CH_ALL);
            LTC6804_adcv();
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



double CalculateTemp(int bank, int auxcodes[NUMBEROFIC][6]){
    //TODO need to know what Vin is 
    //Might need to calaculate adc to Voltage first
    
   
    int ic=0; //The IC we are currently reading
   int sensenum=0; //The senesor we are currently reading. 
   while(ic<NUMBEROFIC){
       while(sensenum<6){
    int Volt_Of_GPIO=0;
    double Resist_Of_GPIO=0;
           Volt_Of_GPIO=auxcodes[ic][sensenum];
           Resist_Of_GPIO=(Volt_Of_GPIO*VoltageDividerResistance)*(Vin-Volt_Of_GPIO);   //Through Voltage Divider
    TempK= A_Constant + B_Constant*log(Resist_Of_GPIO)+ C_Constant*(pow(log(Resist_Of_GPIO),3));
    if (bank==1){
    TempCBank1[ic][sensenum]=TempK-273.15;
    }
    else if (bank==2){
    TempCBank2[ic][sensenum]=TempK-273.15;
    }
      sensenum=sensenum+1; }
   ic=ic+1;}
   return sensenum; //TODO Not accurate just getting rid of warning.
}

int Test_Temp_Sensors(int Aux_codes_Bank1[][6], int Aux_codes_Bank2[][6]){
   int Fault=0;
    int IC_Counter;
    int TempSense_Counter;
CalculateTemp(bank_1,Aux_codes_Bank1);
CalculateTemp(bank_2,Aux_codes_Bank1);
for (IC_Counter=0;IC_Counter<NUMBEROFIC;IC_Counter++){
for (TempSense_Counter=0;TempSense_Counter<6;TempSense_Counter++){
    if (Aux_codes_Bank1[IC_Counter][TempSense_Counter]>=Over_Temp_Value){
        Fault=OverTempratureThreshold;
    }
    if (Fault==OverTempratureThreshold){
        //If any of the temps are over this threshold exit out of loop and report.
        TempSense_Counter=6;  
        IC_Counter= NUMBEROFIC;
    }
    //For Bank 2
    //If there is no fault for Bank1
    if (Fault!=OverTempratureThreshold){
      if (Aux_codes_Bank1[IC_Counter][TempSense_Counter]>=Over_Temp_Value){
        Fault=OverTempratureThreshold;
    }
    if (Fault==OverTempratureThreshold){
        //If any of the temps are over this threshold exit out of loop and report.
        TempSense_Counter=6;  
        IC_Counter= NUMBEROFIC;
    }
    }
    
}
}
return Fault;
}
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
        LTC6804_DATA_ConfigBank1[ic][4] = CFGR4 & 0xFF; //First  8 Bits of DCC
        LTC6804_DATA_ConfigBank1[ic][5] = (CFGR5) + (DCTO << 4);
    }// Combined DCTO and the Last 4 bits of DCC
    else if (bank == 2) {
        LTC6804_DATA_ConfigBank2[ic][4] = CFGR4 & 0xFF; //First  8 Bits of DCC
        LTC6804_DATA_ConfigBank2[ic][5] = (CFGR5) + (DCTO << 4);
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
int RunBypass_Set(int bank,int cell_codes[][12]) {
    int cellbyp = 0;
    int batvolt = 0;
    int Ic; // Increment for IC
    int Cell; // Increment for Cells
    // Want to make a function for all Batterys Right now it works with just 1 IC
    // Need to understand how he Bank IC and Cell system works 

    for (Ic = 0; Ic < NUMBEROFIC; Ic++) {

        for (Cell = 0; Cell < Cell_Per_Bank; Cell++) // runs threw num of batteries
        {
            batvolt = CheckThresholds(OverVoltageFault,cell_codes[Ic][Cell]);
                if (batvolt == 0) // if bypass needs enabled..
                {
                    SetBypass(bank, Ic, Cell, true); // sets bypass on
                    cellbyp = 1;
                    Battery_Is_Charging_Flag=1;
                }
                if (batvolt == OverVoltageFault) //if bypass needs turned off...
                {
                    SetBypass(bank, Ic, Cell, false); // sets bypass off
                }
        }
    }
    UpdateLT6804(bank);
    return cellbyp;
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

//Not Sure how this  LTC6804_DATA works however will copy for consistency 

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

// FIXME Need to change I2C address!

void ReadCurrentVolt() {
    CVolt[0] = ADS1015readADC_SingleEnded(0, 0x48); //Set channel and IC
    CVolt[1] = ADS1015readADC_SingleEnded(1, 0x48);
    CVolt[2] = ADS1015readADC_SingleEnded(2, 0x48);
    CVolt[3] = ADS1015readADC_SingleEnded(3, 0x48);
    CVolt[4] = ADS1015readADC_SingleEnded(0, 0x4B);
    CVolt[5] = ADS1015readADC_SingleEnded(1, 0x4B);
    ReadVoltToCurrent(); //Converts ADC counts to amps
}

/*******************************************************************
 * @brief           ReadVolt
 * @brief           Reads in the ADC counts and converts to voltages 
 * @return          none
 * @note            Gets it ready for a traditional getter
 *******************************************************************/

void ReadVolt() {
    Volt1 = ADS1015readADC_SingleEnded(2, 0x4B);
    Volt2 = ADS1015readADC_SingleEnded(3, 0x4B);
    Volt1 = (Volt1 / ADCBIT)*5 * VOLTAGERATIO;
    Volt2 = (Volt2 / ADCBIT)*5 * VOLTAGERATIO;
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
    
    CarOn = 0;
}

bool ChargerVal(){
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

int CurrentGet(bool total, char channel) {
    if (total) {
        if (CarOn) {
            return Current[0] + Current[2] + Current[4];
        } else {
            return Current[1] + Current[3] + Current[5];
        }
    } else {
        if (CarOn) {
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
        }

    }
    return -1;
}