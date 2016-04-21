#include "Functions.h"

void Delay(long int wait) {
    long int i = 0;
    for (; wait > i; i++) {
        __delay_ms(1); // function provided by xc compiler
    }
}