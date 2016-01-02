/* 
 * File:   SlaveCommunications.h
 * Author: User
 *
 * Created on June 10, 2015, 9:44 PM
 */

#ifndef SLAVECOMMUNICATIONS_H
#define	SLAVECOMMUNICATIONS_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "ADDRESSING.h"
#include "SlaveAddressing.h"
#include <stdbool.h>
#include <xc.h>
#define RS485_SLAVE_Port LATAbits.LATA7
#define RS485_SLAVE_Port1 LATAbits.LATA4 
    extern void checkSlaveCommDirection();
    extern bool Transmit_stall1;
    extern void sendData1(unsigned char whereToSend);
    extern bool receiveData1();
    extern void ToSend1(const unsigned char where, const unsigned int what);
    extern volatile int receiveArray1[100];

    extern void updateSlaveCommunications();

    extern volatile unsigned long int slaveTime;
    extern void sendSlavePacket(int slave);
    extern int BVolts[NUMSLAVES][BATTPERSLAVE];
    extern int BTemps[NUMSLAVES][TEMPPERSLAVE];
    extern int faultCount[NUMSLAVES];
    extern int faultFlag;
#define TALK 1
#define LISTEN 0


#ifdef	__cplusplus
}
#endif

#endif	/* SLAVECOMMUNICATIONS_H */

