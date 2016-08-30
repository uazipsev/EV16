/*
 * File:   FastTransfer2.c
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015
 */

#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "FastTransfer2.h"
#include "PinDef.h"

bool CLI = 1;

void wipeRxBuffer2(void)
{
	int i=0;
	for(i=0;i<RX_BUFFER_SIZE2;i++)
	{
		rx_buffer2[i]=0;
		
	}
	
}

//Captures address of receive array, the max data address, the address of the module, true/false if AKNAKs are wanted and the Serial address

void begin2(volatile int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void), int (*stuffavailable)(void), unsigned char (*stuffpeek)(void)) {
    receiveArrayAddress2 = ptr;
    moduleAddress2 = givenAddress;
    serial_write2 = stufftosend;
    serial_available2 = stuffavailable;
    serial_peek2 = stuffpeek;
    serial_read2 = stufftoreceive;
    maxDataAddress2 = maxSize / 2;
    sendStructAddress2 = (unsigned char*) & ring_buffer2;
    AKNAKsend2 = error;
    alignErrorCounter2 = 0;

}

//CRC Calculator

unsigned char CRC82(const unsigned char * data, unsigned char len) {
    unsigned char crc = 0x00;
    while (len--) {
        unsigned char extract = *data++;
        unsigned char tempI;
        for (tempI = 8; tempI; tempI--) {
            unsigned char sum = (crc ^ extract) & 0x01;
            crc >>= 1;
            if (sum) {
                crc ^= polynomial;
            }
            extract >>= 1;
        }
    }
    return crc;
}

//Sends out send buffer with a 2 start bytes, where the packet is going, where it came from, the size of the data packet, the data and the crc.

void sendData2(unsigned char whereToSend) {

    //calculate the crc
    unsigned char CS = CRC82(sendStructAddress2, ring_buffer2.count);

    serial_write2(0x06); //start address
    serial_write2(0x85); //start address
    serial_write2(whereToSend);
    serial_write2(moduleAddress2);
    serial_write2(ring_buffer2.count); //length of packet not including the crc


    //send the rest of the packet
    int i;
    for (i = 0; i < ring_buffer2.count; i++) {
        serial_write2(*(sendStructAddress2 + i));
    }

    //send the crc
    serial_write2(CS);

    //record the sent message data for aknak check later
    crcBufS_put2(&crc_buffer2, whereToSend, CS, 0);

    // clears the buffer after a sending
    FastTransfer_buffer_flush2(&ring_buffer2, 1);

}

