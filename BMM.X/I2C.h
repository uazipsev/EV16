/* 
 * File:   I2C_API.h
 * Author: Rick
 *
 * Created on December 14, 2014, 8:04 PM
 */

#ifndef I2C_API_H
#define	I2C_API_H

#include <stdbool.h>

void IdleI2C(void);
void StartI2C(void);
void WriteI2C(unsigned char);
char StopI2C(void);
void RestartI2C(void);
char getsI2C(char*, unsigned char);
void NotAckI2C(void);
void InitI2C(void);
char ACKStatus(void);
char getI2C(void);
void AckI2C(void);
unsigned int EEAckPolling(unsigned char);
unsigned int putstringI2C(unsigned char*);
void i2c_Write(char address, bool read_write, char *data, int numofbytes);

#endif	/* I2C_API_H */

