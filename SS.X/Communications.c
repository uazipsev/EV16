#include <stdbool.h>
#include <xc.h>
#include "FastTransfer.h"
#include "Communications.h"
#include "ADDRESSING.h"
//#include "mcc_generated_files/pin_manager.h"

void updateComms() {
  
    if (receiveData()) {
        //INDICATOR_Toggle();
        respondECU();
    }
}

void respondECU() {
    LATCbits.LATC5 = 1;
    ToSend(RESPONSE_ADDRESS, DDS_ADDRESS);
    ToSend(BUTTONS_DDS,0);
   // Delay(9);
    sendData(ECU_ADDRESS);
    //Delay(3);
    LATCbits.LATC5 = 0;
}

