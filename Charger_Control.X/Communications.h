/* 
 * File:   Communications.h
 * Author: User
 *
 * Created on May 31, 2015, 8:32 PM
 */

#ifndef COMMUNICATIONS_H
#define	COMMUNICATIONS_H

    extern volatile int receiveArray[20];
    void updateComms();
    extern void sendData(unsigned char whereToSend);
    extern bool receiveData();
    extern void ToSend(const unsigned char where, const unsigned int what);
    void respondChargerAsECU();
    bool SetBMM();

#endif	/* COMMUNICATIONS_H */

