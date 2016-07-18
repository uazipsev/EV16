/* 
 * File:   EEprom.h
 * Author: Rick
 *
 * Created on July 18, 2016, 1:32 AM
 */

#ifndef EEPROM_H
#define	EEPROM_H

void EEpromInit();
void DataWrite(char address, char data);
char DataRead(char address);
int readRegister(char i2cAddress, char reg);
void writeRegister(char i2cAddress, char reg, int value);

#endif	/* EEPROM_H */

