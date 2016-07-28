#include <stdio.h>
#include "EEprom.h"

#define NUMOFDRIVER 5

char *DriverData[NUMOFDRIVER] = {"","Andrew T.","Trevin H.","Ben .B","Richard J."};
char CurentDriver; 

void SetDriver(char num){
    CurentDriver = num;
    SaveCarDriver(num);
}

int DriverCount(){
    return NUMOFDRIVER;
}

char *DriverName(int num){
    return DriverData[num];
}

char DriverActive(){
    return CurentDriver;
}