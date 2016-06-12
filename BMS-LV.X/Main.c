/**
*********************************************************************************************************
*
* @brief        BMS - This device reads in voltages and temps. It controls bypass and sends data over RS485
* @file         main.c
* @author       Richard Johnson
* @moduleID
* @ingroup
*
*********************************************************************************************************
* @note  The Firmware shall:
*               -Read in battery voltags (B1-B10)
*               -Read in Temp voltags (T1-T2)
*               -Set LED indicator
*               -Set Bypass (C1-C10)
*               -Read RS485 BUS for data and reply with expectied data
*********************************************************************************************************
 */

#include "mcc_generated_files/mcc.h"
#include "BatteryManagment.h"
#include <stdio.h>
#include <stdlib.h>
#include "Functions.h"
#include "Tempeture.h"



char fault[3] = 0;
char fault_flag = 0;
char infault = 0;

int main(int argc, char** argv) {
    // Initialize the device
    SYSTEM_Initialize();
    SET_SetHigh();
    Delay(120);
    SET_SetLow();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowEnable();

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    //int ADCNT = 0;
    //INDICATOR_SetHigh();
    LATCbits.LATC5 =1;
    printf("BOOT");
  // Start_BMS();
     //*IC=54;
    while (1)
    {
      // Run_Mode();
     
    }
    return (EXIT_SUCCESS);
}


