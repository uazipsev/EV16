#include "functions.h"
#include "xc.h"
#include "mcc_generated_files/mcc.h"


//Function used to make a varable delay
//We use this because the provided fcn dosn't accept large bounds

void Delay(long int wait) {
    long int i = 0;
    for (; wait > i; i++) {
        __delay_ms(1); // function provided by xc compiler
    }
}