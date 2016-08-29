/* 
 * File:   LED_BarGraph.h
 * Author: Rick
 *
 * Created on May 18, 2015, 3:37 AM
 */

#ifndef LED_BARGRAPH_H
#define	LED_BARGRAPH_H

#define LED_ON 1
#define LED_OFF 0

#define LED_RED 1
#define LED_YELLOW 2
#define LED_GREEN 3

#define HT16K33_BLINK_CMD 0x80
#define HT16K33_BLINK_DISPLAYON 0x01
#define HT16K33_BLINK_OFF 0
#define HT16K33_BLINK_2HZ  1
#define HT16K33_BLINK_1HZ  2
#define HT16K33_BLINK_HALFHZ  3

#define HT16K33_CMD_BRIGHTNESS 0xE0

#define SEVENSEG_DIGITS 5

long int displaybuffer[10];

void LEDsetValue(int value, int color);
void LEDBsetBrightness(int b, char i2c_addr);
void LEDblinkRate(int b, char i2c_addr);
void LEDbegin(char i2c_addr);
void LEDwriteDisplay(char i2c_addr);
void LEDclear(void);
void LEDsetBar(int bar, int color);





#endif	/* LED_BARGRAPH_H */

