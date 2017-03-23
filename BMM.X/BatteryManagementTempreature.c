#include "BatteryManagementTemperature.h"
#include <math.h>

int Aux_codes_Bank1[NUMBEROFIC][6];
int Aux_codes_Bank2[NUMBEROFIC][6];


double Average_Temperature_Codes_Bank1[NUMBEROFIC][6];
double Average_Temperature_Codes_Bank2[NUMBEROFIC][6];

double Min_Temp[2][3];
double Max_Temp[2][3];
double Module_Average_Temp_Value[2][3];



/*******************************************************************
 * @Title           Read_Total_Temperature
 * @brief           Reads the GPIO pins of both banks and converts 
 *                  it to Temperature and sends it to weight average.                   
 * @return          A fault if it is reported.       
 *******************************************************************/

int Read_Total_Temperature(int Aux_codes_Bank1[][6], int Aux_codes_Bank2[][6]) {
    int Fault = 0;

    Fault = Read_GPIO_Bank(Aux_codes_Bank1);
    if (Fault != 0) {
        return Fault;
    }
    Fault = Read_GPIO_Bank(Aux_codes_Bank2);
    if (Fault != 0) {
        return Fault;
    }
    Fault = Convert_To_Temp_Total(Aux_codes_Bank1, Aux_codes_Bank2);
    if (Fault==0){
    Pack_Temperature_Sum();}
    return Fault;
}



/*******************************************************************
 * @Title           Read_GPIO_Bank
 * @brief           Reads the GPIO pins of a given bank.                  
 * @return          If the read is a failure it will try to read up 
 *                  to 10 times before it returns a fault.        
 *******************************************************************/
int Read_GPIO_Bank(int Aux_codes[][6]){
    int  Read_Status_INC = 0;
    int Fault;
        do { 
             Fault = Send_Read_GPIO_Command(0, Aux_codes);
            if (Fault != 0) {
                Read_Status_INC = Read_Status_INC + 1;
           }
   
      } while (Fault != 0 && Read_Status_INC <= 10);
       if (Read_Status_INC > 10) {
          Fault = ReadAuxRegFault;
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

int Send_Read_GPIO_Command(int Read_Option, int aux_codes[NUMBEROFIC][6]) {
    int Fault = 0;
    switch (Read_Option) {
        case 0:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_ALL);
            LTC6804_adax();
            wakeup_idle();
            Fault = LTC6804_rdaux(0, NUMBEROFIC, aux_codes); // All GPIO and Ref
            break;
        case 1:
            wakeup_idle();
            set_adc(MD_FILTERED, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO1);
            LTC6804_adax();
            wakeup_idle();
            Fault = LTC6804_rdaux(1, NUMBEROFIC, aux_codes); //GPIO 1
            break;
        case 2:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO2);
            LTC6804_adax();
            wakeup_idle();
            Fault = LTC6804_rdaux(1, NUMBEROFIC, aux_codes); //GPIO 3
            break;
        case 3:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO3);
            LTC6804_adax();
            wakeup_idle();
            Fault = LTC6804_rdaux(1, NUMBEROFIC, aux_codes); //GPIO 3
            break;
        case 4:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO4);
            LTC6804_adax();
            wakeup_idle();
            Fault = LTC6804_rdaux(2, NUMBEROFIC, aux_codes); //GPIO 4
            break;
        case 5:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO5);
            LTC6804_adax();
            wakeup_idle();
            Fault = LTC6804_rdaux(2, NUMBEROFIC, aux_codes); //GPIO 5
            break;
        case 6:
            wakeup_idle();
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_VREF2);
            LTC6804_adax();
            wakeup_idle();
            Fault = LTC6804_rdaux(2, NUMBEROFIC, aux_codes); //VREF
            break;
        default:
            Fault = ReadAuxRegFault;
            break;
    }
    return Fault;
}






/*******************************************************************
 * @Title           Convert_To_Temp_Total
 * @Argument        Two temporary 2d-arrays that holds the voltage data from the sensors of the BMS.
 * @return          A Fault if a fault has occurred. 
 * 
 * @ Explanation:   
 *   This function takes new data acquired by the LTC6804 from each bank and sends it to 
 *   Convert_To_Temp_Bank() to convert while checking for faults with Check_Array_Faults_Temp()
 *         
 *******************************************************************/
