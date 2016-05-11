/*******************************************************************
 * @brief           BatteryManagment.c
 * @brief           Adds easy to use functions to the LTC6804.c
 * @return          EU
 * @note            The lib is writen for US
 *******************************************************************/

#include "BatteryManagment.h"
#include "BatteryManagmentPrivate.h"
#include "ADS1015.h"
#include "LT6804.h"
#include "Timers.h"
#include <stdbool.h>
//TODO Need to make a fault status and a use with var
int Read_Status_INC=0;

//|r_config[0]|r_config[1]|r_config[2]|r_config[3]|r_config[4]|r_config[5]|r_config[6]  |r_config[7] |r_config[8]|r_config[9]|  .....    |
//|-----------|-----------|-----------|-----------|-----------|-----------|-------------|------------|-----------|-----------|-----------|
//|IC1 CFGR0  |IC1 CFGR1  |IC1 CFGR2  |IC1 CFGR3  |IC1 CFGR4  |IC1 CFGR5  |IC1 PEC High |IC1 PEC Low |IC2 CFGR0  |IC2 CFGR1  |  .....    |

/*******************************************************************
 * @brief           Start_BMS
 * @brief           Setup The BMS and set configs
 * @return          none
 * @note            
 *******************************************************************/

void Start_BMS(){
    LTC6804_initialize();
    ADS1015Begin();
}
void Charge_Mode(int command){
    //if in charge mode 
    Run_ByPass(cell_codes_Bank1,cell_codes_Bank2);
   
}

void Run_Mode(){
   Read_Total_Voltage(cell_codes_Bank1,cell_codes_Bank2);
}


//TODO figure out fault function of bank 1 and 2
void Run_ByPass(int cell_codesBank1[][12],int cell_codesBank2[][12]){
    //To detect error values
     int Error_Value=0;
     //Bank1
 do {
    Error_Value=Read_Battery(0,cell_codes_Bank1);
    if (Error_Value!=0){
    Read_Status_INC=Read_Status_INC+1;}
   } while(Error_Value!=0);
   //RunBypass_Set(bank_1,NUMBEROFIC,cell_codes_Bank1);
   
   //Bank2
   do {
    Error_Value=Read_Battery(0,cell_codesBank2);
    if (Error_Value!=0){
    Read_Status_INC=Read_Status_INC+1;}
   } while(Error_Value!=0);
  // RunBypass_Set(bank_2,NUMBEROFIC,cell_codesBank2);
   
}

void Read_Total_Voltage(int cell_codesBank1[][12],int cell_codesBank2[][12]){

int Error_Value=0;
    do {
    Error_Value=Read_Battery(0,cell_codes_Bank1);
    if (Error_Value!=0){
    Read_Status_INC=Read_Status_INC+1;}
   } while(Error_Value!=0);
   
    do {
    Error_Value=Read_Battery(0,cell_codesBank2);
    if (Error_Value!=0){
    Read_Status_INC=Read_Status_INC+1;}
   } while(Error_Value!=0);

}
/*******************************************************************
 * @brief           Read_Battery
 * @brief           Reads battery voltage of each cell 
 * @return          none
 * @note            
 *******************************************************************/
//TODO Need to Reference the Bat array
int Read_Battery(int BatteryPlacement,int *cell_codes[NUMBEROFIC][12]) {
    int Read_Status=0;

    switch (BatteryPlacement) {
        case 0: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_ALL);
            LTC6804_adcv();
            Read_Status=LTC6804_rdcv(0,3,*cell_codes);
            break;
        case 1: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_1and7, AUX_CH_ALL);
            LTC6804_adcv();
           Read_Status= LTC6804_rdcv(1,3,*cell_codes); //Cell 1
           Read_Status= LTC6804_rdcv(3,3,*cell_codes); //Cell 7
            break;
        case 2: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_2and8, AUX_CH_ALL);
            LTC6804_adcv();
           Read_Status= LTC6804_rdcv(0,3,*cell_codes); // Cell 2
           Read_Status=LTC6804_rdcv(3,3,*cell_codes); //Cell 8
            break;
        case 3: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_3and9, AUX_CH_ALL);
            LTC6804_adcv();
            Read_Status= LTC6804_rdcv(0,3,*cell_codes); // Cell 3
            Read_Status= LTC6804_rdcv(3,3,*cell_codes); //Cell 9
            break;
        case 4: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_4and10, AUX_CH_ALL);
            LTC6804_adcv();
            Read_Status= LTC6804_rdcv(2,3,*cell_codes); // Cell 4
            Read_Status= LTC6804_rdcv(4,3,*cell_codes); //Cell 10
            break;
        case 5: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_5and11, AUX_CH_ALL);
            LTC6804_adcv();
            Read_Status= LTC6804_rdcv(2,3,*cell_codes); // Cell 5
            Read_Status= LTC6804_rdcv(4,3,*cell_codes); //Cell 11
            break;
        case 6: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_6and12, AUX_CH_ALL);
            LTC6804_adcv();
            Read_Status= LTC6804_rdcv(2,3,*cell_codes); // Cell 6
            Read_Status= LTC6804_rdcv(4,3,*cell_codes); //Cell 12
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
int Read_GPIO(int BatteryPlacement, int *aux_codes[NUMBEROFIC][6])
{  int Read_Status=0;
    switch (BatteryPlacement) {


        case 0: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_ALL);
            LTC6804_adax();
            // What Cells to read,amount of IC,Data
             Read_Status=LTC6804_rdaux(0,3,*aux_codes); // All GPIO and Ref

            break;
        case 1: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO1);
            LTC6804_adax();
            Read_Status=LTC6804_rdaux(1,3,*aux_codes);//GPIO 1
            break;
        case 2: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO2);
            LTC6804_adax();
            Read_Status=LTC6804_rdaux(1,3,*aux_codes);//GPIO 2
            break;
        case 3: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO3);
            LTC6804_adax();
            Read_Status=LTC6804_rdaux(1,3,*aux_codes);//GPIO 3
            break;
        case 4: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO4);
            LTC6804_adax();
            Read_Status=LTC6804_rdaux(2,3,*aux_codes);//GPIO 4
            break;
        case 5: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO5);
            LTC6804_adax();
            Read_Status=LTC6804_rdaux(2,3,*aux_codes);//GPIO 5
            break;
        case 6: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_VREF2);
            LTC6804_adax();
            Read_Status=LTC6804_rdaux(2,3,*aux_codes);//GPIO 6
            break;
        default:
            break;}

    return Read_Status;
}

