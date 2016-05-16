#include <xc.h>
#include "Define.h"
#include "Current.h"
#include "Global.h"
#include "mcc_generated_files/adc.h"

float Battery_Current[5] = 0;
float TempBattery_Current[5] = 0;
float PrevBattery_Current[5] = 0;
float Current_Mean = 0;

char Current_Fault()
{
    char fault = 0;      // Init fault as if there is none
    for(int i = 0;i<4;i++)
    {
        if ((CURRENTHIGH < Battery_Current[i]) && (CURRENTHIGH < Current_Mean)) // I need to add the ability to check other packets
        {
            fault++;
        }
    }
    if(fault > NUMFALTS)
    {
        fault = 1;
    }
    else
    {
        fault = 0;
    }
    return fault;
}

void Current_Read()
{
  //Set the ADC interupt to start to fill in the Battery ADC Buffer
  ADC_Buffer_Point = 0;
  Current_Aquire = 1;  //Set global flag for ADC ISR to trigger battery volt reads
  ADCON1 = 0x80; //Set up to run ADC from VDD to Vss
  ADC_GetConversion(Asen);
}

void Current_Filter()
{
   // This is a exponential moving average.
   for(int x = 0; x < 4; x++)
   {
      Battery_Current[x] = (BATALPHA*TempBattery_Current[x] + ((1- BATALPHA)*PrevBattery_Current[x]));
      PrevBattery_Current[x] = Battery_Current[x];
      Current_Mean += Battery_Current[x];
   }
   Current_Mean = Current_Mean/5.0;
}

void Current_Convert()
{
    for(int x = 0; x < 4; x++)
    {
        TempBattery_Current[x] = ((((Current_Adc[x]/1024)*500)-2500)/66); //Normal converson w/ 2.5 offset and 66mV/A
    }
    Current_Filter();
}

float Current_Get()
{
    return  Current_Mean;
}
