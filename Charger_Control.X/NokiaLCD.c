/*******************************************************************
 * @brief           NokiaLCD.c
 * @brief           Adds easy to use functions to the Nokia LCD
 * @return          EU
 * @note            The lib is written for Nokia 5110 (https://learn.adafruit.com/downloads/pdf/nokia-5110-3310-monochrome-lcd.pdf)
 *******************************************************************/

#include "NokiaLCD.h"
#include "Functions.h"
#include "mcc_generated_files/spi1.h"
#include "mcc_generated_files/mcc.h"

/*******************************************************************
 * @brief           NokiaStart
 * @brief           Set's up the LCD 
 * @return          none
 * @note            
 *******************************************************************/

void NokiaStart(){
    LCD_CS_SetDigitalOutput();
    LCD_DC_SetDigitalOutput();
    LCD_RES_SetDigitalOutput();
    SPI1_Initialize();
    LCD_RES_SetHigh();
    Delay(100);
    LCD_RES_SetLow();
    Delay(100);
    LCD_RES_SetHigh();
    LCD_DC_SetLow();
    LCD_CS_SetLow();
    SPI1_Exchange8bit(0x21);
    SPI1_Exchange8bit(0xC8);
    SPI1_Exchange8bit(0x06);
    SPI1_Exchange8bit(0x13);
    SPI1_Exchange8bit(0x20);
    SPI1_Exchange8bit(0x0C);
    LCD_CS_SetHigh();
    clearLcd();
    blackLcd();
}

/*******************************************************************
 * @brief           clearLcd
 * @brief           This may clear the LCD display..I don't know...
 * @return          none
 * @note            
 *******************************************************************/

void clearLcd(){
    int res;
    LCD_CS_SetLow(); 
    LCD_DC_SetHigh();
    for(res=0;res<504;res++){
        SPI1_Exchange8bit(0x00);
    }
    LCD_CS_SetHigh();
    
}

/*******************************************************************
 * @brief           blackLCD
 * @brief           I have no clue what this does..really....
 * @return          none
 * @note            
 *******************************************************************/

void blackLcd(){
    int res;
    LCD_CS_SetLow();
    LCD_DC_SetHigh();
    for(res=0;res<504;res++){
        SPI1_Exchange8bit(0xFF);
    }
    LCD_CS_SetHigh();
}

/*******************************************************************
 * @brief           gotoXy
 * @brief           go to pixel for format 
 * @return          none
 * @note            
 *******************************************************************/

void gotoXy(unsigned char x,unsigned char y){
    LCD_CS_SetLow();
    LCD_DC_SetLow();
    y=y|0x40;
    SPI1_Exchange8bit(y);
    x=(x*6)|0x80;
    SPI1_Exchange8bit(x);
    LCD_CS_SetHigh();
}

/*******************************************************************
 * @brief           NokiaStr
 * @brief           This allows us to print text on the display
 * @return          none
 * @note            
 *******************************************************************/

void NokiaStr( char *str,unsigned char len){
    int i;
    LCD_CS_SetLow();
    LCD_DC_SetHigh();
    for(;len>0;len --){
        for(i=0;i<=4;i++){
            SPI1_Exchange8bit(FONTLOOKUP[*str-32][i]);
            SPI1_Exchange8bit(0x00);
            str++;
        }
    }
    LCD_CS_SetHigh();
}