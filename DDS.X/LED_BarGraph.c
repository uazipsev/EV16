
#include "LED_BarGraph.h"
#include "mcc_generated_files/i2c1.h"

#define SLAVE_I2C_GENERIC_RETRY_MAX     4

#ifndef _BV
#define _BV(bit) (1<<(bit))
#endif

void LEDsetValue(int value, int color) {
    if (value > 24) value = 24;
    if (value < 0) value = 0;
    int k;
    for (k = 0; k < 24; k++) {
        if (k < value){ 
             //LATC1 = ~LATC1;
            LEDsetBar(k, color);}
        else LEDsetBar(k, LED_OFF);
    }
    return;

}

void LEDBsetBrightness(int b, char i2c_addr) {
    if (b > 15) b = 15;
    uint8_t writeBuffer[2];
    uint16_t timeOut;
    writeBuffer[0] = (HT16K33_CMD_BRIGHTNESS | b);
    I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;

    timeOut = 0;
    while (status != I2C1_MESSAGE_FAIL) {
        // write one byte to EEPROM (3 is the number of bytes to write)
        I2C1_MasterWrite(&writeBuffer,
                1,
                i2c_addr,
                &status);

        // wait for the message to be sent or status has changed.
        while (status == I2C1_MESSAGE_PENDING);

        if (status == I2C1_MESSAGE_COMPLETE)
            break;
        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
            break;
        if (status == I2C1_MESSAGE_FAIL)
            break;
        else
            timeOut++;
    }
    //I2C1_MasterWrite( (HT16K33_CMD_BRIGHTNESS | b),1,i2c_addr,I2C1_MESSAGE_PENDING);
}

void LEDblinkRate(int b, char i2c_addr) {
    if (b > 3) b = 0; // turn off if not sure
    uint8_t writeBuffer[2];
    uint16_t timeOut;
    writeBuffer[0] = (HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1));
    I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;

    timeOut = 0;
    while (status != I2C1_MESSAGE_FAIL) {
        // write one byte to EEPROM (3 is the number of bytes to write)
        I2C1_MasterWrite(&writeBuffer,
                1,
                i2c_addr,
                &status);

        // wait for the message to be sent or status has changed.
        while (status == I2C1_MESSAGE_PENDING);

        if (status == I2C1_MESSAGE_COMPLETE)
            break;
        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
            break;
        if (status == I2C1_MESSAGE_FAIL)
            break;
        else
            timeOut++;
    }
    //I2C1_MasterWrite( (HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1)),1,i2c_addr,I2C1_MESSAGE_PENDING);
}

void LEDbegin(char i2c_addr) {
    uint8_t writeBuffer[3];
    uint16_t timeOut;
    writeBuffer[0] = 0x21;
    I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;

    timeOut = 0;
    while (status != I2C1_MESSAGE_FAIL) {
        // write one byte to EEPROM (3 is the number of bytes to write)
        I2C1_MasterWrite(&writeBuffer,
                1,
                i2c_addr,
                &status);

        // wait for the message to be sent or status has changed.
        while (status == I2C1_MESSAGE_PENDING);

        if (status == I2C1_MESSAGE_COMPLETE)
            break;
        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
            break;
        if (status == I2C1_MESSAGE_FAIL)
            break;
        else
            timeOut++;
    }
    //I2C1_MasterWrite(0x21,1,i2c_addr,I2C1_MESSAGE_PENDING);
    LEDblinkRate(HT16K33_BLINK_OFF, i2c_addr);
    LEDBsetBrightness(15, i2c_addr); // max brightness
}

void LEDwriteDisplay(char i2c_addr) {
    uint8_t writeBuffer[20];
    uint16_t timeOut;
    writeBuffer[0] = 0x00;
    I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;

    timeOut = 0;
    while (status != I2C1_MESSAGE_FAIL) {
        // write one byte to EEPROM (3 is the number of bytes to write)
        I2C1_MasterWrite(&writeBuffer,
                1,
                i2c_addr,
                &status);

        // wait for the message to be sent or status has changed.
        while (status == I2C1_MESSAGE_PENDING);

        if (status == I2C1_MESSAGE_COMPLETE)
            break;
        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
            break;
        if (status == I2C1_MESSAGE_FAIL)
            break;
        else
            timeOut++;
    }
    I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;


    //I2C1_MasterWrite( (uint8_t)0x00,1,i2c_addr,I2C1_MESSAGE_PENDING);
    //I2C1_MasterWrite( &displaybuffer,8,i2c_addr,I2C1_MESSAGE_PENDING);
    writeBuffer[0] = 0;
    writeBuffer[1] = displaybuffer[0] & 0xFF;
    writeBuffer[2] = displaybuffer[0] >> 8;
    writeBuffer[3] = displaybuffer[1] & 0xFF;
    writeBuffer[4] = displaybuffer[1] >> 8;
    writeBuffer[5] = displaybuffer[2] & 0xFF;
    writeBuffer[6] = displaybuffer[2] >> 8;
    writeBuffer[7] = displaybuffer[3] & 0xFF;
    writeBuffer[8] = displaybuffer[3] >> 8;
    writeBuffer[9] = displaybuffer[4] & 0xFF;
    writeBuffer[10] = displaybuffer[4] >> 8;
    writeBuffer[11] = displaybuffer[5] & 0xFF;
    writeBuffer[12] = displaybuffer[5] >> 8;
    writeBuffer[13] = displaybuffer[6] & 0xFF;
    writeBuffer[14] = displaybuffer[6] >> 8;
    writeBuffer[15] = displaybuffer[7] & 0xFF;
    writeBuffer[16] = displaybuffer[7] >> 8;
    writeBuffer[17] = displaybuffer[8] & 0xFF;
    writeBuffer[18] = displaybuffer[8] >> 8;

    timeOut = 0;
    while (status != I2C1_MESSAGE_FAIL) {
        // write one byte to EEPROM (3 is the number of bytes to write)
        I2C1_MasterWrite(&writeBuffer,
                17,
                i2c_addr,
                &status);

        // wait for the message to be sent or status has changed.
        while (status == I2C1_MESSAGE_PENDING);

        if (status == I2C1_MESSAGE_COMPLETE)
            break;
        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
            break;
        if (status == I2C1_MESSAGE_FAIL)
            break;
        else
            timeOut++;
    }
}

void LEDclear(void) {
    for (uint8_t i = 0; i < 8; i++) {
        displaybuffer[i] = 0;
    }
}

void LEDsetBar(int bar, int color) {
    uint16_t a, c;

    if (bar < 12)
        c = bar / 4;
    else
        c = (bar - 12) / 4;

    a = bar % 4;
    if (bar >= 12)
        a += 4;

    //Serial.print("Ano = "); Serial.print(a); Serial.print(" Cath = "); Serial.println(c);
    if (color == LED_RED) {
        // Turn on red LED.
        displaybuffer[c] |= _BV(a);
        // Turn off green LED.
        displaybuffer[c] &= ~_BV(a + 8);
    } else if (color == LED_YELLOW) {
        // Turn on red and green LED.
        displaybuffer[c] |= _BV(a) | _BV(a + 8);
    } else if (color == LED_OFF) {
        // Turn off red and green LED.
        displaybuffer[c] &= ~_BV(a) & ~_BV(a + 8);
    } else if (color == LED_GREEN) {
        // Turn on green LED.
        displaybuffer[c] |= _BV(a + 8);
        // Turn off red LED.
        displaybuffer[c] &= ~_BV(a);
    }
}

