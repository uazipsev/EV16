/*******************************************************************
 * @brief           Function.c
 * @brief           Catch all for the random functions of the device
 * @note            - by RJ
 *******************************************************************/

#include "Function.h"
#include "mcc_generated_files/mcc.h"
#include <xc.h>

/*******************************************************************
 * @brief           Delay
 * @brief           This fcn is used to convert _delay_ms to longer periods of time
 * @return          None
 * @note            the shortest delay is 1mS
 *******************************************************************/

void Delay(int wait) {
    int x;
    for (x = 0; x < wait; x++) {
        __delay_ms(1);
    }
}
