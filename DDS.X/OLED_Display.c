#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "mcc_generated_files/i2c1.h"
#include <string.h>

#include "OLED_Display.h"
#include "OLED_Display_P.h"

void OLED_command(char com)
{
   Buff[0] = 0x80;// 0x80;
   //StartI2C ();
   Buff[1] = com;
   I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;

    timeOut = 0;
    while (status != I2C1_MESSAGE_FAIL) {
        // write one byte to EEPROM (3 is the number of bytes to write)
        I2C1_MasterWrite(Buff,
                2,
                OLED,
                &status);

        // wait for the message to be sent or status has changed.
        while (status == I2C1_MESSAGE_PENDING);

        if (status == I2C1_MESSAGE_COMPLETE)
            break;
        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
            break;
        if (status == I2C1_MESSAGE_FAIL)
            break;
        else
            timeOut++;
    }
}

void oledGotoYX(unsigned char Row, unsigned char Column)
{
    OLED_command( 0xB0 + Row);
    OLED_command( 0xB0 + Row);
    OLED_command( 0x00 + (8*Column & 0x0F) );
    OLED_command( 0x00 + (8*Column & 0x0F) );
    OLED_command( 0x10 + ((8*Column>>4)&0x0F) );
    OLED_command( 0x10 + ((8*Column>>4)&0x0F) );
}

//void OLED_line (int x1, int y1, int x2, int y2) 
//{ 
//      signed int x, y, addx, addy, dx, dy; 
//      signed long P; 
//      int i; 
//      dx = abs ( (signed int) (x2 - x1)); 
//      dy = abs ( (signed int) (y2 - y1)); 
//      x = x1; 
//      y = y1; 
//
//      if (x1 > x2) 
//         addx = -1; 
//
//      else 
//      addx = 1; 
//
//      if (y1 > y2) 
//         addy = -1; 
//
//      else 
//      addy = 1; 
//
//      if (dx >= dy) 
//      { 
//         P = 2 * dy - dx; 
//         for (i = 0; i<= dx;  i++) 
//         { 
//            oledGotoYX(x,y); 
//
//            if (P < 0) 
//            { 
//               P += 2*dy; 
//               x += addx; 
//            } 
//
//            else 
//            { 
//               P += 2*dy - 2 * dx; 
//               x += addx; 
//               y += addy; 
//            } 
//         } 
//      } 
//
//      else 
//      { 
//         P = 2 * dx - dy; 
//         for (i = 0; i<= dy;  i++) 
//         { 
//            oledGotoYX(x, y); 
//
//            if (P < 0) 
//            { 
//               P += 2*dx; 
//               y += addy; 
//            } 
//
//            else 
//            { 
//               P += 2*dx - 2 * dy; 
//               x += addx; 
//               y += addy; 
//            } 
//         } 
//      } 
//}
//   
//void OLED_rect(int x1, int y1, int x2, int y2, int riemp) 
//   { 
//      if (riemp) 
//      { 
//         int y, ymax;      // Find the y min and max 
//         if (y1 < y2) 
//         { 
//            y = y1; 
//            ymax = y2; 
//         } 
//
//         else 
//         { 
//            y = y2; 
//            ymax = y1; 
//         } 
//
//         for (; y <= ymax; ++y)     // Draw lines to fill the rectangle 
//            OLED_line (x1, y, x2, y); 
//      } 
//
//      else 
//      { 
//         OLED_line (x1, y1, x2, y1); // Draw the 4 sides 
//         OLED_line (x1, y2, x2, y2); 
//         OLED_line (x1, y1, x1, y2); 
//         OLED_line (x2, y1, x2, y2); 
//      } 
//   } 

void  OLED_init()
{  
   OLED_command (0xae); 
   OLED_command (0xa8); 
   OLED_command (0x3f); 
   OLED_command (0xd3); 
   OLED_command (0x00); 
   OLED_command (0x40); 
    
   OLED_command (0xa0); 
   OLED_command (0xa1); 
   OLED_command (0xc0); 
    
   OLED_command (0xc8); 
   OLED_command (0xda); 
   OLED_command (0x12); 
   OLED_command (0x81); 
   OLED_command (0xfF); 
   OLED_command (0xa4); 
   OLED_command (0xa6); 
   OLED_command (0xd5); 
   OLED_command (0x80); 
   OLED_command (0x8d); 
   OLED_command (0x14); 
   OLED_command (0xAF); 
   OLED_command (0x20); 
   OLED_command (0x00);

}