/*******************************************************************
 * @brief           Set_Bypass
 * @brief           sets bypass for a cell on the stack
 * @return          none
 * @note            
 *******************************************************************/

//Update
void SetBypass(int bank, int ic, int cell, bool value){
	if(value){
		if(cell < 8){
			CFGR4 = CFGR4 | (1 << cell);  //This sets the cell on the stack to on when less than 8 
		}
		else{
			CFGR5 = CFGR5 | (1 << (cell-8)); //This sets the cell on the stack to on when > 8
		}
	}
	else{
		if(cell < 8){
			CFGR4 = CFGR4 & ~(1 << cell); //This sets the cell on the stack to off when less than 8
		}
		else{
			CFGR5 = CFGR5 & ~(1 << (cell-8)); //This sets the cell on the stack to off when > 8
		}
	}
    LTC6804_DATA_Config[bank][(ic*8)+4] = CFGR4& 0xFF; //First  8 Bits of DCC
    LTC6804_DATA_Config[bank][(ic*8)+5] = (CFGR5) + (DCTO<< 4); // Combined DCTO and the Last 4 bits of DCC
}

/*******************************************************************
 * @brief           RunBypass
 * @brief           Controls bypass algorithm for pack
 * @return          none
 * @note            
 *******************************************************************/
int RunBypass_Set(int bank, int ic, int cell_codes[][12]){
    int cellbyp = 0;
    int voltstat=0; 
    int batvolt = 0;
    int i;// Increment for IC
    int c;// Increment for Cells
// Want to make a function for all Batterys Right now it works with just 1 IC
  // Need to understand how he Bank IC and Cell system works 
    
    for (i = 0; i<=NUMBEROFIC;i++){
        
           for(c = 0; c<=Cell_Per_Bank;c++)      // runs threw num of batteries
           {
           //voltstat = CheckUnderOverVoltageFlag();
           if (voltstat==0){
              if(batvolt>=Bypass_High_Limit)      // if bypass needs enabled..
            {
               SetBypass(bank,ic,c,true);           // sets bypass on
               cellbyp = 1;
            }
           if(batvolt <= Bypass_Low_Limit)     //if bypass needs turned off...
           {
               SetBypass(bank,ic,c,false);           // sets bypass off
           }
           }
        }
    }
    UpdateLT6804(bank);
  return cellbyp;}


/*******************************************************************
 * @brief           SetTempEnable
 * @brief           This enables the power to the temp measurements
 * @return          none
 * @note            
 *******************************************************************/


void SetTempEnable(int bank, int ic, bool value){
	if(value){
		CFGR0 = CFGR0 | (1 << 4); //Turn on GPIO 1
	}
	else{
		CFGR0 = CFGR0 & ~(1 << 4); //Turn off GPIO 1
	}
	LTC6804_DATA_Config[bank][ic*8] = CFGR0;
}

/*******************************************************************
 * @brief           CheckUnderOverVoltageFlag
 * @brief           This will respond (true?)if there is a OV/UV 
 * @return          The flag true if there is a fault
 * @note            
 *******************************************************************/

int CheckUnderOverVoltageFlag(){
return 1;}

/*******************************************************************
 * @brief           SetUnderOverVoltage
 * @brief           This will set the UV and OV for all the IC's and banks
 * @return          none
 * @note            
 *******************************************************************/

