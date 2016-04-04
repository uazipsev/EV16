
#include "BatteryManagment.h"

//|r_config[0]|r_config[1]|r_config[2]|r_config[3]|r_config[4]|r_config[5]|r_config[6]  |r_config[7] |r_config[8]|r_config[9]|  .....    |
//|-----------|-----------|-----------|-----------|-----------|-----------|-------------|------------|-----------|-----------|-----------|
//|IC1 CFGR0  |IC1 CFGR1  |IC1 CFGR2  |IC1 CFGR3  |IC1 CFGR4  |IC1 CFGR5  |IC1 PEC High |IC1 PEC Low |IC2 CFGR0  |IC2 CFGR1  |  .....    |


void Start_LTC6804_initialize() {
    LTC6804_initialize();
}

void Read_Battery(int BatteryPlacement) {

    switch (BatteryPlacement) {
        case 0: set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_ALL, AUX_CH_ALL);
            LTC6804_adcv();
            break;
        case 1: set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_1and7, AUX_CH_ALL);
            LTC6804_adcv();
            break;
        case 2: set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_2and8, AUX_CH_ALL);
            LTC6804_adcv();
            break;
        case 3: set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_3and9, AUX_CH_ALL);
            LTC6804_adcv();
            break;
        case 4: set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_4and10, AUX_CH_ALL);
            LTC6804_adcv();
            break;
        case 5: set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_5and11, AUX_CH_ALL);
            LTC6804_adcv();
            break;
        case 6: set_adc(MD_NORMAL, DCP_DISABLED, CELL_CH_6and12, AUX_CH_ALL);
            LTC6804_adcv();
            break;
        default:
            break;
    }
                
            
}

void SetBypass(int bank, int ic, int cell, bool value){
	if(value){
		if(cell < 8){
			CFGR4 = CFGR4 | (1 << cell);
		}
		else(){
			CFGR5 = CFGR5 | (1 << (cell-8));
		}
	}
	else(){
		if(cell < 8){
			CFGR4 = CFGR4 & ~(1 << cell);
		}
		else(){
			CFGR5 = CFGR5 & ~(1 << (cell-8));
		}
	}
	LTC6804_DATA[bank][ic][5] = CFGR5;
	LTC6804_DATA[bank][ic][4] = CFGR4;
}

void SetTempEnable(int bank, int ic, bool value){
	if(value){
		CFGR0 = CFGR0 | (1 << 4);
	}
	else(){
		CFGR0 = CFGR0 & ~(1 << 4);
	}
	LTC6804_DATA[bank][ic][0] = CFGR0;
}

void SetUnderOverVoltage(int under, int over){
	int uv[2];
	int ov[2]0;
	
	uv[0] = ((under >> 0) & 0xff);
	uv[1] = ((under >> 8) & 0xff);
	
	ov[0] = ((over >> 12) & 0xff);
	ov[1] = ((over >> 4) & 0xff);
	
	CFGR1 = uv[0];
	CFGR2 = uv[1];
}