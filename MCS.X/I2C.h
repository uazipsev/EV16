/* 
 * File:   I2C_API.h
 * Author: Igor
 *
 * Created on December 14, 2014, 8:04 PM
 */

#ifndef I2C_API_H
#define	I2C_API_H

#include <stdbool.h>

void i2c_Write(char address, bool read_write, char *data, int numofbytes);
void i2c_wait(unsigned int cnt);
void I2c_Init(void);
void i2cUpdate();

#endif	/* I2C_API_H */

