/* 
 * File:   FastTransferPrivate.h
 * Author: richc
 *
 * Created on May 5, 2016, 8:04 PM
 */

#ifndef FASTTRANSFERPRIVATE_H
#define	FASTTRANSFERPRIVATE_H


void (*serial_write)(unsigned char);
unsigned char (*serial_read)(void);
int (*serial_available)(void);
unsigned char (*serial_peek)(void);
unsigned char * rx_buffer; //address for temporary storage and parsing buffer
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

void FastTransfer_buffer_put(struct ringBufS *_this, const unsigned char towhere, const unsigned int towhat);
unsigned char FastTransfer_buffer_get(struct ringBufS* _this);
void FastTransfer_buffer_flush(struct ringBufS* _this, const int clearBuffer);
unsigned int FastTransfer_buffer_modulo_inc(const unsigned int value, const unsigned int modulus);
void crcBufS_put(struct crcBufS* _this, unsigned char address, unsigned char oldCRC, unsigned char status);
void crcBufS_status_put(struct crcBufS* _this, unsigned char time, unsigned char status);
unsigned char crcBufS_get(struct crcBufS* _this, unsigned char time, unsigned char space);

#endif	/* FASTTRANSFERPRIVATE_H */