int Convert_To_Temp_Total(int New_Temp_Data_Bank1[][6], int New_Temp_Data_Bank2[][6]) {
    int Fault = 0;
    
    Convert_To_Temp_Bank(bank_1,New_Temp_Data_Bank1);
    Convert_To_Temp_Bank(bank_2,New_Temp_Data_Bank2);
    if (Starting_Samples==false){
    Fault=Check_Array_Faults_Temp();}
    return Fault;
}



/*******************************************************************
 * @Title           Convert_To_Temp_Bank
 * @Argument 1      A integer to detect which bank the function is operating on
 * @Argument 2      The Temporary data that will be converted to temperature. 
 * @return          None
 * 
 * @ Explanation:   
 *   This function takes the data from New_Temp_Data and converts the data into 
 *   a temperature that is then combined into a weight version of that data.
 *         
 *******************************************************************/
void  Convert_To_Temp_Bank(int bank_num, int I_New_Temp_Data[][6]) {
    double D_New_Temp_Data[NUMBEROFIC][6]; //The data that will be transferred.
    Convert_To_Voltage_Temp(I_New_Temp_Data,D_New_Temp_Data); //Converts the data into a voltage scale this is usable.
    CalculateTemp(D_New_Temp_Data); //Convert voltage reading to a temp in C
    Update_Average_Array_Temp( bank_num, D_New_Temp_Data); //Updates the average of all of th eC 
}



/*******************************************************************
 * @Title           Convert_To_Voltage_Temp
 * @brief           Data to be converted to the appropriate voltage level
 * @return          none        
 *******************************************************************/
void Convert_To_Voltage_Temp(int Int_Array_Bank[][6],double Double_Array_Bank[][6]) {
    int ic;
    int cell;
    int Temp_Val = 0;
    for (ic=0;ic < 9;ic++) {
        for (cell=0;cell < Temp_Sens_Per_IC ;cell++) {
            //Had to convert to float from int first than mutiply the floating number gave me errors otherwise.
            Temp_Val = Int_Array_Bank[ic][cell]; 
            Double_Array_Bank[ic][cell] = Temp_Val * 0.0001;
        }
    }
}


/*******************************************************************
 * @Title           CalculateTemp
 * @brief           Calculates the temperature by a voltage divider 
 *                  and a thermistor. math is based on the NXFT15XH103fa2b025  
 * @return          none           
 *******************************************************************/
void CalculateTemp( double Array_Bank[][6]) {
    float TempC = 0;
    float TempK = 0;
    int ic; //The IC we are currently reading
    int sensenum; //The sensor we are currently reading.
    for (ic=0;ic < 9;ic++) {
        for (sensenum=0;sensenum < Temp_Sens_Per_IC; sensenum++) {
            float Volt_Of_GPIO = 0;
            float Resist_Of_GPIO = 0;
            float Voltage_diff = 0;
            Volt_Of_GPIO = Array_Bank[ic][sensenum]; //v2 vin v1 rgpio thermo r2  r1 10k
            Resist_Of_GPIO = (Volt_Of_GPIO * VoltageDividerResistance); //TOTAL EQUATION  R2=(VO*R1)/(Vin-Vo)  
            Voltage_diff = (Vin - Volt_Of_GPIO);
            Resist_Of_GPIO = Resist_Of_GPIO / Voltage_diff; //Through Voltage Divider  TOTAL EQUATION R2=(VO*R1)/(Vin-Vo)
            TempK = (To + ((Inverse_B_Constant) * (log(Resist_Of_GPIO / 10000))));
            TempK = (1 / TempK);
            TempC = TempK - 273.15; //Kelvin to Celsius offset
                Array_Bank[ic][sensenum] = TempC;
        }
    }
}



/*******************************************************************
 * @Title           Update_Average_Array_Temp
 * @brief           Adds the newly acquired temp readings and does the weight average 
 *                  of the current average of the Temperature values. The weight is .80 to .20 
 * @return          none          
 *******************************************************************/
