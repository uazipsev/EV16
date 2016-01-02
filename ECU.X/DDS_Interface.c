#include "DDS_Interface.h"

int seekButtonChange() {
    int i = 0;
    int changeInButton = 0;
    for (i = 0; i < 8; i++) {
        bool buttonState = ((buttons >> i)&(0x01));
        if (buttonArray[i] != buttonState) {
            buttonArray[i] = buttonState;
            changeInButton = i;
        }
    }
    return changeInButton;
}

void changeLEDState(int LED, int state) {
    if (state)
        indicators = indicators | (state << LED);
    
    else if (state == 2)
        indicators = indicators;//| (state << LED);
    
    else
        indicators = indicators & (0xFF^(!state << LED));
}