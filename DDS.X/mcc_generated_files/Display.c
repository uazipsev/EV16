#include "Display.h"
#include "OLED_Display.h"
#include	<stdlib.h>

void SetData(my_data data, int numb){
    char s[20];
      
    if(data == BV){
        oledGotoYX(3,2);
    }
    else if(data == BT){
        oledGotoYX(3,5);
    }
    else if(data == BC){
        oledGotoYX(5,2);
    }
    else if(data == MT){
        oledGotoYX(5,5);
    }
    else if(data == MCT){
        oledGotoYX(7,2);
    }
    else if(data == FLT){
        oledGotoYX(7,5);
    }
    itoa( s, numb, 10 );
    oledPrint( s );
}

void Setupdisplay(){
    OLED_init();
    oledClear(); 
}

void Splash(){
    oledGotoYX(3,2);
    oledPrint("University");
    oledGotoYX(3,3);
    oledPrint("OF");
    oledGotoYX(3,4);
    oledPrint("Akron");
    oledGotoYX(3,5);
    oledPrint("ZIPS-EV");
}

void Normal(){
    oledClear(); 
    oledGotoYX(3,2);
    oledPrint("University");
    oledGotoYX(3,3);
    oledPrint("OF");
    oledGotoYX(3,4);
    oledPrint("Akron");
    oledGotoYX(3,5);
    oledPrint("ZIPS-EV");
}
