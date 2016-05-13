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


#define LCD_CMD 1
#define LCD_DAT 0

/*******************************************************************
 * @brief           NokiaStart
 * @brief           Set's up the LCD 
 * @return          none
 * @note            
 *******************************************************************/
#define LCD_START_LINE_ADDR	(66-2)

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
    LCDwrite(LCD_CMD, 0xC8); //C8 was B1, B1 made the text bolder
    LCDwrite(LCD_CMD, 0x04 | !!(LCD_START_LINE_ADDR & (1u << 6)));
    LCDwrite(LCD_CMD, 0x40 | (LCD_START_LINE_ADDR & ((1u << 6) - 1)));
    //LCDwrite(LCD_CMD, 0x06);
    LCDwrite(LCD_CMD, 0x14);
    LCDwrite(LCD_CMD, 0x20);
    LCDwrite(LCD_CMD, 0x08);
    LCDwrite(LCD_CMD, 0x0C);
    clearLcd();
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
 * @note            Max X = 0-5 Max Y = 0-14 
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

void LcdCharacter(char character)
{
  LCDwrite(LCD_DAT, 0x00);
  for (int index = 0; index < 5; index++)
  {
    LCDwrite(LCD_DAT, FONTLOOKUP[character - 0x20][index]);
  }
  LCDwrite(LCD_DAT, 0x00);
}

/*******************************************************************
 * @brief           NokiaStr
 * @brief           This allows us to print text on the display
 * @return          none
 * @note            
 *******************************************************************/

void NokiaStr( char *str){
  while (*str)
  {
    LcdCharacter(*str++);
  }
}


/*******************************************************************
 * @brief           Splash
 * @brief           This fcn makes a splash screen on the LCD 
 * @return          none
 * @note            My little toy :) 
 *******************************************************************/

void Splash(){
    gotoXy(0,2);
    NokiaStr("Charger Control");
    gotoXy(1,4);
    NokiaStr("Waiting on BMM");
}

