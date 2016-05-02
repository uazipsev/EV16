/*******************************************************************
 * @brief           NokiaLCD.c
 * @brief           Adds easy to use functions to the Nokia LCD
 * @return          EU
 * @note            The lib is written for Nokia 5110 (https://learn.adafruit.com/downloads/pdf/nokia-5110-3310-monochrome-lcd.pdf)
 *******************************************************************/
#include <stdbool.h>
#include "NokiaLCD.h"
#include "Functions.h"
#include "mcc_generated_files/spi1.h"
#include "mcc_generated_files/mcc.h"


#define LCD_CMD 0
#define LCD_DAT 1

/*******************************************************************
 * @brief           NokiaStart
 * @brief           Set's up the LCD 
 * @return          none
 * @note            
 *******************************************************************/

void NokiaStart(){
    TRISBbits.TRISB6 = 0;
    LCD_CS_SetDigitalOutput();
    LCD_DC_SetDigitalOutput();
    LCD_RES_SetDigitalOutput();
    LCD_CS_SetHigh();
    SPI1_Initialize();
    LATBbits.LATB6 = 1;
    Delay(100);
    LATBbits.LATB6 = 0;
    Delay(100);
    LATBbits.LATB6 = 1;
    LCDwrite(LCD_CMD, 0x21);
    LCDwrite(LCD_CMD, 0xBF);
    LCDwrite(LCD_CMD, 0x04);
    LCDwrite(LCD_CMD, 0x14);
    LCDwrite(LCD_CMD, 0x0C);
    LCDwrite(LCD_CMD, 0x20);
    LCDwrite(LCD_CMD, 0x0C);
    clearLcd();
    blackLcd();
}

void LCDwrite(bool mode, char data){
    if(mode){
        LCD_DC_SetLow();  // LCD command
    }
    else{
        LCD_DC_SetHigh(); // LCD Data
    }
    LCD_CS_SetLow();
    SPI1_Exchange8bit(data);
    LCD_CS_SetHigh();
}

/*******************************************************************
 * @brief           clearLcd
 * @brief           This may clear the LCD display..I don't know...
 * @return          none
 * @note            
 *******************************************************************/

void clearLcd(){
    int res;
    for(res=0;res<504;res++){
        LCDwrite(LCD_DAT, 0x00);
    }
    
}

/*******************************************************************
 * @brief           blackLCD
 * @brief           I have no clue what this does..really....
 * @return          none
 * @note            
 *******************************************************************/

void blackLcd(){
    int res;
    for(res=0;res<504;res++){
        LCDwrite(LCD_DAT, res);
    }
}

/*******************************************************************
 * @brief           gotoXy
 * @brief           go to pixel for format 
 * @return          none
 * @note            
 *******************************************************************/

void gotoXy(unsigned char x,unsigned char y){
    y=y|0x40;
    LCDwrite(LCD_CMD, y);
    x=(x*6)|0x80;
    LCDwrite(LCD_CMD, x);
}

/*******************************************************************
 * @brief           NokiaStr
 * @brief           This allows us to print text on the display
 * @return          none
 * @note            
 *******************************************************************/

void NokiaStr( char *str,unsigned char len){
    int i;
    for(;len>0;len --){
        for(i=0;i<=4;i++){
            LCDwrite(LCD_DAT,(FONTLOOKUP[*str-32][i]));
            LCDwrite(LCD_DAT,(0x00));
            str++;
        }
    }
}