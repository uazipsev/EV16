/* 
 * File:   FastTransfer.h
 * Author: Igor
 * Revised May 28, 2015 Zac Kilburn
 * Created on March 23, 2015, 1:21 PM
 */

#ifndef FASTTRANSFER_H
#define	FASTTRANSFER_H

//the capital D is so there is no interference with the lower case d of EasyTransfer
#define Details(name) (int*)&name,sizeof(name)

void begin(volatile int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void), int (*stuffavailable)(void), unsigned char (*stuffpeek)(void));
void sendData(unsigned char whereToSend);
bool receiveData();
void ToSend(const unsigned char where, const unsigned int what);
unsigned char AKNAK(unsigned char module);
unsigned int alignError(void);
unsigned int CRCError(void);
unsigned int addressError(void);
unsigned int dataAddressError(void);

void (*serial_write)(unsigned char);
unsigned char (*serial_read)(void);
int (*serial_available)(void);
unsigned char (*serial_peek)(void);
unsigned char rx_buffer[200]; //address for temporary storage and parsing buffer
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






#endif	/* FASTTRANSFER_H */

