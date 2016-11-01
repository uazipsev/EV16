/* 
 * File:   PDU.h
 * Author: Richard Johnson
 *
 * Created on May 27, 2015, 7:46 PM
 */

#ifndef PDU_H
#define	PDU_H

#include <stdbool.h>

#define NUMOFBYTES 12  //8-1

unsigned int Currentcomp[6] = 0;
char data[NUMOFBYTES] = 0;
unsigned int CurrentADC[6] = 0;
unsigned int Current[6] = 0;

typedef enum {
    DDS = 1,
    MCS = 2,
    SAS = 3,
    BMM = 4,
    TSS = 5,
    AUX = 6,
    ON = 1,
    OFF = 0
} device;

extern void PDUStartup(void);
void EnableSlavePower(device slave, int onof);
void FuseSystem();
void ComputeStorageData(void);
void ReadCurrent(char gather);
void Update(void);
bool CoolingCheck();
void SavePDUFault(char loc, bool data);
bool GetPDUFault(char loc);
unsigned int FaultsCollector();
#endif	/* PDU_H */

