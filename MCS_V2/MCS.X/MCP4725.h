/* 
 * File:   MCP4725.h
 * Author: Rick
 *
 * Created on May 20, 2015, 1:12 AM
 */

#ifndef MCP4725_H
#define	MCP4725_H

#define DAC1Address 0x61
#define DAC2Address 0x60

void SetDAC1(unsigned int value);
void SetDAC2(unsigned int value);

#endif	/* MCP4725_H */

