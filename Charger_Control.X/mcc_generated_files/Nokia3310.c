#include "Nokia3310.h"
#include "../mcc_generated_files/spi2.h"
#include "../mcc_generated_files/mcc.h"


void NokiaStart(){
    LCD_DC_SetLow();
    LCD_CS_SetLow();
    SPI2_Exchange8bit(0x21);
    SPI2_Exchange8bit(0xC8);
    SPI2_Exchange8bit(0x06);
    SPI2_Exchange8bit(0x13);
    SPI2_Exchange8bit(0x20);
    SPI2_Exchange8bit(0x0C);
    clearLcd();
    blackLcd();
}


void clearLcd(){
    int res;
    LCD_CS_SetLow(); 
    LCD_DC_SetHigh();
    for(res=0;res<504;res++){
        SPI2_Exchange8bit(0x00);
    }
}
void blackLcd(){
    int res;
    LCD_CS_SetLow();
    LCD_DC_SetHigh();
    for(res=0;res<504;res++){
        SPI2_Exchange8bit(0xFF);
    }
}

void gotoXy(unsigned char x,unsigned char y){
    LCD_DC_SetLow();
    y=y|0x40;
    SPI2_Exchange8bit(y);
    x=(x*6)|0x80;
    SPI2_Exchange8bit(x);
    LCD_DC_SetHigh();
}

void NokiaStr( char *str,unsigned char len){
    int i;
    LCD_DC_SetHigh();
    for(;len>0;len --){
        for(i=0;i<=4;i++){
            SPI2_Exchange8bit(FONTLOOKUP[*str-32][i]);
            SPI2_Exchange8bit(0x00);
            str++;
        }
    }
}