#include <stdio.h>
#include "EEprom.h"

#define NUMOFDRIVER 5

char *DriverData[NUMOFDRIVER] = {"","Andrew T.","Trevin H.","Ben .B","Richard J."};


void SetDriver(char num){
    printf("\n %d is Active\n",num);
    SaveCarDriver(num);
}

int DriverCount(){
    return NUMOFDRIVER;
}

char *DriverName(int num){
    return DriverData[num];
}