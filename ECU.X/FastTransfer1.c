/*
 * File:   FastTransfer1.c
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015
 */

#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "FastTransfer1.h"
#include "UART1.h"
#include "ADDRESSING.h"

volatile int receiveArray1[20];

//INTERNAL METHODS/VARIABLES HERE
unsigned char AKNAK1(unsigned char module);
unsigned int alignError1(void);
unsigned int CRCError1(void);
unsigned int addressError1(void);
unsigned int dataAddressError1(void);
void (*serial_write1)(unsigned char);
unsigned char (*serial_read1)(void);
int (*serial_available1)(void);
unsigned char (*serial_peek1)(void);
unsigned char rx_buffer1[RX_BUFFER_SIZE1]; //address for temporary storage and parsing buffer
unsigned char rx_array_inx1; //index for RX parsing buffer
unsigned char rx_len1; //RX packet length according to the packet
unsigned char calc_CS1; //calculated Checksum
unsigned char moduleAddress1; // the address of this module
unsigned char returnAddress1; //the address to send the crc back to
unsigned char maxDataAddress1; //max address allowable
volatile int * receiveArrayAddress1; // this is where the data will go when it is received
unsigned char * sendStructAddress1; // this is where the data will be sent from
bool AKNAKsend1; // turns the acknowledged or not acknowledged on/off
unsigned int alignErrorCounter1; //counts the align errors
unsigned int crcErrorCounter1; // counts any failed crcs
unsigned int addressErrorCounter1; // counts every time a wrong address is received
unsigned int dataAdressErrorCounter1; // counts if the received data fall outside of the receive array
unsigned char rx_address1; //RX address received

struct ringBufS1 { // this is where the send data is stored before sending
    unsigned char buf[BUFFER_SIZE];
    int head;
    int tail;
    int count;
};
struct ringBufS1 ring_buffer1;

union stuff1 { // this union is used to join and disassemble integers
    unsigned char parts[2];
    unsigned int integer;
};
union stuff1 group1;

struct crcBufS1 { // this is where the address where sent to, the sent crc, the status of the AKNAK
    unsigned char buf[CRC_BUFFER_SIZE];
    int head;
};
struct crcBufS1 crc_buffer1;

unsigned char CRC81(const unsigned char * data, unsigned char len);
void FastTransfer_buffer_put1(struct ringBufS1 *_this, const unsigned char towhere, const unsigned int towhat);
unsigned char FastTransfer_buffer_get1(struct ringBufS1* _this);
void FastTransfer_buffer_flush1(struct ringBufS1* _this, const int clearBuffer);
unsigned int FastTransfer_buffer_modulo_inc1(const unsigned int value, const unsigned int modulus);
void crcBufS_put1(struct crcBufS1* _this, unsigned char address, unsigned char oldCRC, unsigned char status);
void crcBufS_status_put1(struct crcBufS1* _this, unsigned char time, unsigned char status);
unsigned char crcBufS_get1(struct crcBufS1* _this, unsigned char time, unsigned char space);
void CRCcheck1(void);

void StartFastTransfer1(){
    begin1(receiveArray1, sizeof (receiveArray1), ECU_ADDRESS, false, Send_put1, Receive_get1, Receive_available1, Receive_peek1);
}

unsigned int ReceiveArray1Get(char location){
    return receiveArray1[location];
}

void wipeRxBuffer1(void)
{
	int i=0;
	for(i=0;i<RX_BUFFER_SIZE1;i++)
	{
		rx_buffer1[i]=0;
		
	}
	
}

//Captures address of receive array, the max data address, the address of the module, true/false if AKNAKs are wanted and the Serial address

void begin1(volatile int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void), int (*stuffavailable)(void), unsigned char (*stuffpeek)(void)) {
    receiveArrayAddress1 = ptr;
    moduleAddress1 = givenAddress;
    serial_write1 = stufftosend;
    serial_available1 = stuffavailable;
    serial_peek1 = stuffpeek;
    serial_read1 = stufftoreceive;
    maxDataAddress1 = maxSize / 2;
    sendStructAddress1 = (unsigned char*) & ring_buffer1;
    AKNAKsend1 = error;
    alignErrorCounter1 = 0;

}

//CRC Calculator