//Update Under and over voltages. 
void SetUnderOverVoltage(int VUV, int VOV){
    //LTC6804 - PG: 49 
    CFGR1 = VUV& 0xFF; // Ands with the First 8 bits
    CFGR2 = ((VUV & 0xF00)>> 8)+ ((VOV & 0x0F) <<4); // Finish Last bits of VUV start with VOV
    CFGR3 = (VOV& 0xFF0)>>4;       // Finish VOV setup
    
    // load up static reg
    for(k = 0;k<NUMBEROFCH;k++){ //This is for the banks
        for(j=0;j<NUMBEROFIC;j++){ //This is for the IC's on a bank
            LTC6804_DATA_Config[k][j*8 + 1] = CFGR1;
            LTC6804_DATA_Config[k][j*8 + 2] = CFGR2;
            LTC6804_DATA_Config[k][j*8 + 3] = CFGR3;
        }
    }
}

/*******************************************************************
 * @brief           Set_ADC_Mode
 * @brief           This will set the UV and OV for all the IC's and banks
 * @return          none
 * @note            
 *******************************************************************/

//Not Sure how this  LTC6804_DATA works however will copy for consistency 
void Set_ADC_Mode(int bank, int ic, bool ADCOPT_Mode){
    if(ADCOPT_Mode){
    CFGR0= CFGR4 | ADC_MODE_BIT_14k_3k_2k ;
    }
    else {
    CFGR0=CFGR0 & ~ADC_MODE_BIT_14k_3k_2k;   //ADC_MODE_BIT_27k_7k_26
    }
        LTC6804_DATA_Config[bank][ic*8] = CFGR0;
}

//Not Sure how this  LTC6804_DATA works however will copy for consistency 
void Set_REFON_Pin(int bank, int ic, bool REFON_Mode){
    if(REFON_Mode){
    CFGR0= CFGR4 | REFON_TURN_ON ;
    }
    else {
    CFGR0=CFGR0 & ~REFON_TURN_ON;   //REFOFF_TURN_OFF
    }
        LTC6804_DATA_Config[bank][ic*8] = CFGR0;
}
void Get_Stat(int cmd){
   
 // Set_Stat(MD_NORMAL, cmd);
  //LTC6804_ADSTAT();
}
//
void UpdateLT6804(int bank){
  //TODO make Algorithim to determine which bank it is?
    //I dont think we need to calculate the PEC becuase that is done in the LTC6804_wrcfg

   // LTC6804_wrcfg(NUMBEROFIC,LTC6804_DATA_Config[bank]);   //ERROR Need to Fix
    //LTC6804_wrcfg(3,randomarray[2][6]); //Bullshit code to compile
}

/*******************************************************************
 * @brief           ReadCurrentVolt
 * @brief           Reads in the ADC counts from the current sense PCB
 * @return          none
 * @note            This populates the array with raw ADC values
 *******************************************************************/

// FIXME Need to change I2C address!
void ReadCurrentVolt(){
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

void ReadVolt(){
    Volt1 = ADS1015readADC_SingleEnded(2, 0x02);
    Volt2 = ADS1015readADC_SingleEnded(3, 0x02);
    Volt1 = (Volt1/ADCBIT)*5*VOLTAGERATIO;
    Volt2 = (Volt2/ADCBIT)*5*VOLTAGERATIO;
}

/*******************************************************************
 * @brief           ReadVoltToCurrent
 * @brief           converts ADC counts to amps
 * @return          none
 * @note            Gets it ready for a traditional getter
 *******************************************************************/
// FIXME Need to simplify the ADC convert 1 ADC count = 1mV
void ReadVoltToCurrent(){
    for(k = 0;k<5;k++){
        //TODO: Remove for production firmware
        Current[k] = ((CVolt[k]/ADCBIT)*5); ///SHUNTOHMS/CURRENTGAIN) + CurrentOffset[k];
    }
}

/*******************************************************************
 * @brief           ChargerEN
 * @brief           Tells the BMS system that the charger is connected
 * @return          none
 * @note            Sets flag for reading
 *******************************************************************/

void ChargerEN(){
    CarOn = 0;
}

/*******************************************************************
 * @brief           CurrentCoulombCount
 * @brief           This function "should" get us a coulomb count (I hope)
 * @return          none
 * @note            This fcn is controlled by a timer for a true CC (timer 2) 
 *******************************************************************/

void CurrentCoulombCount(int tme){
    if(CarOn){                        //Positive charing current
        CC1 = CC1 - (Current[0]*tme);
        CC2 = CC2 - (Current[2]*tme);
        CC3 = CC3 - (Current[4]*tme);
    }
    else{                             //negative discharging current  
        CC1 = CC1 + (Current[1]*tme);
        CC2 = CC2 + (Current[3]*tme);
        CC3 = CC3 + (Current[5]*tme);
    }
}

/*******************************************************************
 * @brief           CurrentGet
 * @brief           getter
 * @return          none
 * @note            This can give you a different response depending on input
 *******************************************************************/

int CurrentGet(bool total, char channel){
    if(total){
        if(CarOn){
            return Current[0] + Current[2] + Current[4];
        }
        else{
            return Current[1] + Current[3] + Current[5];
        }
    }
    else{
        if(CarOn){
            switch(channel){
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
        }
        else{
            switch(channel){
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