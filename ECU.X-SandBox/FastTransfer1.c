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
#include "PinDef.h"

#include "COBS.h"

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

unsigned int ReceiveArray1Get(unsigned char location){
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

void sendData1(unsigned char whereToSend, unsigned char ComandByte, unsigned char DataTable, unsigned char DataTableIndex) {

    
    //calculate the crc
    
    unsigned char SendArray[30];
    unsigned char COBSArray[30];
    
    unsigned char DataLenth = 1;
    
    cobs_encode_result  result;
    
    //SendArray[0] = whereToSend; //Address
   // SendArray[1] = 0x00; //start COBS
    SendArray[0] = NUMOFEXTBYTES+1;//ring_buffer.count; //start COBS
    SendArray[1] = ComandByte;
    SendArray[2] = DataTable;
    SendArray[3] = DataTableIndex;
    SendArray[4] = DataLenth;

    //ring_buffer.count = 1;
    
    //send the rest of the packet
    int i;
    int count = 5;
    i = count;

        SendArray[count] = 0x11;//ring_buffer.buf[i];
        count++;
        SendArray[count] = 0x22;//ring_buffer.buf[i];
        count++;

    unsigned char CS = CRC8(SendArray, count);
    //send the crc
    //printf("CRC = %x\n",CS);
    
    SendArray[count++] = (CS);
   
   // for(i = 0;i<count;i++){
    //    printf("%x ",SendArray[i]);
    //}
    //printf("\n");
    
    result = cobs_encode(COBSArray, sizeof(COBSArray), SendArray, count);
    
    SendArray[0] = whereToSend;
    
    for(i = 1;i<result.out_len+1;i++){
        SendArray[i] = COBSArray[i-1];
    }
    
    for(i = 0;i<result.out_len+2;i++){
        Send_put1(SendArray[i]);
    }
}

 unsigned char ReciveArray1[30];
 unsigned char ProcessArray1[30];

bool receiveData1() {
    if(Receive_available1()>5){
        if(Receive_get1() == ECU_ADDRESS){
            int i = 0;
            unsigned char Data = 0;
            do{
                Data = Receive_get1();
                ReciveArray1[i] = Data;
                DelayUS(200);
                //printf("%u ",Data);
                i++;
            }while(Data != 0x00);

                        char d = 0;
//            for(d;d<i;d++){
//                printf("%u ",ProcessArray1[d]);
//            }
      //                  printf("\n"); 
            
            cobs_decode_result result;

            result = cobs_decode(ProcessArray1, sizeof(ProcessArray1), ReciveArray1, i);


//            for(d=0;d<result.out_len;d++){
//                printf("%u ",ProcessArray1[d]);
//            }
//            printf("\n"); 
            
            char CS = CRC8(ProcessArray1, result.out_len-1);
            
            //printf("CS = %i\n",CS); 
             
            if(ProcessArray1[result.out_len-1] == CS){
                INDICATOR ^= 1;

                return true;
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
        memset(_this->buf, 0, sizeof (_this->buf)); //TODO: this may be causing issues
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