unsigned char CRC81(const unsigned char * data, unsigned char len) {
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

void sendData1(unsigned char whereToSend) {

    //calculate the crc
    unsigned char CS = CRC81(sendStructAddress1, ring_buffer1.count);

    serial_write1(0x06); //start address
    serial_write1(0x85); //start address
    serial_write1(whereToSend);
    serial_write1(moduleAddress1);
    serial_write1(ring_buffer1.count); //length of packet not including the crc


    //send the rest of the packet
    int i;
    for (i = 0; i < ring_buffer1.count; i++) {
        serial_write1(*(sendStructAddress1 + i));
    }

    //send the crc
    serial_write1(CS);

    //record the sent message data for aknak check later
   // crcBufS_put1(&crc_buffer1, whereToSend, CS, 0);

    // clears the buffer after a sending
    FastTransfer_buffer_flush1(&ring_buffer1, 0);

}

bool receiveData1() {

    //start off by looking for the header bytes. If they were already found in a previous call, skip it.
    if (rx_len1 == 0) {
        //this size check may be redundant due to the size check below, but for now I'll leave it the way it is.
        if (serial_available1() > 4) {
            //this will block until a 0x06 is found or buffer size becomes less then 3.
            while (serial_read1() != 0x06) {
                //This will trash any preamble junk in the serial buffer
                //but we need to make sure there is enough in the buffer to process while we trash the rest
                //if the buffer becomes too empty, we will escape and try again on the next call
                alignErrorCounter1++; //increments the counter whenever a byte is trashed
                if (serial_available1() < 5)
                    return false;
            }
            if (serial_read1() == 0x85) {
                rx_address1 = serial_read1(); // pulls the address
                returnAddress1 = serial_read1(); // pulls where the message came from
                rx_len1 = serial_read1(); // pulls the length
                //make sure the address received is a match for this module if not throw the packet away
                if (rx_address1 != moduleAddress1) {
                    addressErrorCounter1++; // increments a counter whenever the wrong address is received
                    //if the address does not match the buffer is flushed for the size of
                    //the data packet plus one for the CRC
                    //int u;
                    //for (u = 0; u <= (rx_len1 + 1); u++) {
                    //serial_read1();
                    //}
                    rx_len1 = 0; // reset length
                    return false;
                }
                // if the address matches the a dynamic buffer is created to store the received data
                //rx_buffer1 = (unsigned char*) malloc(rx_len1 + 1);
            }
        }
    }

    //we get here if we already found the header bytes, the address matched what we know, and now we are byte aligned.
    if (rx_len1 != 0) {

        //this check is preformed to see if the first data address is a 255, if it is then this packet is an AKNAK
        if (rx_array_inx1 == 0) {
//            while (!(serial_available1() >= 1));
//            if (255 == serial_peek1()) {
//                CRCcheck1();
//                rx_len1 = 0;
//                rx_array_inx1 = 0;
//                wipeRxBuffer1();
//                //free(rx_buffer1);
//                return receiveData1();
//            }
        }


        while (serial_available1() && rx_array_inx1 <= rx_len1) {
            rx_buffer1[rx_array_inx1++] = serial_read1();
        }

        if (rx_len1 == (rx_array_inx1 - 1)) {
            //seem to have got whole message
            //last uint8_t is CS
            calc_CS1 = CRC81(rx_buffer1, rx_len1);



            if (calc_CS1 == rx_buffer1[rx_array_inx1 - 1]) {//CS good

                // reassembles the data and places it into the receive array according to data address.
                int r;
                for (r = 0; r < rx_len1; r = r + 3) {
                    if (rx_buffer1[r] < maxDataAddress1) {
                        group1.parts[0] = rx_buffer1[r + 1];
                        group1.parts[1] = rx_buffer1[r + 2];
                        receiveArrayAddress1[(rx_buffer1[r])] = group1.integer;
                    } else {
                        dataAdressErrorCounter1++;
                    }
                }


                if (AKNAKsend1) { // if enabled sends an AK
                    unsigned char holder[3];
                    holder[0] = 255;
                    holder[1] = 1;
                    holder[2] = rx_buffer1[rx_array_inx1 - 1];
                    unsigned char crcHolder = CRC81(holder, 3);
                    serial_write1(0x06);
                    serial_write1(0x85);
                    serial_write1(returnAddress1);
                    serial_write1(moduleAddress1);
                    serial_write1(3);
                    serial_write1(255);
                    serial_write1(1);
                    serial_write1(rx_buffer1[rx_array_inx1 - 1]);
                    serial_write1(crcHolder);
                }



                rx_len1 = 0;
                rx_array_inx1 = 0;
                wipeRxBuffer1();
                //free(rx_buffer1);
                return true;
            } else {
                crcErrorCounter1++; //increments the counter every time a crc fails

                if (AKNAKsend1) { // if enabled sends NAK
                    unsigned char holder[3];
                    holder[0] = 255;
                    holder[1] = 2;
                    holder[2] = rx_buffer1[rx_array_inx1 - 1];
                    unsigned char crcHolder = CRC81(holder, 3);
                    serial_write1(0x06);
                    serial_write1(0x85);
                    serial_write1(returnAddress1);
                    serial_write1(moduleAddress1);
                    serial_write1(3);
                    serial_write1(255);
                    serial_write1(2);
                    serial_write1(rx_buffer1[rx_array_inx1 - 1]);
                    serial_write1(crcHolder);
                }

                //failed checksum, need to clear this out
                rx_len1 = 0;
                rx_array_inx1 = 0;
                wipeRxBuffer1();
                //free(rx_buffer1);
                return false;
            }
        }
    }


    return false;
}


// populates what info needs sent and to what data address

void ToSend1(unsigned char where, unsigned int what) {
    FastTransfer_buffer_put1(&ring_buffer1, where, what);
}


// disassembles the data and places it in a buffer to be sent

void FastTransfer_buffer_put1(struct ringBufS1 *_this, unsigned char towhere, unsigned int towhat) {

    group1.integer = towhat;

    if (_this->count < (BUFFER_SIZE - 3)) {
        _this->buf[_this->head] = towhere;
        _this->head = FastTransfer_buffer_modulo_inc1(_this->head, BUFFER_SIZE);
        ++_this->count;
        _this->buf[_this->head] = group1.parts[0];
        _this->head = FastTransfer_buffer_modulo_inc1(_this->head, BUFFER_SIZE);
        ++_this->count;
        _this->buf[_this->head] = group1.parts[1];
        _this->head = FastTransfer_buffer_modulo_inc1(_this->head, BUFFER_SIZE);
        ++_this->count;

    }

}


//pulls info out of the send buffer in a first in first out fashion

unsigned char FastTransfer_buffer_get1(struct ringBufS1* _this) {
    unsigned char c;
    if (_this->count > 0) {
        c = _this->buf[_this->tail];
        _this->tail = FastTransfer_buffer_modulo_inc1(_this->tail, BUFFER_SIZE);
        --_this->count;
    } else {
        c = 0;
    }
    return (c);
}

void *memset(void *s, int c, size_t n);

//flushes the send buffer to get it ready for new data

void FastTransfer_buffer_flush1(struct ringBufS1* _this, const int clearBuffer) {
    _this->count = 0;
    _this->head = 0;
    _this->tail = 0;
    if (clearBuffer) {
        //memset(_this->buf, 0, sizeof (_this->buf)); //TODO: this may be causing issues
    }
}


// increments counters for the buffer functions

unsigned int FastTransfer_buffer_modulo_inc1(const unsigned int value, const unsigned int modulus) {
    unsigned int my_value = value + 1;
    if (my_value >= modulus) {
        my_value = 0;
    }
    return (my_value);
}


//searches the buffer for the status of a message that was sent

unsigned char AKNAK1(unsigned char module) {
    int r;
    for (r = 0; r < CRC_COUNT; r++) {
        if (module == crcBufS_get1(&crc_buffer1, r, 0)) {
            return crcBufS_get1(&crc_buffer1, r, 2);
        }
    }
    return 4;
}


//returns align error

unsigned int alignError1(void) {
    return alignErrorCounter1;
}


//returns CRC error

unsigned int CRCError1(void) {
    return crcErrorCounter1;
}


//returns address error

unsigned int addressError1(void) {
    return addressErrorCounter1;
}

unsigned int dataAddressError1(void) {
    return dataAdressErrorCounter1;
}

// after a packet is sent records the info of that packet

void crcBufS_put1(struct crcBufS1* _this, unsigned char address, unsigned char oldCRC, unsigned char status) {
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

void crcBufS_status_put1(struct crcBufS1* _this, unsigned char time, unsigned char status) {
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

unsigned char crcBufS_get1(struct crcBufS1* _this, unsigned char time, unsigned char space) {
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

void CRCcheck1(void) {

    while (!(serial_available1() > 3)); // trap makes sure that there are enough bytes in the buffer for the AKNAK check

    unsigned char arrayHolder[3];
    arrayHolder[0] = serial_read1();
    arrayHolder[1] = serial_read1();
    arrayHolder[2] = serial_read1();
    unsigned char SentCRC = serial_read1();
    unsigned char calculatedCRC = CRC81(arrayHolder, 3);


    if (SentCRC == calculatedCRC) {

        int rt;
        for (rt = 0; rt < CRC_COUNT; rt++) {
            if (returnAddress1 == crcBufS_get1(&crc_buffer1, rt, 0)) {
                if (arrayHolder[2] == crcBufS_get1(&crc_buffer1, rt, 1)) {
                    if (arrayHolder[1] == 1) {
                        crcBufS_status_put1(&crc_buffer1, rt, 1);
                        break;
                    } else if (arrayHolder[1] == 2) {
                        crcBufS_status_put1(&crc_buffer1, rt, 2);
                        break;
                    }
                }
            }
        }
    } else {
        crcErrorCounter1++;
    } //increments the counter every time a crc fails
}

