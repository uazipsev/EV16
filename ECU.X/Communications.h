/* 
 * File:   Communications.h
 * Author: User
 *
 * Created on May 31, 2015, 3:26 PM
 */

#ifndef COMMUNICATIONS_H
#define	COMMUNICATIONS_H

#define PDUSTATE 1
#define MCSSTATE 2
#define SASSTATE 3
#define DDSSTATE 4
#define BMMSTATE 5
    //COMMUNICATIONS METHODS
    extern void updateComms();


    void checkCommDirection();
    void bus1Update();
    void resetCommTimers();
    void RS485_Direction1(int T_L);
    void sendErrorCode();


    void checkCommDirection1();
    void bus2Update();
    void resetCommTimers2();
    void RS485_Direction2(int T_L);
    void sendErrorCode2();
    bool ComCheck(char device);

    //
    extern bool requestMCSData();
    extern bool receiveCommMCS();
    extern bool readyToSendMCS;
    extern bool MCS_COMMS_ERROR;
    //

    extern bool requestPDUData();
    extern bool receiveCommPDU();
    extern bool readyToSendPDU;
    extern bool PDU_COMMS_ERROR;
    //HORN METHOD
    extern void RTD(int lenth);

    //FAST TRANSFER / UART STUFF
    extern void sendData(unsigned char whereToSend);
    extern bool receiveData();
    extern void ToSend(const unsigned char where, const unsigned int what);
    extern volatile int receiveArray[100];
    extern volatile bool Transmit_stall;
    extern volatile unsigned int talkTime;

    extern void sendData1(unsigned char whereToSend);
    extern bool receiveData1();
    extern void ToSend1(const unsigned char where, const unsigned int what);
    extern volatile int receiveArray1[20];
    extern volatile bool Transmit_stall1;
    extern volatile unsigned int talkTime1;

    extern void sendData2(unsigned char whereToSend);
    extern bool receiveData2();
    extern void ToSend2(const unsigned char where, const unsigned int what);
    extern volatile int receiveArray2[20];
    extern volatile bool Transmit_stall2;
    extern volatile unsigned int talkTime2;

    extern void sendData3(unsigned char whereToSend);
    extern bool receiveData3();
    extern void ToSend3(const unsigned char where, const unsigned int what);
    extern volatile int receiveArray3[20];
    extern volatile bool Transmit_stall3;
    extern volatile unsigned int talkTime3;

#endif	/* COMMUNICATIONS_H */

