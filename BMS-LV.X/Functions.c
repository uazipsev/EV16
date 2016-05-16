#include <stdio.h>
#include <stdlib.h>
#include "mcc_generated_files/pin_manager.h"
#include "Functions.h"
#include "mcc_generated_files/mcc.h"
#include <xc.h>

void Set_4051(int Channel,char enable)
{
    if (Channel & 0x01)
    {
        MUX_A_SetHigh();
    }
    else
    {
        MUX_A_SetLow();
    }
    if ((Channel>>1) & 0x01)
    {
        MUX_B_SetHigh();
    }
    else
    {
        MUX_B_SetLow();
    }
    if ((Channel>>2) & 0x01)
    {
        MUX_C_SetHigh(); 
    }
    else
    {
        MUX_C_SetLow();  
    }
    if(enable == 1)
    {
        Temp_INH_SetLow();
    }
    else
    {
        Temp_INH_SetHigh();
    }
}

void Delay(int wait)
{
    int x;
    for(x = 0;x<wait;x++)
    {
       __delay_ms(1);
    }
}
