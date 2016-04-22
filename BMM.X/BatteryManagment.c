
#include "BatteryManagment.h"
#include "BatteryManagmentPrivate.h"
#include "ADS1015.h"
#include "LT6804.h"
#include "Timers.h"
#include <stdbool.h>



//|r_config[0]|r_config[1]|r_config[2]|r_config[3]|r_config[4]|r_config[5]|r_config[6]  |r_config[7] |r_config[8]|r_config[9]|  .....    |
//|-----------|-----------|-----------|-----------|-----------|-----------|-------------|------------|-----------|-----------|-----------|
//|IC1 CFGR0  |IC1 CFGR1  |IC1 CFGR2  |IC1 CFGR3  |IC1 CFGR4  |IC1 CFGR5  |IC1 PEC High |IC1 PEC Low |IC2 CFGR0  |IC2 CFGR1  |  .....    |

void Start_BMS(){
    LTC6804_initialize();
    ADS1015Begin();
}

void Read_Battery(int BatteryPlacement) {
    switch (BatteryPlacement) {
        case 0: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_ALL);
            LTC6804_adcv();
           // LTC6804_rdcv(0,3,Voltage_data[][12]);
            break;
        case 1: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_1and7, AUX_CH_ALL);
            LTC6804_adcv();
           // LTC6804_rdcv(1,3,Voltage_data[][12]); //Cell 1
           // LTC6804_rdcv(3,3,Voltage_data[][12]); //Cell 7
            break;
        case 2: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_2and8, AUX_CH_ALL);
            LTC6804_adcv();
            //LTC6804_rdcv(0,3,Voltage_data[][12]); // Cell 2
            //LTC6804_rdcv(3,3,Voltage_data[][12]); //Cell 8
            break;
        case 3: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_3and9, AUX_CH_ALL);
            LTC6804_adcv();
            //LTC6804_rdcv(0,3,Voltage_data[][12]); // Cell 3
            //LTC6804_rdcv(3,3,Voltage_data[][12]); //Cell 9
            break;
        case 4: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_4and10, AUX_CH_ALL);
            LTC6804_adcv();
            //LTC6804_rdcv(2,3,Voltage_data[][12]); // Cell 4
            //LTC6804_rdcv(4,3,Voltage_data[][12]); //Cell 10
            break;
        case 5: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_5and11, AUX_CH_ALL);
            LTC6804_adcv();
            //LTC6804_rdcv(2,3,Voltage_data[][12]); // Cell 5
            //LTC6804_rdcv(4,3,Voltage_data[][12]); //Cell 11
            break;
        case 6: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_6and12, AUX_CH_ALL);
            LTC6804_adcv();
            //LTC6804_rdcv(2,3,Voltage_data[][12]); // Cell 6
            //LTC6804_rdcv(4,3,Voltage_data[][12]); //Cell 12
            break;
        default:
            break;
    }        
}


void Read_GPIO(int BatteryPlacement )
{ switch (BatteryPlacement) {
        case 0: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_ALL);
            LTC6804_adax();
            // What Cells to read,amount of IC,Data
            // LTC6804_rdaux(0,3,Aux_data[][6]); // All GPIO and Ref

            break;
        case 1: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO1);
            LTC6804_adax();
            //LTC6804_rdaux(1,3,Aux_data[][6]);//GPIO 1
            break;
        case 2: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO2);
            LTC6804_adax();
            //LTC6804_rdaux(1,3,Aux_data[][6]);//GPIO 2
            break;
        case 3: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO3);
            LTC6804_adax();
            //LTC6804_rdaux(1,3,Aux_data[][6]);//GPIO 3
            break;
        case 4: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO4);
            LTC6804_adax();
            //LTC6804_rdaux(2,3,Aux_data[][6]);//GPIO 4
            break;
        case 5: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_GPIO5);
            LTC6804_adax();
            //LTC6804_rdaux(2,3,Aux_data[][6]);//GPIO 5
            break;
        case 6: 
            set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_VREF2);
            LTC6804_adax();
            //LTC6804_rdaux(2,3,Aux_data[][6]);//GPIO 6
            break;
        default:
            break;}


}



//Update
void SetBypass(int bank, int ic, int cell, bool value){
	if(value){
		if(cell < 8){
			CFGR4 = CFGR4 | (1 << cell);
		}
		else{
			CFGR5 = CFGR5 | (1 << (cell-8));
		}
	}
	else{
		if(cell < 8){
			CFGR4 = CFGR4 & ~(1 << cell);
		}
		else{
			CFGR5 = CFGR5 & ~(1 << (cell-8));
		}
	}
    LTC6804_DATA[bank][(ic*8)+5] = CFGR4& 0xFF; //First  8 Bits of DCC
    LTC6804_DATA[bank][(ic*8)+4] = (CFGR5) + (DCTO<< 4); // Combined DCTO and the Last 4 bits of DCC
}


