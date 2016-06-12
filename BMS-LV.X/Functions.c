#include <stdio.h>
#include <stdlib.h>
#include "mcc_generated_files/pin_manager.h"
#include "Functions.h"
#include "mcc_generated_files/mcc.h"
#include <xc.h>


void Delay(int wait)
{
    int x;
    for(x = 0;x<wait;x++)
    {
       __delay_ms(1);
    }
}
void DelayMicro(int wait)
{
    int x;
    for(x = 0;x<wait;x++)
    {
       __delay_us(1);
    }
}