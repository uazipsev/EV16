/*
 * File:   FastTransfer3.c
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015
 */

#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "FastTransfer3.h"
#include "UART3.h"
#include "ADDRESSING.h"

volatile int receiveArray3[20];

//INTERNAL METHODS/VARIABLES HERE
unsigned char AKNAK3(unsigned char module);
unsigned int alignError3(void);
unsigned int CRCError3(void);
unsigned int addressError3(void);
unsigned int dataAddressError3(void);
void (*serial_write3)(unsigned char);
unsigned char (*serial_read3)(void);
int (*serial_available3)(void);
unsigned char (*serial_peek3)(void);
unsigned char rx_buffer3[RX_BUFFER_SIZE3]; //address for temporary storage and parsing buffer
unsigned char rx_array_inx3; //index for RX parsing buffer
unsigned char rx_len3; //RX packet length according to the packet
unsigned char calc_CS3; //calculated Checksum
unsigned char moduleAddress3; // the address of this module
unsigned char returnAddress3; //the address to send the crc back to
unsigned char maxDataAddress3; //max address allowable
volatile int * receiveArrayAddress3; // this is where the data will go when it is received
unsigned char * sendStructAddress3; // this is where the data will be sent from
bool AKNAKsend3; // turns the acknowledged or not acknowledged on/off
unsigned int alignErrorCounter3; //counts the align errors
unsigned int crcErrorCounter3; // counts any failed crcs
unsigned int addressErrorCounter3; // counts every time a wrong address is received
unsigned int dataAdressErrorCounter3; // counts if the received data fall outside of the receive array
unsigned char rx_address3; //RX address received

void wipeRxBuffer3(void)
{
	int i=0;
	for(i=0;i<RX_BUFFER_SIZE3;i++)
	{
		rx_buffer3[i]=0;
		
	}
	
}
struct ringBufS3 { // this is where the send data is stored before sending
    unsigned char buf[BUFFER_SIZE];
    int head;
    int tail;
    int count;
};
struct ringBufS3 ring_buffer3;

union stuff3 { // this union is used to join and disassemble integers
    unsigned char parts[2];
    unsigned int integer;
};
union stuff3 group3;

struct crcBufS3 { // this is where the address where sent to, the sent crc, the status of the AKNAK
    unsigned char buf[CRC_BUFFER_SIZE];
    int head;
};
struct crcBufS3 crc_buffer3;

unsigned char CRC83(const unsigned char * data, unsigned char len);
void FastTransfer_buffer_put3(struct ringBufS3 *_this, const unsigned char towhere, const unsigned int towhat);
unsigned char FastTransfer_buffer_get3(struct ringBufS3* _this);
void FastTransfer_buffer_flush3(struct ringBufS3* _this, const int clearBuffer);
unsigned int FastTransfer_buffer_modulo_inc3(const unsigned int value, const unsigned int modulus);
void crcBufS_put3(struct crcBufS3* _this, unsigned char address, unsigned char oldCRC, unsigned char status);
void crcBufS_status_put3(struct crcBufS3* _this, unsigned char time, unsigned char status);
unsigned char crcBufS_get3(struct crcBufS3* _this, unsigned char time, unsigned char space);
void CRCcheck3(void);


void Start3(){
    begin3(receiveArray3, sizeof (receiveArray3), ECU_ADDRESS, false, Send_put3, Receive_get3, Receive_available3, Receive_peek3);
}

//Captures address of receive array, the max data address, the address of the module, true/false if AKNAKs are wanted and the Serial address

void begin3(volatile int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void), int (*stuffavailable)(void), unsigned char (*stuffpeek)(void)) {
    receiveArrayAddress3 = ptr;
    moduleAddress3 = givenAddress;
    serial_write3 = stufftosend;
    serial_available3 = stuffavailable;
    serial_peek3 = stuffpeek;
    serial_read3 = stufftoreceive;
    maxDataAddress3 = maxSize / 2;
    sendStructAddress3 = (unsigned char*) & ring_buffer3;
    AKNAKsend3 = error;
    alignErrorCounter3 = 0;

}

//CRC Calculator

