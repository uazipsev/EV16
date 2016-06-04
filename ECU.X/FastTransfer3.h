/* 
 * File:   FastTransfer3.h
 * Author: F
 *
 * Created on May 31, 2015, 2:09 PM
 */

#ifndef FASTTRANSFER3_H
#define	FASTTRANSFER3_H

#ifdef	__cplusplus
extern "C" {
#endif


#define RX_BUFFER_SIZE3 250
    //the capital D is so there is no interference with the lower case d of EasyTransfer
#define Details(name) (int*)&name,sizeof(name)


#define polynomial 0x8C  //polynomial used to calculate crc
#define BUFFER_SIZE 200 //ring buffer size
#define CRC_COUNT 5 // how many AKNAKs are stored
#define CRC_DEPTH 3  // how many pieces of data are stored with each CRC send event
#define CRC_BUFFER_SIZE (CRC_COUNT * CRC_DEPTH) //crc buffer size 5 deep and 3 bytes an entry

    //PUBLIC METHODS/VARIABLES HERE
    void begin3(volatile int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void), int (*stuffavailable)(void), unsigned char (*stuffpeek)(void));
    void sendData3(unsigned char whereToSend);
    bool receiveData3(void);
    void ToSend3(const unsigned char where, const unsigned int what);

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


#ifdef	__cplusplus
}
#endif

#endif	/* FASTTRANSFER3_H */

