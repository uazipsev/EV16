/*
 * File:   PDU.c
 * Author: Richard Johnson
 *
 * Created on May 27, 2015, 7:46 PM
 *
 * This will control the mosfet drivers and run them like a PDU
 */
#include "PDU.h"
#include "Shift595.h"
#include <stdio.h>
#include "mcc_generated_files/pin_manager.h" 
#include "mcc_generated_files/adc.h"
#include "mcc_generated_files/memory.h"

bool MCSOn = 0;

void PDUStartup(void) {
    //We are assuming the car just started up.
    //Lets shut down all outputs untill told otherwise
    StartUp595();
    //now enable SAS and DDS
    EnableSlavePower(SAS, OFF);
    EnableSlavePower(DDS, OFF);
    EnableSlavePower(MCS, OFF);
    EnableSlavePower(BMM, OFF);
    EnableSlavePower(TSS, OFF);
    Update();
    //Lets pull Prev values out of memory for control
    ComputeStorageData();
}

//sets the 9v outputs as requested

void EnableSlavePower(device slave, int onof) {
    switch (slave) {
        case SAS:
            SetPin595(2, 6, onof);
            break;
        case BMM:
            SetPin595(1, 1, onof);
            break;
        case MCS:
            SetPin595(1, 6, onof);
            MCSOn = onof;
            break;
        case DDS:
            SetPin595(2, 1, onof);
            break;
        case TSS:
            SetPin595(3, 6, onof);
            break;
        case AUX:
            SetPin595(3, 1, onof);
            break;
    }
}

//sets up to read the current from the different mosfet drivers

void ReadCurrent(char gather) {
    if (gather == 1) {
        //read the first three
        SetPin595(1, 4, ON);
        SetPin595(1, 3, OFF);
        SetPin595(1, 2, OFF);
        SetPin595(2, 4, OFF);
        SetPin595(2, 3, OFF);
        SetPin595(2, 2, OFF);
        SetPin595(3, 4, OFF);
        SetPin595(3, 3, OFF);
        SetPin595(3, 2, OFF);
        Update();
        //CurrentADC[0] = ADC_GetConversion(U5Multisense);
        //CurrentADC[2] = ADC_GetConversion(U8Multisense);
        CurrentADC[5] = ADC_GetConversion(U10Multisense);
    } 
    else if(gather == 2){
        //read the second three
        SetPin595(1, 4, OFF);
        SetPin595(1, 3, OFF);
        SetPin595(1, 2, OFF);
        SetPin595(2, 4, ON);
        SetPin595(2, 3, OFF);
        SetPin595(2, 2, OFF);
        SetPin595(3, 4, OFF);
        SetPin595(3, 3, OFF);
        SetPin595(3, 2, OFF);
        Update();
        //CurrentADC[1] = ADC_GetConversion(U5Multisense);
        CurrentADC[3] = ADC_GetConversion(U8Multisense);
        //CurrentADC[5] = ADC_GetConversion(U10Multisense);
    }
    else if(gather == 3){
            //read the second three
        SetPin595(1, 4, OFF);
        SetPin595(1, 3, OFF);
        SetPin595(1, 2, OFF);
        SetPin595(2, 4, OFF);
        SetPin595(2, 3, OFF);
        SetPin595(2, 2, OFF);
        SetPin595(3, 4, ON);
        SetPin595(3, 3, OFF);
        SetPin595(3, 2, OFF);
        Update();
        CurrentADC[1] = ADC_GetConversion(U5Multisense);
        //CurrentADC[3] = ADC_GetConversion(U8Multisense);
        //CurrentADC[5] = ADC_GetConversion(U10Multisense);
    }
    else if(gather == 4){
            //read the second three
        SetPin595(1, 4, ON);
        SetPin595(1, 3, ON);
        SetPin595(1, 2, OFF);
        SetPin595(2, 4, OFF);
        SetPin595(2, 3, OFF);
        SetPin595(2, 2, OFF);
        SetPin595(3, 4, OFF);
        SetPin595(3, 3, OFF);
        SetPin595(3, 2, OFF);
        Update();
        //CurrentADC[1] = ADC_GetConversion(U5Multisense);
        //CurrentADC[3] = ADC_GetConversion(U8Multisense);
        CurrentADC[4] = ADC_GetConversion(U10Multisense);
    }
    else if(gather == 5){
            //read the second three
        SetPin595(1, 4, OFF);
        SetPin595(1, 3, OFF);
        SetPin595(1, 2, OFF);
        SetPin595(2, 4, ON);
        SetPin595(2, 3, ON);
        SetPin595(2, 2, OFF);
        SetPin595(3, 4, OFF);
        SetPin595(3, 3, OFF);
        SetPin595(3, 2, OFF);
        Update();
        //CurrentADC[1] = ADC_GetConversion(U5Multisense);
        CurrentADC[4] = ADC_GetConversion(U8Multisense);
        //CurrentADC[5] = ADC_GetConversion(U10Multisense);
    }
    else if(gather == 6){
            //read the second three
        SetPin595(1, 4, OFF);
        SetPin595(1, 3, OFF);
        SetPin595(1, 2, OFF);
        SetPin595(2, 4, OFF);
        SetPin595(2, 3, OFF);
        SetPin595(2, 2, OFF);
        SetPin595(3, 4, ON);
        SetPin595(3, 3, ON);
        SetPin595(3, 2, OFF);
        Update();
        CurrentADC[0] = ADC_GetConversion(U5Multisense);
        //CurrentADC[3] = ADC_GetConversion(U8Multisense);
        //CurrentADC[5] = ADC_GetConversion(U10Multisense);
    }
    
}


//pulling data out of EEPROM and getting ready to use it for our "fuse" code

void ComputeStorageData(void) {
    for (int i = 0; i < NUMOFBYTES; i++) {
        data[i] = DATAEE_ReadByte(i);
    }
    Currentcomp[0] = ((data[0] << 8) | data[1]);
    Currentcomp[1] = ((data[2] << 8) | data[3]);
    Currentcomp[2] = ((data[4] << 8) | data[5]);
    Currentcomp[3] = ((data[6] << 8) | data[7]);
    Currentcomp[4] = ((data[8] << 8) | data[9]);
    Currentcomp[5] = ((data[10] << 8) | data[11]);

}

//This is our software "fuse" code to shut off outputs when under stress

void FuseSystem() {
    printf("Reading Stuff \n");
    for (int i = 0; i < 6; i++) {
        Current[i] = CurrentADC[i]*48; //all numbers at this point are mult by 10000
        printf("%u ",Current[i]);
        //So to get real numbers divide by 10000
    }
    printf("\n");
    for (int i = 0; i < 6; i++) {
        if (Current[i] > Currentcomp[i]) {
            //over current condition
            LED1_SetHigh();
            switch(i){
                case 0:
                    EnableSlavePower(AUX, 0);
                    break;
                case 1:
                    EnableSlavePower(TSS, 0);
                    break;
                case 2:
                    EnableSlavePower(SAS, 0);
                    break;
                case 3:
                    EnableSlavePower(DDS, 0);
                    break;
                case 4:
                    EnableSlavePower(BMM, 0);
                    break;
                case 5:
                    EnableSlavePower(MCS, 0);
                    break;
            }
        }
    }
}

void Update(void) {
    writeRegisters();
}

bool CoolingCheck(){
    return MCSOn;
}