unsigned char CRC83(const unsigned char * data, unsigned char len) {
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

void sendData3(unsigned char whereToSend) {

    //calculate the crc
    unsigned char CS = CRC83(sendStructAddress3, ring_buffer3.count);

    serial_write3(0x06); //start address
    serial_write3(0x85); //start address
    serial_write3(whereToSend);
    serial_write3(moduleAddress3);
    serial_write3(ring_buffer3.count); //length of packet not including the crc


    //send the rest of the packet
    int i;
    for (i = 0; i < ring_buffer3.count; i++) {
        serial_write3(*(sendStructAddress3 + i));
    }

    //send the crc
    serial_write3(CS);

    //record the sent message data for aknak check later
    crcBufS_put3(&crc_buffer3, whereToSend, CS, 0);

    // clears the buffer after a sending
    FastTransfer_buffer_flush3(&ring_buffer3, 1);

}

bool receiveData3() {

    //start off by looking for the header bytes. If they were already found in a previous call, skip it.
    if (rx_len3 == 0) {
        //this size check may be redundant due to the size check below, but for now I'll leave it the way it is.
        if (serial_available3() > 4) {
            //this will block until a 0x06 is found or buffer size becomes less then 3.
            while (serial_read3() != 0x06) {
                //This will trash any preamble junk in the serial buffer
                //but we need to make sure there is enough in the buffer to process while we trash the rest
                //if the buffer becomes too empty, we will escape and try again on the next call
                alignErrorCounter3++; //increments the counter whenever a byte is trashed
                if (serial_available3() < 5)
                    return false;
            }
            if (serial_read3() == 0x85) {
                rx_address3 = serial_read3(); // pulls the address
                returnAddress3 = serial_read3(); // pulls where the message came from
                rx_len3 = serial_read3(); // pulls the length
                //make sure the address received is a match for this module if not throw the packet away
                if (rx_address3 != moduleAddress3) {
                    addressErrorCounter3++; // increments a counter whenever the wrong address is received
                    //if the address does not match the buffer is flushed for the size of
                    //the data packet plus one for the CRC
                    //int u;
                    //for (u = 0; u <= (rx_len3 + 1); u++) {
                        serial_read3();
                    //}
                    rx_len3 = 0; // reset length
                    return false;
                }
                // if the address matches the a dynamic buffer is created to store the received data
                //rx_buffer3 = (unsigned char*) malloc(rx_len3 + 1);
            }
        }
    }

    //we get here if we already found the header bytes, the address matched what we know, and now we are byte aligned.
    if (rx_len3 != 0) {

        //this check is preformed to see if the first data address is a 255, if it is then this packet is an AKNAK
        if (rx_array_inx3 == 0) {
            while (!(serial_available3() >= 1));
            if (255 == serial_peek3()) {
                CRCcheck3();
                rx_len3 = 0;
                rx_array_inx3 = 0;
                 wipeRxBuffer3();
                //free(rx_buffer3);
                return receiveData3();
            }
        }


        while (serial_available3() && rx_array_inx3 <= rx_len3) {
            rx_buffer3[rx_array_inx3++] = serial_read3();
        }

        if (rx_len3 == (rx_array_inx3 - 1)) {
            //seem to have got whole message
            //last uint8_t is CS
            calc_CS3 = CRC83(rx_buffer3, rx_len3);



            if (calc_CS3 == rx_buffer3[rx_array_inx3 - 1]) {//CS good

                // reassembles the data and places it into the receive array according to data address.
                int r;
                for (r = 0; r < rx_len3; r = r + 3) {
                    if (rx_buffer3[r] < maxDataAddress3) {
                        group3.parts[0] = rx_buffer3[r + 1];
                        group3.parts[1] = rx_buffer3[r + 2];
                        receiveArrayAddress3[(rx_buffer3[r])] = group3.integer;
                    } else {
                        dataAdressErrorCounter3++;
                    }
                }


                if (AKNAKsend3) { // if enabled sends an AK
                    unsigned char holder[3];
                    holder[0] = 255;
                    holder[1] = 1;
                    holder[2] = rx_buffer3[rx_array_inx3 - 1];
                    unsigned char crcHolder = CRC83(holder, 3);
                    serial_write3(0x06);
                    serial_write3(0x85);
                    serial_write3(returnAddress3);
                    serial_write3(moduleAddress3);
                    serial_write3(3);
                    serial_write3(255);
                    serial_write3(1);
                    serial_write3(rx_buffer3[rx_array_inx3 - 1]);
                    serial_write3(crcHolder);
                }



                rx_len3 = 0;
                rx_array_inx3 = 0;
                wipeRxBuffer3();
                //free(rx_buffer3);
                return true;
            } else {
                crcErrorCounter3++; //increments the counter every time a crc fails

                if (AKNAKsend3) { // if enabled sends NAK
                    unsigned char holder[3];
                    holder[0] = 255;
                    holder[1] = 2;
                    holder[2] = rx_buffer3[rx_array_inx3 - 1];
                    unsigned char crcHolder = CRC83(holder, 3);
                    serial_write3(0x06);
                    serial_write3(0x85);
                    serial_write3(returnAddress3);
                    serial_write3(moduleAddress3);
                    serial_write3(3);
                    serial_write3(255);
                    serial_write3(2);
                    serial_write3(rx_buffer3[rx_array_inx3 - 1]);
                    serial_write3(crcHolder);
                }

                //failed checksum, need to clear this out
                rx_len3 = 0;
                rx_array_inx3 = 0;
                wipeRxBuffer3();
               // free(rx_buffer3);
                return false;
            }
        }
    }


    return false;
}


// populates what info needs sent and to what data address

void ToSend3(unsigned char where, unsigned int what) {
    FastTransfer_buffer_put3(&ring_buffer3, where, what);
}


// disassembles the data and places it in a buffer to be sent

void FastTransfer_buffer_put3(struct ringBufS3 *_this, unsigned char towhere, unsigned int towhat) {

    group3.integer = towhat;

    if (_this->count < (BUFFER_SIZE - 3)) {
        _this->buf[_this->head] = towhere;
        _this->head = FastTransfer_buffer_modulo_inc3(_this->head, BUFFER_SIZE);
        ++_this->count;
        _this->buf[_this->head] = group3.parts[0];
        _this->head = FastTransfer_buffer_modulo_inc3(_this->head, BUFFER_SIZE);
        ++_this->count;
        _this->buf[_this->head] = group3.parts[1];
        _this->head = FastTransfer_buffer_modulo_inc3(_this->head, BUFFER_SIZE);
        ++_this->count;

    }

}


//pulls info out of the send buffer in a first in first out fashion

unsigned char FastTransfer_buffer_get3(struct ringBufS3* _this) {
    unsigned char c;
    if (_this->count > 0) {
        c = _this->buf[_this->tail];
        _this->tail = FastTransfer_buffer_modulo_inc3(_this->tail, BUFFER_SIZE);
        --_this->count;
    } else {
        c = 0;
    }
    return (c);
}

void *memset(void *s, int c, size_t n);

//flushes the send buffer to get it ready for new data

void FastTransfer_buffer_flush3(struct ringBufS3* _this, const int clearBuffer) {
    _this->count = 0;
    _this->head = 0;
    _this->tail = 0;
    if (clearBuffer) {
        memset(_this->buf, 0, sizeof (_this->buf));
    }
}


// increments counters for the buffer functions

unsigned int FastTransfer_buffer_modulo_inc3(const unsigned int value, const unsigned int modulus) {
    unsigned int my_value = value + 1;
    if (my_value >= modulus) {
        my_value = 0;
    }
    return (my_value);
}


//searches the buffer for the status of a message that was sent

unsigned char AKNAK3(unsigned char module) {
    int r;
    for (r = 0; r < CRC_COUNT; r++) {
        if (module == crcBufS_get3(&crc_buffer3, r, 0)) {
            return crcBufS_get3(&crc_buffer3, r, 2);
        }
    }
    return 4;
}


//returns align error

unsigned int alignError3(void) {
    return alignErrorCounter3;
}


//returns CRC error

unsigned int CRCError3(void) {
    return crcErrorCounter3;
}


//returns address error

unsigned int addressError3(void) {
    return addressErrorCounter3;
}

unsigned int dataAddressError3(void) {
    return dataAdressErrorCounter3;
}

// after a packet is sent records the info of that packet

void crcBufS_put3(struct crcBufS3* _this, unsigned char address, unsigned char oldCRC, unsigned char status) {
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

void crcBufS_status_put3(struct crcBufS3* _this, unsigned char time, unsigned char status) {
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

unsigned char crcBufS_get3(struct crcBufS3* _this, unsigned char time, unsigned char space) {
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

void CRCcheck3(void) {

    while (!(serial_available3() > 3)); // trap makes sure that there are enough bytes in the buffer for the AKNAK check

    unsigned char arrayHolder[3];
    arrayHolder[0] = serial_read3();
    arrayHolder[1] = serial_read3();
    arrayHolder[2] = serial_read3();
    unsigned char SentCRC = serial_read3();
    unsigned char calculatedCRC = CRC83(arrayHolder, 3);


    if (SentCRC == calculatedCRC) {

        int rt;
        for (rt = 0; rt < CRC_COUNT; rt++) {
            if (returnAddress3 == crcBufS_get3(&crc_buffer3, rt, 0)) {
                if (arrayHolder[2] == crcBufS_get3(&crc_buffer3, rt, 1)) {
                    if (arrayHolder[1] == 1) {
                        crcBufS_status_put3(&crc_buffer3, rt, 1);
                        break;
                    } else if (arrayHolder[1] == 2) {
                        crcBufS_status_put3(&crc_buffer3, rt, 2);
                        break;
                    }
                }
            }
        }
    } else {
        crcErrorCounter3++;
    } //increments the counter every time a crc fails
}

