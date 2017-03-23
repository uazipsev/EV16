#include "BatteryManagementCells.h"

        //Arrays for Cell Voltages
int cell_codes_Bank1[NUMBEROFIC][12];
int cell_codes_Bank2[NUMBEROFIC][12];

double Average_cell_codes_Bank1[NUMBEROFIC][12];
double Average_cell_codes_Bank2[NUMBEROFIC][12];

double Min_Cell_Voltage[2][3];
double Max_Cell_Voltage[2][3];
//Arrays for GPIO

double Module_Voltage_Value[2][3];



int Read_Total_Voltage(int cell_codesBank1[][12], int cell_codesBank2[][12]) {
    int Fault = 0;
    //Reading the registers
    Fault = Read_Cell_Voltage_Bank(cell_codesBank1);
    if (Fault != 0) {
        return Fault;
    }

    Fault = Read_Cell_Voltage_Bank(cell_codesBank2);
    if (Fault != 0) {
        return Fault;
    }

    Fault=Insert_Cell_Data_Total(cell_codesBank1, cell_codesBank2);
     if (Fault == 0) {
 Pack_Cell_Voltage_Sum();
 }
    return Fault;
}

int Insert_Cell_Data_Total(int New_Cell_Data_Bank1[][12], int New_Cell_Data_Bank2[][12]){
        int Fault=0;
    Insert_Cell_Data_Bank(bank_1,New_Cell_Data_Bank1);
    Insert_Cell_Data_Bank(bank_2,New_Cell_Data_Bank2);
    if (Starting_Samples==false){
Fault=Check_Array_Faults_Cells();}
    return Fault;
}

void Insert_Cell_Data_Bank(int bank_num, int I_New_Cell_Data[][12]){
    double D_New_Cell_Data[NUMBEROFIC][12];
Convert_To_Voltage_Cell(I_New_Cell_Data,D_New_Cell_Data);
Update_Average_Array_Cell(bank_num, D_New_Cell_Data);
}


/*******************************************************************
 * @Title           Read_GPIO_Bank
 * @brief           Reads the GPIO pins of a given bank.                  
 * @return          If the read is a failure it will try to read up 
 *                  to 10 times before it returns a fault.        
 *******************************************************************/
int Read_Cell_Voltage_Bank(int Cell_Voltage_codes[][12]){
    int  Read_Status_INC = 0;
    int Fault;
        do { 
             Fault = Send_Read_CellV_Command(0, Cell_Voltage_codes);
            if (Fault != 0) {
                Read_Status_INC = Read_Status_INC + 1;
           }
   
      } while (Fault != 0 && Read_Status_INC <= 10);
      //If we cant read the registers 10 times in the row call a fault. 
       if (Read_Status_INC > 10) {
          Fault = ReadVoltRegFault;
       }
    return Fault;
}


/*******************************************************************
 * @Title           Send_Read_GPIO_Command
 * @Argument 1      This dictates which GPIO pin is going to be read. 
 *                  0=all then each number reads that GPIO number.
 * 
 * @Argument 2      Array that will hold the read data.
 * 
 * @brief           Reads GPIO pins based on Read_Option for the Temp sensors.
 * @return          none
 *******************************************************************/