void oledPutChar( char ch ){
    if ( ( ch < 32 ) || ( ch > 127 ) )
        ch = ' ';

    const uint8_t *base = &OledFont[ch - 32][0];

    uint8_t bytes[9];
    bytes[0] = 0x40;
    memmove( bytes + 1, base, 8 );
    
    I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;

    timeOut = 0;
    while (status != I2C1_MESSAGE_FAIL) {
        // write one byte to EEPROM (3 is the number of bytes to write)
        I2C1_MasterWrite(bytes,
                9,
                OLED,
                &status);

        // wait for the message to be sent or status has changed.
        while (status == I2C1_MESSAGE_PENDING);

        if (status == I2C1_MESSAGE_COMPLETE)
            break;
        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
            break;
        if (status == I2C1_MESSAGE_FAIL)
            break;
        else
            timeOut++;
    }
}

void oledClear()
{
    for ( uint16_t row = 0; row < 8; row++ ) {
        for ( uint16_t col = 0; col < 16; col++ ) {
            oledGotoYX( row, col );
            oledPutChar( ' ' );
        }
    }
}

void oledPrint( const char *s )
{
    while (*s) oledPutChar( *s++);
}

const char picture[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x3F,0x80,0x00,0xC0,0x00,0x7F,0xE0,0x00,0x30,0x00,0x1F,0xFF,0xF8,0x03,0xFF,0xF8,
	0x24,0x80,0x00,0xA0,0x00,0x7F,0xE0,0x00,0x78,0x00,0x1F,0xFF,0xF8,0x02,0x00,0x08,
	0x15,0x00,0x02,0x90,0x00,0x66,0x60,0x60,0xFC,0x00,0x17,0xA3,0x18,0x0E,0xEE,0xE8,
	0x0E,0x01,0x01,0xA0,0x00,0x66,0x60,0x61,0xFE,0x00,0x13,0x2D,0xE8,0x08,0xEE,0xE8,
	0x04,0x05,0x00,0xC0,0x00,0x66,0x60,0x60,0x30,0x00,0x14,0xAD,0xE8,0x08,0xEE,0xE8,
	0x04,0x15,0x01,0xA0,0x00,0x66,0x60,0x60,0x30,0x00,0x17,0xAD,0x98,0x08,0xEE,0xE8,
	0x04,0x55,0x02,0x90,0x00,0x66,0x60,0x60,0x30,0x00,0x17,0xA3,0xE8,0x08,0xEE,0xE8,
	0x05,0x55,0x00,0xA0,0x00,0x7F,0xE0,0x60,0x30,0x00,0x17,0xAF,0xE8,0x08,0xEE,0xE8,
	0x05,0x55,0x00,0xC0,0x00,0x7F,0xE0,0x60,0x30,0x00,0x17,0xAF,0x18,0x0E,0xEE,0xE8,
	0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFC,0x30,0x00,0x1F,0xFF,0xF8,0x02,0x00,0x08,
	0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xF8,0x30,0x00,0x1F,0xFF,0xF8,0x03,0xFF,0xF8,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x39,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};


void Display(void) {
    OLED_command(SSD1306_COLUMNADDR);
    OLED_command(0);   // Column start address (0 = reset)
    OLED_command(SSD1306_LCDWIDTH-1); // Column end address (127 = reset)

    OLED_command(SSD1306_PAGEADDR);
    OLED_command(0); // Page start address (0 = reset)
    #if SSD1306_LCDHEIGHT == 64
    ssd1306_command(7); // Page end address
    #endif
    #if SSD1306_LCDHEIGHT == 32
    OLED_command(3); // Page end address
    #endif
    #if SSD1306_LCDHEIGHT == 16
    OLED_command(1); // Page end address
    #endif
    
    I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;
    int number = SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8;
    timeOut = 0;
    while (status != I2C1_MESSAGE_FAIL) {
        // write one byte to EEPROM (3 is the number of bytes to write)
        I2C1_MasterWrite(picture,
                50,
                OLED,
                &status);

        // wait for the message to be sent or status has changed.
        while (status == I2C1_MESSAGE_PENDING);

        if (status == I2C1_MESSAGE_COMPLETE)
            break;
        else
            timeOut++;
    }
}
