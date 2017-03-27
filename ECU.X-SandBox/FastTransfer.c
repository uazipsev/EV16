/*
 * File:   FastTransfer.c
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015
 */

#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "FastTransfer.h"
#include "UART.h"
#include "ADDRESSING.h"
#include "COBS.h"
#include "PinDef.h"
#include "Functions.h"

volatile int receiveArray[100];

void (*serial_write)(unsigned char);
unsigned char (*serial_read)(void);
int (*serial_available)(void);
unsigned char (*serial_peek)(void);
unsigned char rx_buffer[RX_BUFFER_SIZE]; //address for temporary storage and parsing buffer
unsigned char rx_array_inx; //index for RX parsing buffer
unsigned char rx_len; //RX packet length according to the packet
unsigned char calc_CS; //calculated Checksum
unsigned char moduleAddress; // the address of this module
unsigned char returnAddress; //the address to send the crc back to
unsigned char maxDataAddress; //max address allowable
volatile int * receiveArrayAddress; // this is where the data will go when it is received
unsigned char * sendStructAddress; // this is where the data will be sent from
bool AKNAKsend; // turns the acknowledged or not acknowledged on/off
unsigned int alignErrorCounter; //counts the align errors
unsigned int crcErrorCounter; // counts any failed crcs
unsigned int addressErrorCounter; // counts every time a wrong address is received
unsigned int dataAdressErrorCounter; // counts if the received data fall outside of the receive array
unsigned char rx_address; //RX address received

#define polynomial 0x8C  //polynomial used to calculate crc
#define BUFFER_SIZE 200 //ring buffer size
#define CRC_COUNT 5 // how many AKNAKs are stored
#define CRC_DEPTH 3  // how many pieces of data are stored with each CRC send event
#define CRC_BUFFER_SIZE (CRC_COUNT * CRC_DEPTH) //crc buffer size 5 deep and 3 bytes an entry

struct ringBufS { // this is where the send data is stored before sending
    unsigned char buf[BUFFER_SIZE];
    int head;
    int tail;
    int count;
};
struct ringBufS ring_buffer;

union stuff { // this union is used to join and disassemble integers
    unsigned char parts[2];
    unsigned int integer;
};
union stuff group;

struct crcBufS { // this is where the address where sent to, the sent crc, the status of the AKNAK
    unsigned char buf[CRC_BUFFER_SIZE];
    int head;
};
struct crcBufS crc_buffer;

unsigned char CRC8(const unsigned char * data, unsigned char len);
void FastTransfer_buffer_put(struct ringBufS *_this, const unsigned char towhere, const unsigned int towhat);
unsigned char FastTransfer_buffer_get(struct ringBufS* _this);
void FastTransfer_buffer_flush(struct ringBufS* _this, const int clearBuffer);
unsigned int FastTransfer_buffer_modulo_inc(const unsigned int value, const unsigned int modulus);
void crcBufS_put(struct crcBufS* _this, unsigned char address, unsigned char oldCRC, unsigned char status);
void crcBufS_status_put(struct crcBufS* _this, unsigned char time, unsigned char status);
unsigned char crcBufS_get(struct crcBufS* _this, unsigned char time, unsigned char space);
void CRCcheck(void);

unsigned int ReceiveArrayGet(int location){
    return receiveArray[location];
}

void wipeRxBuffer(void)
{
	int i=0;
	for(i=0;i<RX_BUFFER_SIZE;i++)
	{
		rx_buffer[i]=0;
		
	}
	
}

void StartFastTransfer(){
     begin(receiveArray, sizeof (receiveArray), ECU_ADDRESS, false, Send_put, Receive_get, Receive_available, Receive_peek);
}

//Captures address of receive array, the max data address, the address of the module, true/false if AKNAKs are wanted and the Serial address

void begin(volatile int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void), int (*stuffavailable)(void), unsigned char (*stuffpeek)(void)) {
    receiveArrayAddress = ptr;
    moduleAddress = givenAddress;
    serial_write = stufftosend;
    serial_available = stuffavailable;
    serial_peek = stuffpeek;
    serial_read = stufftoreceive;
    maxDataAddress = maxSize / 2;
    sendStructAddress = (unsigned char*) & ring_buffer;
    AKNAKsend = error;
    alignErrorCounter = 0;

}

//CRC Calculator

