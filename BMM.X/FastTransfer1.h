/* 
 * File:   FastTransfer1.h
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015, 2:09 PM
 */

#ifndef FASTTRANSFER1_H
#define	FASTTRANSFER1_H

#ifdef	__cplusplus
extern "C" {
#endif

    //the capital D is so there is no interference with the lower case d of EasyTransfer
#define Details(name) (int*)&name,sizeof(name)


#define polynomial 0x8C  //polynomial used to calculate crc
#define BUFFER_SIZE 400 //ring buffer size
#define CRC_COUNT 5 // how many AKNAKs are stored
#define CRC_DEPTH 3  // how many pieces of data are stored with each CRC send event
#define CRC_BUFFER_SIZE (CRC_COUNT * CRC_DEPTH) //crc buffer size 5 deep and 3 bytes an entry

    //PUBLIC METHODS/VARIABLES HERE
    void begin1(volatile int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void), int (*stuffavailable)(void), unsigned char (*stuffpeek)(void));
    void sendData1(unsigned char whereToSend);
    bool receiveData1();
    void ToSend1(const unsigned char where, const unsigned int what);

    volatile int receiveArray1[100];

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
    unsigned char * rx_buffer1; //address for temporary storage and parsing buffer
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









#ifdef	__cplusplus
}
#endif

#endif	/* FASTTRANSFER1_H */