int Send_Read_CellV_Command(int ReadOption, int cell_codes[][12]) {
    int Fault = 0;
    switch (ReadOption) {
        //The difference of ReadOption determines which set of cells are going to be read where case 0 is all of the voltage cells in a IC.
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
            Fault = LTC6804_rdcv(0, NUMBEROFIC, cell_codes);
            break;
        case 1:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_1and7, AUX_CH_ALL);
            wakeup_idle();
            LTC6804_adcv();
            wakeup_idle();
            Fault = LTC6804_rdcv(1, NUMBEROFIC, cell_codes); //Cell 1
            Fault = LTC6804_rdcv(3, NUMBEROFIC, cell_codes); //Cell 7
            break;
        case 2:
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_2and8, AUX_CH_ALL);
            wakeup_idle();
            LTC6804_adcv();
            wakeup_idle();
            Fault = LTC6804_rdcv(1, NUMBEROFIC, cell_codes); // Cell 2
            Fault = LTC6804_rdcv(3, NUMBEROFIC, cell_codes); //Cell 8
            break;
        case 3:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_3and9, AUX_CH_ALL);
            LTC6804_adcv();
            wakeup_idle();
            Fault = LTC6804_rdcv(1, NUMBEROFIC, cell_codes); // Cell 3
            Fault = LTC6804_rdcv(3, NUMBEROFIC, cell_codes); //Cell 9
            break;
        case 4:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_4and10, AUX_CH_ALL);
            LTC6804_adcv();
            wakeup_idle();
            Fault = LTC6804_rdcv(2, NUMBEROFIC, cell_codes); // Cell 4
            Fault = LTC6804_rdcv(4, NUMBEROFIC, cell_codes); //Cell 10
            break;
        case 5:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_5and11, AUX_CH_ALL);
            LTC6804_adcv();
            wakeup_idle();
            Fault = LTC6804_rdcv(2, NUMBEROFIC, cell_codes); // Cell 5
            Fault = LTC6804_rdcv(4, NUMBEROFIC, cell_codes); //Cell 11
            break;
        case 6:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_6and12, AUX_CH_ALL);
            LTC6804_adcv();
            wakeup_idle();
            Fault = LTC6804_rdcv(2, NUMBEROFIC, cell_codes); // Cell 6
            Fault = LTC6804_rdcv(4, NUMBEROFIC, cell_codes); //Cell 12
            break;
        default:
            Fault = ReadVoltRegFault;
            break;
    }
    return Fault;
}





/*******************************************************************
 * @Title           Convert_To_Voltage_Temp
 * @brief           Data to be converted to the appropriate voltage level
 * @return          none        
 *******************************************************************/
void Convert_To_Voltage_Cell(int I_Array_Bank[][12],double D_Array_Bank[][12]) {
    int ic = 0;
    int cell = 0;
    int Temp_ValB1 = 0;
    while (ic < NUMBEROFIC) {
        while (cell < Cell_Per_Bank) {
             //Had to convert to float from int first than mutiply the floating number gave me errors otherwise.
            Temp_ValB1 = I_Array_Bank[ic][cell];
            D_Array_Bank[ic][cell] = Temp_ValB1*0.0001;
            cell++;
        }
        cell=0;
        ic++;
    }
}



/*******************************************************************
 * @Title           Update_Average_Array_Temp
 * @brief           Adds the newly acquired temp readings and does the weight average 
 *                  of the current average of the Temperature values. The weight is .80 to .20 
 * @return          none          
 *******************************************************************/
void Update_Average_Array_Cell(int bank, double Array_Bank[][12]) {
    int Ic = 0;
    int cell = 0;
    //If first sample there is no weighted needed because it is the first sample.

    if (Starting_Samples == true) {
        while (Ic < NUMBEROFIC) {
            while (cell < 12) {

                //Cell Voltages
                if (bank == bank_1) {
                    Average_cell_codes_Bank1[Ic][cell] = Array_Bank[Ic][cell];
                }
                else if (bank == bank_2) {
                    Average_cell_codes_Bank2[Ic][cell] = Array_Bank[Ic][cell];
                }
                cell = cell + 1;
            }
            cell = 0;
            Ic = Ic + 1;
        }
    }
    else if (Starting_Samples == false) {
        while (Ic < NUMBEROFIC) {
            while (cell < 12) {
                if (bank == bank_1) {
                    Average_cell_codes_Bank1[Ic][cell] = (.8 * (Average_cell_codes_Bank1[Ic][cell])+ (.2 * Array_Bank[Ic][cell]));
                }
                else if (bank == bank_2) {
                    Average_cell_codes_Bank2[Ic][cell] = (.8 * (Average_cell_codes_Bank2[Ic][cell]) +(.2 * Array_Bank[Ic][cell]));
                }
                cell = cell++;
            }
            cell = 0;
            Ic = Ic++;
        }
    }

}


int Check_Array_Faults_Cells() {
    int Fault=0;
    Fault = Check_Cell_Thresholds_Bank(bank_1, Average_cell_codes_Bank1);
    if (Fault != 0) {
        return Fault;
    }
    Fault = Check_Cell_Thresholds_Bank(bank_2, Average_cell_codes_Bank2);
    return Fault;

}


//Function to check all the voltage thresholds in the pack. And assigning minimum and maximum values.

