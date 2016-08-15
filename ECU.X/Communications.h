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
void updateComms();
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

#endif	/* COMMUNICATIONS_H */