char receiveData2() {
    if(!CLI){
        //start off by looking for the header bytes. If they were already found in a previous call, skip it.
        if (rx_len2 == 0) {
            //this size check may be redundant due to the size check below, but for now I'll leave it the way it is.
            if (serial_available2() > 4) {

                //this will block until a 0x06 is found or buffer size becomes less then 3.
                while (serial_read2() != 0x06) {
                    //This will trash any preamble junk in the serial buffer
                    //but we need to make sure there is enough in the buffer to process while we trash the rest
                    //if the buffer becomes too empty, we will escape and try again on the next call
                    alignErrorCounter2++; //increments the counter whenever a byte is trashed
                    if (serial_available2() < 5)
                        return false;
                }
                if (serial_read2() == 0x85) {
                    rx_address2 = serial_read2(); // pulls the address
                    returnAddress2 = serial_read2(); // pulls where the message came from
                    rx_len2 = serial_read2(); // pulls the length
                    //make sure the address received is a match for this module if not throw the packet away
                    if (rx_address2 != moduleAddress2) {
                        addressErrorCounter2++; // increments a counter whenever the wrong address is received
                        //if the address does not match the buffer is flushed for the size of
                        //the data packet plus one for the CRC
                        //int u;
                        //for (u = 0; u <= (rx_len2 + 1); u++) {
                            //serial_read2();
                        //}
                        rx_len2 = 0; // reset length
                        return false;
                    }
                    // if the address matches the a dynamic buffer is created to store the received data
                    //rx_buffer2 = (unsigned char*) malloc(rx_len2 + 1);
                }
            }
        }

        //we get here if we already found the header bytes, the address matched what we know, and now we are byte aligned.
        if (rx_len2 != 0) {

            //this check is preformed to see if the first data address is a 255, if it is then this packet is an AKNAK
            if (rx_array_inx2 == 0) {
//                while (!(serial_available2() >= 1));
//                if (255 == serial_peek2()) {
//                    CRCcheck2();
//                    rx_len2 = 0;
//                    rx_array_inx2 = 0;
//                    wipeRxBuffer2();
//                    //free(rx_buffer2);
//                    return receiveData2();
//                }
            }


            while (serial_available2() && rx_array_inx2 <= rx_len2) {
                rx_buffer2[rx_array_inx2++] = serial_read2();
            }

            if (rx_len2 == (rx_array_inx2 - 1)) {
                //seem to have got whole message
                //last uint8_t is CS
                calc_CS2 = CRC82(rx_buffer2, rx_len2);



                if (calc_CS2 == rx_buffer2[rx_array_inx2 - 1]) {//CS good

                    // reassembles the data and places it into the receive array according to data address.
                    int r;
                    for (r = 0; r < rx_len2; r = r + 3) {
                        if (rx_buffer2[r] < maxDataAddress2) {
                            group2.parts[0] = rx_buffer2[r + 1];
                            group2.parts[1] = rx_buffer2[r + 2];
                            receiveArrayAddress2[(rx_buffer2[r])] = group2.integer;
                        } else {
                            dataAdressErrorCounter2++;
                        }
                    }


                    if (AKNAKsend2) { // if enabled sends an AK
                        unsigned char holder[3];
                        holder[0] = 255;
                        holder[1] = 1;
                        holder[2] = rx_buffer2[rx_array_inx2 - 1];
                        unsigned char crcHolder = CRC82(holder, 3);
                        serial_write2(0x06);
                        serial_write2(0x85);
                        serial_write2(returnAddress2);
                        serial_write2(moduleAddress2);
                        serial_write2(3);
                        serial_write2(255);
                        serial_write2(1);
                        serial_write2(rx_buffer2[rx_array_inx2 - 1]);
                        serial_write2(crcHolder);
                    }



                    rx_len2 = 0;
                    rx_array_inx2 = 0;
                    wipeRxBuffer2();
                    //free(rx_buffer2);
                    return true;
                } else {
                    crcErrorCounter2++; //increments the counter every time a crc fails

                    if (AKNAKsend2) { // if enabled sends NAK
                        unsigned char holder[3];
                        holder[0] = 255;
                        holder[1] = 2;
                        holder[2] = rx_buffer2[rx_array_inx2 - 1];
                        unsigned char crcHolder = CRC82(holder, 3);
                        serial_write2(0x06);
                        serial_write2(0x85);
                        serial_write2(returnAddress2);
                        serial_write2(moduleAddress2);
                        serial_write2(3);
                        serial_write2(255);
                        serial_write2(2);
                        serial_write2(rx_buffer2[rx_array_inx2 - 1]);
                        serial_write2(crcHolder);
                    }

                    //failed checksum, need to clear this out
                    rx_len2 = 0;
                    rx_array_inx2 = 0;
                    wipeRxBuffer2();
                    //free(rx_buffer2);
                    return false;
                }
            }
        }
        return false;
    }
    else{
        return serial_available2();
    }
}


// populates what info needs sent and to what data address

void ToSend2(unsigned char where, unsigned int what) {
    FastTransfer_buffer_put2(&ring_buffer2, where, what);
}


// disassembles the data and places it in a buffer to be sent

void FastTransfer_buffer_put2(struct ringBufS2 *_this, unsigned char towhere, unsigned int towhat) {

    group2.integer = towhat;

    if (_this->count < (BUFFER_SIZE - 3)) {
        _this->buf[_this->head] = towhere;
        _this->head = FastTransfer_buffer_modulo_inc2(_this->head, BUFFER_SIZE);
        ++_this->count;
        _this->buf[_this->head] = group2.parts[0];
        _this->head = FastTransfer_buffer_modulo_inc2(_this->head, BUFFER_SIZE);
        ++_this->count;
        _this->buf[_this->head] = group2.parts[1];
        _this->head = FastTransfer_buffer_modulo_inc2(_this->head, BUFFER_SIZE);
        ++_this->count;

    }

}


//pulls info out of the send buffer in a first in first out fashion

unsigned char FastTransfer_buffer_get2(struct ringBufS2* _this) {
    unsigned char c;
    if (_this->count > 0) {
        c = _this->buf[_this->tail];
        _this->tail = FastTransfer_buffer_modulo_inc2(_this->tail, BUFFER_SIZE);
        --_this->count;
    } else {
        c = 0;
    }
    return (c);
}