int Check_Cell_Thresholds_Bank(int bank, double cell_codes_bank[][12]) {
    int Fault = 0;
    //Going through every IC and cell
    for (int CurrentIC = 0; CurrentIC < NUMBEROFIC; CurrentIC++) {
        for (int cell = 0; cell < 12; cell++) {
            
            Fault = Check_Thresholds_Cell(cell_codes_bank[CurrentIC][cell]);
           
                //Checking if the cell has the lowest voltage in the pack
                if (cell_codes_bank[CurrentIC][cell] < Min_Cell_Voltage[bank-1][Data_Value]) {
                    // Creating location of the lowest Cell Voltage.
                    Min_Cell_Voltage[bank-1][Data_Value] = cell_codes_bank[CurrentIC][cell];
                    Min_Cell_Voltage[bank-1][IC_LOCATION] = CurrentIC;
                    Min_Cell_Voltage[bank-1][SENSOR_LOCATION] = cell;
                }

                //Checking if the cell has the highest voltage in the pack
                if (cell_codes_bank[CurrentIC][cell] > Max_Cell_Voltage[bank-1][Data_Value]) {
                    // Creating location of the highest Cell Voltage.
                    Max_Cell_Voltage[bank-1][Data_Value] = cell_codes_bank[CurrentIC][cell];
                    Max_Cell_Voltage[bank-1][IC_LOCATION] = CurrentIC;
                    Max_Cell_Voltage[bank-1][SENSOR_LOCATION] = cell;
                }
            if (Fault != 0) {
                return Fault;
            }
        }
    }
    return Fault;
}


//Function to check all the voltage thresholds in the pack. And assigning minimum and maximum values.

int Check_Cell_Thresholds_Bank2(int bank, double cell_codes_bank[][12]) {
    int Fault = 0;
    //Going through every IC and cell
    for (int CurrentIC = 0; CurrentIC < NUMBEROFIC; CurrentIC++) {
        for (int cell = 0; cell < 12; cell++) {
            
            Fault = Check_Thresholds_Cell(cell_codes_bank[CurrentIC][cell]);
            if (bank == bank_1) {
                //Checking if the cell has the lowest voltage in the pack
                if (cell_codes_bank[CurrentIC][cell] < Min_Cell_Voltage[bank][Data_Value]) {
                    // Creating location of the lowest Cell Voltage.
                    Min_Cell_Voltage[Bank1_Array_Indicator][Data_Value] = cell_codes_bank[CurrentIC][cell];
                    Min_Cell_Voltage[Bank1_Array_Indicator][IC_LOCATION] = CurrentIC;
                    Min_Cell_Voltage[Bank1_Array_Indicator][SENSOR_LOCATION] = cell;
                }

                //Checking if the cell has the highest voltage in the pack
                if (cell_codes_bank[CurrentIC][cell] > Max_Cell_Voltage[bank][Data_Value]) {
                    // Creating location of the highest Cell Voltage.
                    Max_Cell_Voltage[Bank1_Array_Indicator][Data_Value] = cell_codes_bank[CurrentIC][cell];
                    Max_Cell_Voltage[Bank1_Array_Indicator][IC_LOCATION] = CurrentIC;
                    Max_Cell_Voltage[Bank1_Array_Indicator][SENSOR_LOCATION] = cell;
                }
            }                //Have to repeat even though its redundant because of cell_codes_bank2
            else if (bank == bank_2) {
                if (cell_codes_bank[CurrentIC][cell] < Min_Cell_Voltage[bank][Data_Value]) {

                    Min_Cell_Voltage[Bank2_Array_Indicator][Data_Value] = cell_codes_bank[CurrentIC][cell];
                    Min_Cell_Voltage[Bank2_Array_Indicator][IC_LOCATION] = CurrentIC;
                    Min_Cell_Voltage[Bank2_Array_Indicator][SENSOR_LOCATION] = cell;
                }
                if (cell_codes_bank[CurrentIC][cell] > Max_Cell_Voltage[bank][Data_Value]) {

                    Max_Cell_Voltage[Bank2_Array_Indicator][Data_Value] = cell_codes_bank[CurrentIC][cell];
                    Max_Cell_Voltage[Bank2_Array_Indicator][IC_LOCATION] = CurrentIC;
                    Max_Cell_Voltage[Bank2_Array_Indicator][SENSOR_LOCATION] = cell;
                }
            }
            if (Fault != 0) {
                return Fault;
            }
        }
    }
    return Fault;
}


