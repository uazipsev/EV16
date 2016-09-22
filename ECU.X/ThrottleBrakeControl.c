
#include "ThrottleBrakeControl.h"
#include "SASComms.h"
#include "PinDef.h"

unsigned int throttle1, throttle2, brake1,brake2;
unsigned int ThrottlePrecent, TripThrottle, TripBrake, ThrottleMax = 0;

extern int SAS_FAULT_CONDITION;
bool CheckThrotleConsistency() {
    throttle1 = GetSASRaw(GETSAST1RAW);
    throttle2 = GetSASRaw(GETSAST1RAW);
    brake1 = GetSASRaw(GETSASB1RAW);

    //throttle consistency check
    if((((throttle1*(ThrottlePrecent/100)) > throttle2) && ((throttle1 *((ThrottlePrecent/100)-1)) < throttle2))) {
        //SAS_FAULT_CONDITION = THROTTLE_SANITY_CHECK; // TODO: This is erroring out - need filtering!
        //throttle1=0;
        //throttle2=0;
    }
    if ((((throttle1 + throttle2) / 2) > TripThrottle) && (brake1 > TripBrake)) {
        //SAS_FAULT_CONDITION = THROTTLE_BRAKE_CHECK;  //  TODO: Fix me
        //throttle1=0;
        //throttle2=0;
        //brake1=0;
    }
    if((throttle1>ThrottleMax) || (throttle2 > ThrottleMax)){
        throttle1 = ThrottleMax;
        throttle2 = ThrottleMax;
    }
    return true;
}

unsigned int GetSASValue(char request){
    if(request == GETSAST1){
        return throttle1;
    }
    else if(request == GETSAST2){
        return throttle2;
    }
    else if(request == GETSASB1){
        return brake1;
    }
    else if(request == GETSASB2){
        return brake2;
    }
    else return 0;
}

char GetSASFalts(){
    return SAS_FAULT_CONDITION;
}

void SetThrotteMax(int val){
    ThrottleMax = val;
}