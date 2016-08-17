/*******************************************************************
 * @brief           Radio.c
 * @brief           Controls radio functions, state system 
 * @return          N/A
 * @note            
 *******************************************************************/
#include "Radio.h"
#include "SR_FRS.h"
#include "PinDef.h"
#include <xc.h>
#include <stdbool.h>
#include "Timer.h"
#include "ADC.h"
#include "Function.H"

#define TALKBUTTONWAIT 5
#define LISTENBUTTONWAIT 5
#define POWERDOWNTIME 100000
#define ACTIVELED 15
#define VOLTAGEDIVIDERRATIO 3
#define BATTERYLVCUTOFF 6.2

int time = 0;
int count = 0;
float Battery = 0;
char Mode = 0;
bool Talking = false;
bool Shutdown = false;

/*******************************************************************
 * @brief           RadioBegin
 * @brief           SR_FRS start
 * @return          none
 * @note            Sets up modem
 *******************************************************************/
void RadioBegin(){
    SR_FRSStart();  //Set up radio
}

/*******************************************************************
 * @brief           RadioOperation
 * @brief           State system
 * @return          none
 * @note            runs radio operation
 *******************************************************************/
void RadioOperation(){
    if(!PushToTalk && !Talking){  //if button for talking is held down and we are not talking
        count++;  
    }
    if((count > TALKBUTTONWAIT) && !Talking){  //If we waited long enough and we are still not talking
        SR_FRSTalk();  //Tell the radio to activate PTT
        LED_Red = 1;   //turn the LED on
        Talking = true;  //We are now talking
        //TMR2_StopTimer();  //Stop timer for sleep fcn
        ClearTicker();       //clear the ticker from the timer
    }
    if(Talking && PushToTalk){   //if we are talking and button is high
        count--;
        if(count < LISTENBUTTONWAIT){  //if we passed this op LISTENBUTTONWAIT times
            LED_Red = 0;         //turn off led
            SR_FRSTalk();        //toggle radio ptt to off
            //TMR2_StartTimer(); //start timer back up for sleep
            count = 0;           //clear counter
            Talking = false;     //clear talking flag
        }
    }
    if(Talking && !PushToTalk){ //This is to reload count if a breaf blip happens on the button while held down
        count = TALKBUTTONWAIT;
    }
    if(!Talking && PushToTalk){ //This is to reload count if a breaf blip happens on the button while whaiting to talk
        count = 0;
    }
    if(GetTicker() > POWERDOWNTIME){  //if ticker passes POWERDOWNTIME
        //SHUT DOWN DEVICE 
        SR_FRSPowerDown();    //shut off radio
        LED_Blue = 1;         //Led user know - make need to make this better     
    }
    if(time > ACTIVELED){            //Because this fcn runs every 100ms, this fcn runs every ACTIVELED
        LED_Green = 1;                          //Turn on LED
        Battery = ReadVoltage(BATT);            //Read bat
        Battery = (Battery*5.0)/1023.0;         //Convert to voltage
        Battery = Battery*VOLTAGEDIVIDERRATIO;  //Revert to batteryV
        time = 0;                               //Clear counter
    }
    if((time > 1) && (LED_Green == 1)){         //Turns off LED after 100ms 
        LED_Green = 0;
    }
    if(Battery < BATTERYLVCUTOFF){              //If battery is dead
        //SR_FRSPowerDown();          //Turn off RADIO
        //LED_Red = 1;                //Led user know
    }
    if(ReadCharger() == CHARGING){  //If we sense the charger running
        LED_Blue = 1;   //turn on Blue LED
    }
    if(ReadCharger() == DONE){      //if we sense charging done
        LED_Blue = 0;  //Turn off LED
        LED_Green = 1; //Turn on Green LED 
    }
    time++;  //ticker for led blink
}
