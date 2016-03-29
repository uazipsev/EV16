
#include "BatteryManagment.h"

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