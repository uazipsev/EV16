#include "Function.h"
#include "LED_BarGraph.h"
#include <xc.h>
#include "mcc_generated_files/mcc.h"

void Delay(int wait) {
    int x;
    for (x = 0; x < wait; x++) {
        __delay_ms(1);
    }
}

void TestBarGraph(){
    for (char b=0; b<24; b++){
        LEDsetBar(b, LED_YELLOW);
        LEDwriteDisplay(0x70);
        LEDwriteDisplay(0x71);
        Delay(100);
        LEDsetBar(b, LED_OFF);
        LEDwriteDisplay(0x70);
        LEDwriteDisplay(0x71);
    }
    for (char b=0; b<24; b++){
        LEDsetBar(b, LED_GREEN);
        LEDwriteDisplay(0x70);
        LEDwriteDisplay(0x71);
        Delay(100);
        LEDsetBar(b, LED_OFF);
        LEDwriteDisplay(0x70);
        LEDwriteDisplay(0x71);
    }
}