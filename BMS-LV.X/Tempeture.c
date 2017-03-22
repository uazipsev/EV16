
#include "Define.h"
#include "Tempeture.h"
#include "mcc_generated_files/adc.h"
#include <math.h>
#include <stdio.h>
#include <pic18f45k22.h>

float Temp_DegF[8] = 0;
float TmpTemp_DegF[8] = 0;
float PrevTemp_DegF[8] = 0;

int Temp_Adc[8];


void TempRun(){
    Temp_Read();
    Temp_Convert();
}

char Temp_Fault()
{
    // Init fault as if there is none
    char fault = 0;
    for(int i = 0;i<NUMOFBATT;i++)
    {
        if (TEMPHIGH > Temp_DegF[i])
        {
            printf("Temp Sense %b is too hot",i);
            fault = 1;
        }
    }
    return fault;
}

void Temp_Read()
{
  TEMP_SENSE_PWR = TEMP_ON;
  ADCON1 = 0x80; //Set up to run ADC from VDD to VSS
  Temp_Adc[0] = ADC_GetConversion(TEMP1);
  Temp_Adc[1] = ADC_GetConversion(TEMP2);
  Temp_Adc[2] = ADC_GetConversion(TEMP3);
  Temp_Adc[3] = ADC_GetConversion(TEMP4);
  Temp_Adc[4] = ADC_GetConversion(TEMP5);
  Temp_Adc[5] = ADC_GetConversion(TEMP6);
  Temp_Adc[6] = ADC_GetConversion(TEMP7);
  TEMP_SENSE_PWR = TEMP_OFF;
}

void Temp_Filter()
{
   // This is a exponential moving average.
   for(int x = 0; x < NUMOFBATT; x++)
   {
       Temp_DegF[x] = (TEMPALPHA*TmpTemp_DegF[x] + ((1- TEMPALPHA)*PrevTemp_DegF[x]));
       PrevTemp_DegF[x] = Temp_DegF[x];
   }
}

void Temp_Convert()
{
   float steinhart;
   for(int x = 0; x < NUMOFBATT; x++)
   {
       steinhart = (SERIESRESISTOR / ((1023.0 / Temp_Adc[x]) - 1)) / THERMISTORNOMINAL;  //Convert ADC counts to resistance/Ro
       steinhart = log(steinhart);                       // ln(R/Ro)
       steinhart /= BCOEFFICIENT;                        // 1/B * ln(R/Ro)
       steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
       steinhart = 1.0 / steinhart;                      // Invert
       steinhart -= 273.15;                              // convert to C
       steinhart = (steinhart*1.8) + 32.0;            // convert to F
       TmpTemp_DegF[x] = steinhart;
   }
   Temp_Filter();
}

float Tempeture_Get(int channelnum)
{
   return  Temp_DegF[channelnum];
}