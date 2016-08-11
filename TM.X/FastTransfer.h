/* 
 * File:   FastTransfer.h
 * Author: Igor
 * Revised May 28, 2015 Zac Kilburn
 * Created on March 23, 2015, 1:21 PM
 */

#ifndef FASTTRANSFER_H
#define	FASTTRANSFER_H

#define RX_BUFFER_SIZE 100
//the capital D is so there is no interference with the lower case d of EasyTransfer
#define Details(name) (int*)&name,sizeof(name)

void begin(volatile int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void), int (*stuffavailable)(void), unsigned char (*stuffpeek)(void));
void sendData(unsigned char whereToSend);
bool receiveData(void);
void ToSend(const unsigned char where, const unsigned int what);
unsigned char AKNAK(unsigned char module);
unsigned int alignError(void);
unsigned int CRCError(void);
unsigned int addressError(void);
unsigned int dataAddressError(void);

#endif	/* FASTTRANSFER_H */