void Update_Average_Array_Temp(int bank, double Array_Bank[][6]) {
    int Ic;
    int cell;
    //If first sample there is no weighted needed becuase it is the first sample.
    if (Starting_Samples == true) {
        for (Ic=0;Ic < NUMBEROFIC;Ic++) {
            for (cell=0;cell < Temp_Sens_Per_IC; cell++) {
                //GPIO Values
                if (bank==bank_1){
                Average_Temperature_Codes_Bank1[Ic][cell] = Array_Bank[Ic][cell];}
                else if (bank==bank_2){
                Average_Temperature_Codes_Bank2[Ic][cell] = Array_Bank[Ic][cell];}
            }
        }
    } else if (Starting_Samples == false) {
        for (Ic=0;Ic < NUMBEROFIC; Ic++) {
            for (cell=0;cell < Temp_Sens_Per_IC; cell++) {
                if (bank==bank_1){
                Average_Temperature_Codes_Bank1[Ic][cell] = (.8 * (Average_Temperature_Codes_Bank1[Ic][cell])+ (.2 * Array_Bank[Ic][cell]));}
                  else if (bank==bank_2){
                Average_Temperature_Codes_Bank2[Ic][cell] = (.8 * (Average_Temperature_Codes_Bank2[Ic][cell]) +(.2 * Array_Bank[Ic][cell]));
                  }
            }
        }
    }

}



/*******************************************************************
 * Title            Pack_Temperature_Sum
 * @return          none
 * @note            This functions goes through and finds the average Temperature from each BMS module.
 *                  It does this by adding all 15 temp sensors up and then dividing it by 15.      
 *******************************************************************/
void Pack_Temperature_Sum() {
    double Temporary_Module[2][3]={0};//This module holds the temp sensors as its totaling for the average.
    int ic, sense_num, Bank_Num ;
    //This function has 3 nested loops. One for each sensor in a IC.
    //One for each IC in a bank. and finally One for each bank.
    for (Bank_Num=0;Bank_Num < 2;Bank_Num++) {
        for (ic=0;ic < 9;ic++) {
            //Each case falls through 3 because there is 3 IC per module.
            switch (ic) {
                    //Each Module has 3 LTC6804 with 12 voltage cells a piece. Summing that up for each module.
                case 0:
                case 1:
                case 2:
                    for (sense_num=0;sense_num < Temp_Sens_Per_IC;sense_num++) { //We are doing 5 because the 6th is a voltage regulator and that is not a temperature
                        if (Bank_Num == 0) {
                           
                            Temporary_Module[Bank_Num][0] = Average_Temperature_Codes_Bank1[ic][sense_num] + Temporary_Module[Bank_Num][0];
                        }
                        if (Bank_Num == 1) {
                            Temporary_Module[Bank_Num][0] = Average_Temperature_Codes_Bank2[ic][sense_num] + Temporary_Module[Bank_Num][0];
                        }
                    }
                    break;
                case 3:
                case 4:
                case 5:
                    for (sense_num=0;sense_num < Temp_Sens_Per_IC;sense_num++) { //We are doing 5 because the 6th is a voltage regulator and that is not a temperature
                        if (Bank_Num == 0) {
                            Temporary_Module[Bank_Num][1] = Average_Temperature_Codes_Bank1[ic][sense_num] + Temporary_Module[Bank_Num][1];
                        }
                        if (Bank_Num == 1) {
                            Temporary_Module[Bank_Num][1] = Average_Temperature_Codes_Bank2[ic][sense_num] + Temporary_Module[Bank_Num][1];
                        }
                    }
                    break;
                case 6:
                case 7:
                case 8:
                   for (sense_num=0;sense_num < Temp_Sens_Per_IC;sense_num++){ //We are doing 5 because the 6th is a voltage regulator and that is not a temperature
                        if (Bank_Num == 0) {
                            Temporary_Module[Bank_Num][2] = Average_Temperature_Codes_Bank1[ic][sense_num] + Temporary_Module[Bank_Num][2];
                        }
                        if (Bank_Num == 1) {
                            Temporary_Module[Bank_Num][2] = Average_Temperature_Codes_Bank2[ic][sense_num] + Temporary_Module[Bank_Num][2];
                        }
                    }
                    break;
            }
        }
        //      Once one bank is finished I am taking the 3 modules from this bank 
        //      and dividing it by the total amount of sensors per bank (15) to get average temp of the module. We might want total temp if that is the case we will need to delete these functions.
        Module_Average_Temp_Value[Bank_Num][0] = (Temporary_Module[Bank_Num][0] / Num_TempSense_Per_Module);
        Module_Average_Temp_Value[Bank_Num][1] = (Temporary_Module[Bank_Num][1] / Num_TempSense_Per_Module);
        Module_Average_Temp_Value[Bank_Num][2] = (Temporary_Module[Bank_Num][2] / Num_TempSense_Per_Module);
    }
}


  
/*******************************************************************
 * Title            Check_Array_Faults_Temp
 * Arguments         
 *                  This function checks each temperature sensor and determine 
 *                  if it is the maximum of minimum temperature and assigns it .
 *                  It will then check if the readings are above a threshold. 
 *                  If it is it will return a fault. 
 * @return          Fault for extreme temperature 
 * @note            
 *******************************************************************/