//
//int RunBypass(int bank, int ic, bool value)
//{
//    int cellbyp = 0;
//    int i = 0;
//    int voltstat=0; 
//    float batvolt = 0;
//// Want to make a function for all Batterys Right now it works with just 1 IC
//    // Need to understand how he Bank IC and Cell system works 
//    
//    
//    for(i = 0; i<=Cell_Per_Bank;i++)      //<! runs threw num of batteries
//    {
//       // batvolt = Read_Battery(i);    //<! gets battery voltage Not working need to know how to get Read_Battery
//        //voltstat = CheckUnderOverVoltageFlag();
//        if (voltstat==0){
//        if(batvolt>=Bypass_High_Limit)      //<! if bypass needs enabled..
//        {
//           SetBypass(bank,ic,i,1);           //<! sets bypass on
//           cellbyp = 1;
//        }
//        if(batvolt <= Bypass_Low_Limit)     //<! if bypass needs turned off...
//        {
//           SetBypass(bank,ic,i,0);           //<! sets bypass off
//        }
//        }
//    }
//    return cellbyp;
//}




void SetTempEnable(int bank, int ic, bool value){
	if(value){
		CFGR0 = CFGR0 | (1 << 4);
	}
	else{
		CFGR0 = CFGR0 & ~(1 << 4);
	}
	LTC6804_DATA[bank][ic*8] = CFGR0;
}

int CheckUnderOverVoltageFlag(){
return 1;}

//Update Under and over voltages. 
void SetUnderOverVoltage(int VUV, int VOV){
    //LTC6804 - PG: 49 
    CFGR1 = VUV& 0xFF; // Ands with the First 8 bits
    CFGR2 = ((VUV & 0xF00)>> 8)+ ((VOV & 0x0F) <<4); // Finish Last bits of VUV start with VOV
    CFGR3 = (VOV& 0xFF0)>>4;       // Finish VOV setup
    
    for(k = 0;k<NUMBEROFCH;k++){
        for(j=0;j<NUMBEROFIC;j++){
            LTC6804_DATA[k][j*8 + 1] = CFGR1;
            LTC6804_DATA[k][j*8 + 2] = CFGR2;
            LTC6804_DATA[k][j*8 + 3] = CFGR3;
        }
    }
}
//Not Sure how this  LTC6804_DATA works however will copy for consistency 
void Set_ADC_Mode(int bank, int ic, bool ADCOPT_Mode){
    if(ADCOPT_Mode){
    CFGR0= CFGR4 | ADC_MODE_BIT_14k_3k_2k ;
    }
    else {
    CFGR0=CFGR0 & ~ADC_MODE_BIT_14k_3k_2k;   //ADC_MODE_BIT_27k_7k_26
    }
        LTC6804_DATA[bank][ic*8] = CFGR0;
}

//Not Sure how this  LTC6804_DATA works however will copy for consistency 
void Set_REFON_Pin(int bank, int ic, bool REFON_Mode){
    if(REFON_Mode){
    CFGR0= CFGR4 | REFON_TURN_ON ;
    }
    else {
    CFGR0=CFGR0 & ~REFON_TURN_ON;   //REFOFF_TURN_OFF
    }
        LTC6804_DATA[bank][ic*8] = CFGR0;
}
void Get_Stat(int cmd){
   
 // Set_Stat(MD_NORMAL, cmd);
  //LTC6804_ADSTAT();
}
//
void UpdateLT6804(int bank){
  
    //I dont think we need to calculate the PEC becuase that is done in the LTC6804_wrcfg

    //LTC6804_wrcfg(NUMBEROFIC,LTC6804_DATA[bank]);   ERROR Need to Fix
    //LTC6804_wrcfg(3,randomarray[2][6]); //Bullshit code to compile
}

void ReadCurrentVolt(){
    CVolt[0] = ADS1015readADC_SingleEnded(0, 0x01);
    CVolt[1] = ADS1015readADC_SingleEnded(1, 0x01);
    CVolt[2] = ADS1015readADC_SingleEnded(2, 0x01);
    CVolt[3] = ADS1015readADC_SingleEnded(3, 0x01);
    CVolt[4] = ADS1015readADC_SingleEnded(0, 0x02);
    CVolt[5] = ADS1015readADC_SingleEnded(1, 0x02);
}

void ReadVolt(){
    Volt1 = ADS1015readADC_SingleEnded(2, 0x02);
    Volt2 = ADS1015readADC_SingleEnded(3, 0x02);
    Volt1 = (Volt1/ADCBIT)*5*VOLTAGERATIO;
    Volt2 = (Volt2/ADCBIT)*5*VOLTAGERATIO;
}

void ReadVoltToCurrent(){
    ReadCurrentVolt();
    for(k = 0;k<5;k++){
        Current[k] = ((CVolt[k]/ADCBIT)*5/SHUNTOHMS/CURRENTGAIN) + CurrentOffset[k];
    }
}

void ChargerEN(){
    CarOn = 0;
}

void CurrentCoulombCount(int tme){
    if(CarOn){
        CC1 = CC1 - (Current[0]*tme);
        CC2 = CC2 - (Current[2]*tme);
        CC3 = CC3 - (Current[4]*tme);
    }
    else{
        CC1 = CC1 + (Current[1]*tme);
        CC2 = CC2 + (Current[3]*tme);
        CC3 = CC3 + (Current[5]*tme);
    }
}

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