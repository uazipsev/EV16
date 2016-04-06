/* 
 * File:   I2C_API.h
 * Author: Rick
 *
 * Created on December 14, 2014, 8:04 PM
 */

#ifndef I2C_API_H
#define	I2C_API_H

#define MAX_RETRY	 1000
#define ONE_BYTE     1
#define TWO_BYTE     2

// EEPROM ADDRESS SIZE
#define ADDRWIDTH   ONE_BYTE     
  
// EEPROM DRIVER COMMAND DEFINITION
#define I2C_IDLE 		 0  
#define I2C_WRITE        1      
#define I2C_READ         2    
#define I2C_ERR        0xFFFF

// EEPROM DATA OBJECT
typedef struct { 
        unsigned int *buff;      
        unsigned int n;        
        unsigned int addr;       
        unsigned int csel;            
}I2CEMEM_DATA; 

// EEPROM DRIVER OBJECT
typedef struct { 
        unsigned int	cmd; 
		I2CEMEM_DATA	*oData;	        
        void (*init)(void *);                   
        void (*tick)(void *); 
        }I2CEMEM_DRV; 
    
#define I2CSEMEM_DRV_DEFAULTS { 0,\
        (I2CEMEM_DATA *)0,\
        (void (*)(void *))I2CEMEMinit,\
        (void (*)(void *))I2CEMEMdrv}  
        

void I2CEMEMinit(I2CEMEM_DRV *); 
void I2CEMEMdrv(I2CEMEM_DRV *);


#endif	/* I2C_API_H */

