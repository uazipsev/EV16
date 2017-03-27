/* 
 * File:   FastTransfer2.h
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015, 2:09 PM
 */

#ifndef FASTTRANSFER2_H
#define	FASTTRANSFER2_H

#ifdef	__cplusplus
extern "C" {
#endif

#define RX_BUFFER_SIZE2 250
    //the capital D is so there is no interference with the lower case d of EasyTransfer
#define Details(name) (int*)&name,sizeof(name)


#define polynomial 0x8C  //polynomial used to calculate crc
#define BUFFER_SIZE 200 //ring buffer size
#define CRC_COUNT 5 // how many AKNAKs are stored
#define CRC_DEPTH 3  // how many pieces of data are stored with each CRC send event
#define CRC_BUFFER_SIZE (CRC_COUNT * CRC_DEPTH) //crc buffer size 5 deep and 3 bytes an entry

    //PUBLIC METHODS/VARIABLES HERE
    void begin2(volatile int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void), int (*stuffavailable)(void), unsigned char (*stuffpeek)(void));
    void sendData2(unsigned char whereToSend);
    char receiveData2(void);
    void ToSend2(const unsigned char where, const unsigned int what);

    volatile int receiveArray2[20];

    //INTERNAL METHODS/VARIABLES HERE
    unsigned char AKNAK2(unsigned char module);
    unsigned int alignError2(void);
    unsigned int CRCError2(void);
    unsigned int addressError2(void);
    unsigned int dataAddressError1(void);
    void (*serial_write2)(unsigned char);
    unsigned char (*serial_read2)(void);
    int (*serial_available2)(void);
    unsigned char (*serial_peek2)(void);
    unsigned char rx_buffer2[RX_BUFFER_SIZE2]; //address for temporary storage and parsing buffer
    unsigned char rx_array_inx2; //index for RX parsing buffer
    unsigned char rx_len2; //RX packet length according to the packet
    unsigned char calc_CS2; //calculated Checksum
    unsigned char moduleAddress2; // the address of this module
    unsigned char returnAddress2; //the address to send the crc back to
    unsigned char maxDataAddress2; //max address allowable
    volatile int * receiveArrayAddress2; // this is where the data will go when it is received
    unsigned char * sendStructAddress2; // this is where the data will be sent from
    bool AKNAKsend2; // turns the acknowledged or not acknowledged on/off
    unsigned int alignErrorCounter2; //counts the align errors
    unsigned int crcErrorCounter2; // counts any failed crcs
    unsigned int addressErrorCounter2; // counts every time a wrong address is received
    unsigned int dataAdressErrorCounter2; // counts if the received data fall outside of the receive array
    unsigned char rx_address2; //RX address received

    struct ringBufS2 { // this is where the send data is stored before sending
        unsigned char buf[BUFFER_SIZE];
        int head;
        int tail;
        int count;
    };
    struct ringBufS2 ring_buffer2;

    union stuff2 { // this union is used to join and disassemble integers
        unsigned char parts[2];
        unsigned int integer;
    };
    union stuff2 group2;

    struct crcBufS2 { // this is where the address where sent to, the sent crc, the status of the AKNAK
        unsigned char buf[CRC_BUFFER_SIZE];
        int head;
    };
    struct crcBufS2 crc_buffer2;

    unsigned char CRC82(const unsigned char * data, unsigned char len);
    void FastTransfer_buffer_put2(struct ringBufS2 *_this, const unsigned char towhere, const unsigned int towhat);
    unsigned char FastTransfer_buffer_get2(struct ringBufS2* _this);
    void FastTransfer_buffer_flush2(struct ringBufS2* _this, const int clearBuffer);
    unsigned int FastTransfer_buffer_modulo_inc2(const unsigned int value, const unsigned int modulus);
    void crcBufS_put2(struct crcBufS2* _this, unsigned char address, unsigned char oldCRC, unsigned char status);
    void crcBufS_status_put2(struct crcBufS2* _this, unsigned char time, unsigned char status);
    unsigned char crcBufS_get2(struct crcBufS2* _this, unsigned char time, unsigned char space);
    void CRCcheck2(void);



#ifdef	__cplusplus
}
#endif

#endif	/* FASTTRANSFER2_H */

