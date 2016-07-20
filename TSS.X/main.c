
/**
 *********************************************************************************************************
 *
 * @brief        TS - This device reads in sensors and converts them to EU 
 * @file         main.c
 * @author       Richard Johnson - Joey
 * @moduleID
 * @ingroup
 *
 *********************************************************************************************************
 * @note  The Firmware shall:
 *               -Read in IMU and convert to EU
 *               -Read in roter temp 
 *               -Wheel speed
 *               -Read RS485 BUS for data and reply with expectied data (set requested LED states and rely with button states)
 *********************************************************************************************************

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <stdlib.h>
#include "IO.h"
#include "Communications.h"
#include "CarTempSens.h"

/*******************************************************************
 * @brief           Main
 * @brief           The main fcn of the code
 * @return          None
 * @note            The main loop is here
 *******************************************************************/

void main(void) {
    // Initialize the device
    SYSTEM_Initialize();

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
    LATCbits.LATC5 = 0; //Sets pin C5 to zero 
    while (1) {
        updateComms(); // This is for the RS485 communication. 
        TempCalc(1);   //Gets ADC vales and convert them
        TempCalc(2);
        TempGet(1);    // Gets EU
        TempGet(2);
    }
}


/**
 End of File 
 
 */