//Checking if any of the voltages are critically low or high which would need to create a fault.

int Check_Thresholds_Cell(double data) {
    int Fault = 0;
    Fault = TestThreshold(OverVoltageFault, data);
    if (Fault != 0) {
        return Fault;
    }
    Fault = TestThreshold(UnderVoltageFault, data);

    return Fault;

}


//Checking if any of the voltages are critically low or high which would need to create a fault.
int TestThreshold(int test, double data) {
    switch (test) {
        case OverVoltageFault:
            if (data >= Over_Voltage_Value){
                return OverVoltageFault;}
            break;
        case UnderVoltageFault:
            if (data <= Under_Voltage_Value) {
                return UnderVoltageFault;
            }
            break;
        default:
            return Invalid_Test_Cond; //Return Invalid Test Condition
    }
    return 0;
}

//This function is to sum up the voltage of each cell(12) and each ltc6804(3) into a array for each module to be sent to the ECU

void Pack_Cell_Voltage_Sum() {
    double Temporary_Module[2][3]={0};
    int ic, sense_num;
    //For both Banks
    for (ic = 0; ic < 9; ic++) {
        switch (ic) {
                //Each Module has 3 LTC6804 with 12 voltage cells a piece. Summing the total voltage for each module.
            case 0:
            case 1:
            case 2:
                for (sense_num = 0; sense_num < 12; sense_num++) {
                    Temporary_Module[Bank1_Array_Indicator][0] = Average_cell_codes_Bank1[ic][sense_num] + Temporary_Module[Bank1_Array_Indicator][0];
                    Temporary_Module[Bank2_Array_Indicator][0] = Average_cell_codes_Bank2[ic][sense_num] + Temporary_Module[Bank2_Array_Indicator][0];


                }
                break;
            case 3:
            case 4:
            case 5:
                for (sense_num = 0; sense_num < 12; sense_num++) {
                    Temporary_Module[Bank1_Array_Indicator][1] = Average_cell_codes_Bank1[ic][sense_num] + Temporary_Module[Bank1_Array_Indicator][1];
                    Temporary_Module[Bank2_Array_Indicator][1] = Average_cell_codes_Bank2[ic][sense_num] + Temporary_Module[Bank2_Array_Indicator][1];
                }
                break;
            case 6:
            case 7:
            case 8:
                for (sense_num = 0; sense_num < 12; sense_num++) {
                    Temporary_Module[Bank1_Array_Indicator][2] = Average_cell_codes_Bank1[ic][sense_num] + Temporary_Module[Bank1_Array_Indicator][2];
                    Temporary_Module[Bank2_Array_Indicator][2] = Average_cell_codes_Bank2[ic][sense_num] + Temporary_Module[Bank2_Array_Indicator][2];

                }
                break;
        }
    }
    for (int bank_num=0; bank_num<=Bank2_Array_Indicator;bank_num++){
    for (int module_num=0; module_num<=2;module_num++){
   Module_Voltage_Value[bank_num][module_num] =Temporary_Module[bank_num][module_num];
    }
    
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
    if (module>3||module<0){
        return -1;
    }
     if (bank>2||bank<1){
        return -1;
    }
 return Module_Voltage_Value[bank-1][module]; //bank-1 for arrays bank_1=1 thus 1-1=0 for the array. 
}

//This function gets a attribute of the extreme voltage.
//Where type equal what extreme, Parm equals what property of that extreme (location,data etc.) and bank is what bank we are looking at.
double Get_Extreme_Voltage(int type, int parm, int bank) {
    //If we want to pick the minium voltage.
    if (parm > 3 || parm < 0) {
        return -1;
    }
    if (bank > 2 || bank < 1) {
        return -1;
    }
    if (type == min_select) {
        return Min_Cell_Voltage[bank - 1][parm];
    }
    else if (type == max_select) {
        return Max_Cell_Voltage[bank - 1][parm];
    }
    else {
        return -1;
    }
}






//This function gets a attribute of the extreme voltage.
//Where type equal what extreme, Parm equals what property of that extreme (location,data etc.) and bank is what bank we are looking at.
double Get_Extreme_Voltage2(int type, int parm, int bank) {
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
