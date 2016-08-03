/* 
 * File:   Communications.h
 * Author: User
 *
 * Created on May 31, 2015, 8:32 PM
 */

#ifndef COMMUNICATIONS_H
#define	COMMUNICATIONS_H

#define RS485_Port LATDbits.LATD4
#define TALK 1
#define LISTEN 0

    void CommsStart();
    void updateComms();
    extern void sendData(unsigned char whereToSend);
    extern bool receiveData();
    extern void ToSend(const unsigned char where, const unsigned int what);
    void respondChargerAsECU();
    bool SetBMM();

#endif	/* COMMUNICATIONS_H */

