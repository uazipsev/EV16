#include "Shift595.h"
#include "mcc_generated_files/pin_manager.h"
#include "xc.h"
#include "Functions.h"

/*
 * On init we want to clear out the shift Reg.
 * This code does that.
 */
void StartUp595() {
    //Shut off outputs to get ready for config!
    OUTEN_SetHigh();
    CLEAR_SetHigh();
    //clear all shift reg's
    Delay(2);
    OUTEN_SetLow();
    Delay(2); 
    CLEAR_SetLow();
    Delay(2);
    OUTEN_SetHigh();
    Delay(2);
    CLEAR_SetHigh();
    //Init Config Done! Set for regular updates
    Clear595();
}

/*
 * This piece of code allows use to set bits in the right paces to set outputs of the shift reg's
 * The fcn can't augment the array so you need to make sure the array is big enugh for the application
 * This is ajusted in the .h file with num_of_595s
 */
void SetPin595(int Reg, int pin, int value) {
    registers[((Reg - 1)*8) + pin] = value;
}

/*
 *  This will clear the array and set all outputs to zero
 */
void Clear595(void) {
    for (int i = RegPins - 1; i >= 0; i--) {
        registers[i] = LOW;
    }

    writeRegisters();
}

/*
 *  This is a fcn that will set outputs based the private array of this c file
 */
void writeRegisters(void) {
    int val = 0;
    for (int i = RegPins - 1; i >= 0; i--) {
        CLK_SetLow(); //Set clock low (data is shifted in on rising edge)
        //Delay(2);
        val = registers[i];
        if (val == HIGH) {
            DATA_OUT_SetHigh();
        } else if (val == LOW) {
            DATA_OUT_SetLow();
        }
        //Delay(1);
        CLK_SetHigh(); //shift data in
        //Delay(2);
    }
    //shift data over from sift reg to storage reg. 
    CLK_SetLow();
    Delay(1);
    LAT_SetHigh();
    Delay(1);
    LAT_SetLow(); // set select low
}

