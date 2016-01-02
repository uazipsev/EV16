#include "ADC.h"
#include "I2C.h"
#define READ_AN0 0x00
#define READ_AN1 0x00
#define READ_AN2 0x00
#define READ_AN3 0x00
#define CONFIG_AN0 0x4483
#define CONFIG_AN1 0x5483
#define CONFIG_AN2 0x6483
#define CONFIG_AN3 0x7483

#define ADS1015_ADDR 0b1001000



int readADC(int inputNum){
    char d[3];
    int returnable;
    char reading[2];
    switch(inputNum){
        case 0:
            //Read the I2C
            d[0]=READ_AN0;
            i2c_Write(ADS1015_ADDR, 1, d, 1);
            i2c_Write(ADS1015_ADDR, 0, reading, 2);
            //Make 2x (8bits) -> 16Bits
            returnable=(reading[0]&0x00FF) << 8;
            returnable=returnable|(reading[1]&0x00FF);
            returnable=(returnable&0x0FFF)>>4;
            //Setup ADC for Next Channel
            d[0]=0x01;
            d[1]=(CONFIG_AN1&0xFF00)>>8;
            d[2]=(CONFIG_AN1&0x00FF)>>0;
            i2c_Write(ADS1015_ADDR, 1, d, 3);
            break;
        case 1:
            //Read the I2C
            d[0]=READ_AN1;
            i2c_Write(ADS1015_ADDR, 1, d, 1);
            i2c_Write(ADS1015_ADDR, 0, reading, 2);
            //Make 2x (8bits) -> 16Bits
            returnable=(reading[0]&0x00FF) << 8;
            returnable=returnable|(reading[1]&0x00FF);
            returnable=(returnable&0x0FFF)>>4;
            //Setup ADC for Next Channel
            d[0]=0x01;
            d[1]=(CONFIG_AN2&0xFF00)>>8;
            d[2]=(CONFIG_AN2&0x00FF)>>0;
            i2c_Write(ADS1015_ADDR, 1, d, 3);
            break;
        case 2:
            //Read the I2C
            d[0]=READ_AN2;
            i2c_Write(ADS1015_ADDR, 1, d, 1);
            i2c_Write(ADS1015_ADDR, 0, reading, 2);
            //Make 2x (8bits) -> 16Bits
            returnable=(reading[0]&0x00FF) << 8;
            returnable=returnable|(reading[1]&0x00FF);
            returnable=(returnable&0x0FFF)>>4;
            //Setup ADC for Next Channel
            d[0]=0x01;
            d[1]=(CONFIG_AN3&0xFF00)>>8;
            d[2]=(CONFIG_AN3&0x00FF)>>0;
            i2c_Write(ADS1015_ADDR, 1, d, 3);
            break;
        case 3:
            //Read the I2C
            d[0]=READ_AN3;
            i2c_Write(ADS1015_ADDR, 1, d, 1);
            i2c_Write(ADS1015_ADDR, 0, reading, 2);
            //Make 2x (8bits) -> 16Bits
            returnable=(reading[0]&0x00FF) << 8;
            returnable=returnable|(reading[1]&0x00FF);
            returnable=(returnable&0x0FFF)>>4;
            //Setup ADC for Next Channel
            d[0]=0x01;
            d[1]=(CONFIG_AN0&0xFF00)>>8;
            d[2]=(CONFIG_AN0&0x00FF)>>0;
            i2c_Write(ADS1015_ADDR, 1, d, 3);
            break;
            
        
    }
    returnable=(int)((3300.0/4095.0)*returnable);
    return returnable;
}