int Check_Array_Faults_Temp() {
    int IC_Counter, TempSense_Counter, Fault;
    Fault = 0;
    for (IC_Counter = 0; IC_Counter < 9; IC_Counter++) {
        for (TempSense_Counter = 0; TempSense_Counter < Temp_Sens_Per_IC; TempSense_Counter++) {
            //Checking for max or min values to send to ECU
            //Min Bank 1
            if (Average_Temperature_Codes_Bank1[IC_Counter][TempSense_Counter] < Min_Temp[Bank1_Array_Indicator][Data_Value]) {
                Min_Temp[Bank1_Array_Indicator][Data_Value] = Average_Temperature_Codes_Bank1[IC_Counter][TempSense_Counter];
                Min_Temp[Bank1_Array_Indicator][IC_LOCATION] = IC_Counter;
                Min_Temp[Bank1_Array_Indicator][SENSOR_LOCATION] = TempSense_Counter;

            } //Max Bank 1
            if (Average_Temperature_Codes_Bank1[IC_Counter][TempSense_Counter] > Max_Temp[Bank1_Array_Indicator][Data_Value]) {

                Max_Temp[Bank1_Array_Indicator][Data_Value] = Average_Temperature_Codes_Bank1[IC_Counter][TempSense_Counter];
                Max_Temp[Bank1_Array_Indicator][IC_LOCATION] = IC_Counter;
                Max_Temp[Bank1_Array_Indicator][SENSOR_LOCATION] = TempSense_Counter;
            }

            //Min Bank 2
            if (Average_Temperature_Codes_Bank2[IC_Counter][TempSense_Counter] < Min_Temp[Bank2_Array_Indicator][Data_Value]) {

                Min_Temp[Bank2_Array_Indicator][Data_Value] = Average_Temperature_Codes_Bank2[IC_Counter][TempSense_Counter];
                Min_Temp[Bank2_Array_Indicator][IC_LOCATION] = IC_Counter;
                Min_Temp[Bank2_Array_Indicator][SENSOR_LOCATION] = TempSense_Counter;
                //Max Bank 2
            }
            if (Average_Temperature_Codes_Bank2[IC_Counter][TempSense_Counter] > Max_Temp[Bank2_Array_Indicator][Data_Value]) {

                Max_Temp[Bank2_Array_Indicator][Data_Value] = Average_Temperature_Codes_Bank2[IC_Counter][TempSense_Counter];
                Max_Temp[Bank2_Array_Indicator][IC_LOCATION] = IC_Counter;
                Max_Temp[Bank2_Array_Indicator][SENSOR_LOCATION] = TempSense_Counter;
            }
 //Checking if The Temperature Function is above temperature thresholds
            if (Average_Temperature_Codes_Bank1[IC_Counter][TempSense_Counter] >= Over_Temp_Value) {
                Fault = OverTempratureThreshold;
                return Fault;
            }
           
            if (Average_Temperature_Codes_Bank2[IC_Counter][TempSense_Counter] >= Over_Temp_Value) {
                    Fault = OverTempratureThreshold;
                    return Fault;
            }
            

        }
    }
}
/*******************************************************************
 * Title            Get_Extreme_Temperature
 * Arguments        The type of extreme the parameter of the extreme and which bank. 
 *                  This function returns a property of the maximum or minimum temperature. 
 *                  It can return the Value, the IC location, or the Sensor Location, 
 *                  of any maximum or minimum. 
 * @return          The value that has been requested.           
 *******************************************************************/

double Get_Extreme_Temperature(int type, int parm, int bank) {
    if (parm > 3 || parm < 0) {
        return -1;
    }
    if (bank > 2 || bank < 1) {
        return -1;
    }

    if (type == min_select) {

        return Min_Temp[bank - 1][parm];

    } else if (type == max_select) {
        return Max_Temp[bank - 1][parm];

    } else {
        return -1;
    }

}



/*******************************************************************
 * @Title           gettemp
 * @brief           Gets the temperature of a certain sensor
 *                  of the current average of the Temperature values. The weight is .80 to .20 
 * @return          none          
 *******************************************************************/
double gettemp(int ic, int num, int bank) {
    if (bank == 1) {
        return Average_Temperature_Codes_Bank1[ic][num];
    }
    if (bank == 2) {
        return Average_Temperature_Codes_Bank2[ic][num];
    }
}
