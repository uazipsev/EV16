/* 
 * File:   I2C_API.h
 * Author: Rick
 *
 * Created on December 14, 2014, 8:04 PM
 */

#ifndef I2C_API_H
#define	I2C_API_H

unsigned int IdleI2C(void);
unsigned int StartI2C(void);
unsigned int WriteI2C(unsigned char);
unsigned int StopI2C(void);
unsigned int RestartI2C(void);
unsigned int getsI2C(unsigned char*, unsigned char);
unsigned int NotAckI2C(void);
unsigned int InitI2C(void);
unsigned int ACKStatus(void);
unsigned int getI2C(void);
void AckI2C(void);
unsigned int EEAckPolling(unsigned char);
unsigned int putstringI2C(unsigned char*);

#endif	/* I2C_API_H */