void *memset(void *s, int c, size_t n);

//flushes the send buffer to get it ready for new data

void FastTransfer_buffer_flush2(struct ringBufS2* _this, const int clearBuffer) {
    _this->count = 0;
    _this->head = 0;
    _this->tail = 0;
    if (clearBuffer) {
        memset(_this->buf, 0, sizeof (_this->buf));
    }
}


// increments counters for the buffer functions

unsigned int FastTransfer_buffer_modulo_inc2(const unsigned int value, const unsigned int modulus) {
    unsigned int my_value = value + 1;
    if (my_value >= modulus) {
        my_value = 0;
    }
    return (my_value);
}


//searches the buffer for the status of a message that was sent

unsigned char AKNAK2(unsigned char module) {
    int r;
    for (r = 0; r < CRC_COUNT; r++) {
        if (module == crcBufS_get2(&crc_buffer2, r, 0)) {
            return crcBufS_get2(&crc_buffer2, r, 2);
        }
    }
    return 4;
}


//returns align error

unsigned int alignError2(void) {
    return alignErrorCounter2;
}


//returns CRC error

unsigned int CRCError2(void) {
    return crcErrorCounter2;
}


//returns address error

unsigned int addressError2(void) {
    return addressErrorCounter2;
}

unsigned int dataAddressError2(void) {
    return dataAdressErrorCounter2;
}

// after a packet is sent records the info of that packet

void crcBufS_put2(struct crcBufS2* _this, unsigned char address, unsigned char oldCRC, unsigned char status) {
    _this->buf[_this->head] = address;
    _this->head++;
    _this->buf[_this->head] = oldCRC;
    _this->head++;
    _this->buf[_this->head] = status;
    _this->head++;
    if (_this->head >= CRC_BUFFER_SIZE) {
        _this->head = 0;
    }
}


// after a Ak or NAK is received that status is stored

void crcBufS_status_put2(struct crcBufS2* _this, unsigned char time, unsigned char status) {
    if (time >= CRC_COUNT) {
        time = CRC_COUNT - 1;
    }
    time = time + 1;
    int wantedTime = time * 3;
    if (wantedTime > _this->head) {
        wantedTime = (CRC_BUFFER_SIZE) - (wantedTime - _this->head);
        _this->buf[(wantedTime + 2)] = status;
    } else {
        _this->buf[(_this->head - wantedTime) + 2] = status;
    }
}


// pulls data from the AKNAK buffer

unsigned char crcBufS_get2(struct crcBufS2* _this, unsigned char time, unsigned char space) {
    if (time >= CRC_COUNT) {
        time = CRC_COUNT - 1;
    }
    if (space >= CRC_DEPTH) {
        space = CRC_DEPTH - 1;
    }
    time = time + 1;
    int wantedTime = time * 3;
    if (wantedTime > _this->head) {
        wantedTime = (CRC_BUFFER_SIZE) - (wantedTime - _this->head);
        return (_this->buf[(wantedTime + space)]);
    } else {
        return (_this->buf[(_this->head - wantedTime) + space]);
    }
}


//when an AK or NAK is received this compares it to the buffer and records the status

void CRCcheck2(void) {

    while (!(serial_available2() > 3)); // trap makes sure that there are enough bytes in the buffer for the AKNAK check

    unsigned char arrayHolder[3];
    arrayHolder[0] = serial_read2();
    arrayHolder[1] = serial_read2();
    arrayHolder[2] = serial_read2();
    unsigned char SentCRC = serial_read2();
    unsigned char calculatedCRC = CRC82(arrayHolder, 3);


    if (SentCRC == calculatedCRC) {

        int rt;
        for (rt = 0; rt < CRC_COUNT; rt++) {
            if (returnAddress2 == crcBufS_get2(&crc_buffer2, rt, 0)) {
                if (arrayHolder[2] == crcBufS_get2(&crc_buffer2, rt, 1)) {
                    if (arrayHolder[1] == 1) {
                        crcBufS_status_put2(&crc_buffer2, rt, 1);
                        break;
                    } else if (arrayHolder[1] == 2) {
                        crcBufS_status_put2(&crc_buffer2, rt, 2);
                        break;
                    }
                }
            }
        }
    } else {
        crcErrorCounter2++;
    } //increments the counter every time a crc fails
}