unsigned char CRC8(const unsigned char * data, unsigned char len) {
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

#define NUMOFEXTBYTES 4

COBS_ENCODE_DST_BUF_LEN_MAX = 30;
COBS_DECODE_DST_BUF_LEN_MAX = 30; 

//Sends out send buffer with a 2 start bytes, where the packet is going, where it came from, the size of the data packet, the data and the crc.

void sendData(unsigned char whereToSend, unsigned char ComandByte, unsigned char DataTable, unsigned char DataTableIndex) {

    
    //calculate the crc
    
    unsigned char SendArray[30];
    unsigned char COBSArray[30];
    
    unsigned char DataLenth = 2;
    
    cobs_encode_result  result;
    
    //SendArray[0] = whereToSend; //Address
   // SendArray[1] = 0x00; //start COBS
    SendArray[0] = NUMOFEXTBYTES+1;//ring_buffer.count; //start COBS
    SendArray[1] = ComandByte;
    SendArray[2] = DataTable;
    SendArray[3] = DataTableIndex;
    SendArray[4] = DataLenth;

    ring_buffer.count = 1;
    
    //send the rest of the packet
    int i;
    int count = 5;
    i = count;

        SendArray[count] = 0x11;//ring_buffer.buf[i];
        count++;
        SendArray[count] = 0x22;//ring_buffer.buf[i];
        //count++;

    unsigned char CS = CRC8(SendArray, count);
    //send the crc
  //  printf("CRC = %u\n",CS);
    
    SendArray[count++] = (CS);
   
//    for(i = 0;i<count;i++){
//        printf("%u ",SendArray[i]);
//    }
//    printf("\n");
    
    result = cobs_encode(COBSArray, sizeof(COBSArray), SendArray, count);
    
    SendArray[0] = whereToSend;
    
    for(i = 1;i<result.out_len+1;i++){
        SendArray[i] = COBSArray[i-1];
    }
    
    for(i = 0;i<result.out_len+2;i++){
        Send_put(SendArray[i]);
    }
}

 char ReciveArray[30];
 char ProcessArray[30];

bool receiveData() {
    if(Receive_available()>5){
        if(Receive_get() == ECU_ADDRESS){
            int i = 0;
            char Data = 0;
            do{
                Data = Receive_get();
                ReciveArray[i] = Data;
                DelayUS(100);
                i++;
            }while(Data != 0x00);
            
            cobs_decode_result result;

            result = cobs_decode(ProcessArray, sizeof(ProcessArray), ReciveArray, i);

            char CS = CRC8(ProcessArray, result.out_len-1);
            
            if(ProcessArray[result.out_len-1] == CS){
                INDICATOR ^= 1;
                return true;
            }
            else{
                Clear();
            }
        }
        else{
            //ClearBuffer();
        }
    }
    else{
       // ClearBuffer();
    }
    
    return false;
}


// populates what info needs sent and to what data address

void ToSend(unsigned char where, unsigned int what) {
    FastTransfer_buffer_put(&ring_buffer, where, what);
}


// disassembles the data and places it in a buffer to be sent

void FastTransfer_buffer_put(struct ringBufS *_this, unsigned char towhere, unsigned int towhat) {

    group.integer = towhat;

    if (_this->count < (BUFFER_SIZE - 3)) {
        _this->buf[_this->head] = towhere;
        _this->head = FastTransfer_buffer_modulo_inc(_this->head, BUFFER_SIZE);
        ++_this->count;
        _this->buf[_this->head] = group.parts[0];
        _this->head = FastTransfer_buffer_modulo_inc(_this->head, BUFFER_SIZE);
        ++_this->count;
        _this->buf[_this->head] = group.parts[1];
        _this->head = FastTransfer_buffer_modulo_inc(_this->head, BUFFER_SIZE);
        ++_this->count;

    }

}


//pulls info out of the send buffer in a first in first out fashion

unsigned char FastTransfer_buffer_get(struct ringBufS* _this) {
    unsigned char c;
    if (_this->count > 0) {
        c = _this->buf[_this->tail];
        _this->tail = FastTransfer_buffer_modulo_inc(_this->tail, BUFFER_SIZE);
        --_this->count;
    } else {
        c = 0;
    }
    return (c);
}

void *memset(void *s, int c, size_t n);

//flushes the send buffer to get it ready for new data

void FastTransfer_buffer_flush(struct ringBufS* _this, const int clearBuffer) {
    _this->count = 0;
    _this->head = 0;
    _this->tail = 0;
    if (clearBuffer) {
        memset(_this->buf, 0, sizeof (_this->buf));
    }
}


// increments counters for the buffer functions

unsigned int FastTransfer_buffer_modulo_inc(const unsigned int value, const unsigned int modulus) {
    unsigned int my_value = value + 1;
    if (my_value >= modulus) {
        my_value = 0;
    }
    return (my_value);
}


//searches the buffer for the status of a message that was sent

unsigned char AKNAK(unsigned char module) {
    int r;
    for (r = 0; r < CRC_COUNT; r++) {
        if (module == crcBufS_get(&crc_buffer, r, 0)) {
            return crcBufS_get(&crc_buffer, r, 2);
        }
    }
    return 4;
}


//returns align error

unsigned int alignError(void) {
    return alignErrorCounter;
}


//returns CRC error

unsigned int CRCError(void) {
    return crcErrorCounter;
}


//returns address error

unsigned int addressError(void) {
    return addressErrorCounter;
}

unsigned int dataAddressError(void) {
    return dataAdressErrorCounter;
}

// after a packet is sent records the info of that packet

void crcBufS_put(struct crcBufS* _this, unsigned char address, unsigned char oldCRC, unsigned char status) {
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

void crcBufS_status_put(struct crcBufS* _this, unsigned char time, unsigned char status) {
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

unsigned char crcBufS_get(struct crcBufS* _this, unsigned char time, unsigned char space) {
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

void CRCcheck(void) {

    while (!(serial_available() > 3)); // trap makes sure that there are enough bytes in the buffer for the AKNAK check

    unsigned char arrayHolder[3];
    arrayHolder[0] = serial_read();
    arrayHolder[1] = serial_read();
    arrayHolder[2] = serial_read();
    unsigned char SentCRC = serial_read();
    unsigned char calculatedCRC = CRC8(arrayHolder, 3);


    if (SentCRC == calculatedCRC) {

        int rt;
        for (rt = 0; rt < CRC_COUNT; rt++) {
            if (returnAddress == crcBufS_get(&crc_buffer, rt, 0)) {
                if (arrayHolder[2] == crcBufS_get(&crc_buffer, rt, 1)) {
                    if (arrayHolder[1] == 1) {
                        crcBufS_status_put(&crc_buffer, rt, 1);
                        break;
                    } else if (arrayHolder[1] == 2) {
                        crcBufS_status_put(&crc_buffer, rt, 2);
                        break;
                    }
                }
            }
        }
    } else {
        crcErrorCounter++;
    } //increments the counter every time a crc fails
}

