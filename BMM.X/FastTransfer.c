#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "FastTransferPrivate.h"
#include "FastTransfer.h"
#include "PinDef.h"
#include "Function.h"


void wipeRxBuffer()
{
	int i=0;
	for(i=0;i<BUFFER_SIZE;i++)
	{
		rx_buffer[i]=0;
		
	}
	
}

//Captures address of receive array, the max data address, the address of the module, true/false if AKNAKs are wanted and the Serial address

void begin(char * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void), int (*stuffavailable)(void), unsigned char (*stuffpeek)(void)) {
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

//Sends out send buffer with a 2 start bytes, where the packet is going, where it came from, the size of the data packet, the data and the crc.

void sendData(unsigned char whereToSend) {
    //Enable RS485 TX
    
    //RS_RE_DE = 1;
    //calculate the crc
    unsigned char CS = CRC8(sendStructAddress, ring_buffer.count);

    serial_write(0x06); //start address
    serial_write(0x85); //start address
    serial_write(whereToSend);
    serial_write(moduleAddress);
    serial_write(ring_buffer.count); //length of packet not including the crc


    //send the rest of the packet
    int i;
    for (i = 0; i < ring_buffer.count; i++) {
        serial_write(*(sendStructAddress + i));
    }

    //send the crc
    serial_write(CS);

    Delay(1);
    //Disable RS485 TX
    //RS_RE_DE = 0;

    //record the sent message data for aknak check later
    crcBufS_put(&crc_buffer, whereToSend, CS, 0);

    // clears the buffer after a sending
    FastTransfer_buffer_flush(&ring_buffer, 1);

}

bool receiveData() {

    //start off by looking for the header bytes. If they were already found in a previous call, skip it.
    if (rx_len == 0) {
        //this size check may be redundant due to the size check below, but for now I'll leave it the way it is.
        if (serial_available() > 4) {
            //this will block until a 0x06 is found or buffer size becomes less then 3.
            while (serial_read() != 0x06) {
                //This will trash any preamble junk in the serial buffer
                //but we need to make sure there is enough in the buffer to process while we trash the rest
                //if the buffer becomes too empty, we will escape and try again on the next call
                alignErrorCounter++; //increments the counter whenever a byte is trashed
                if (serial_available() < 5)
                    return false;
            }
            
            if (serial_read() == 0x85) {
                
                rx_address = serial_read(); // pulls the address
                returnAddress = serial_read(); // pulls where the message came from
                rx_len = serial_read(); // pulls the length
                //make sure the address received is a match for this module if not throw the packet away
                if (rx_address != moduleAddress) {
                    addressErrorCounter++; // increments a counter whenever the wrong address is received
                    //if the address does not match the buffer is flushed for the size of
                    //the data packet plus one for the CRC
                    //int u;
                    //for (u = 0; u <= (rx_len + 1); u++)
                    //{
                    serial_read();
                    //}
                    rx_len = 0; // reset length
                    return false;
                }
                // if the address matches the a dynamic buffer is created to store the received data
                rx_buffer = (unsigned char*) malloc(rx_len + 1);
            }
        }
    }

    //we get here if we already found the header bytes, the address matched what we know, and now we are byte aligned.
    if (rx_len != 0) {

        //this check is preformed to see if the first data address is a 255, if it is then this packet is an AKNAK
        if (rx_array_inx == 0) {
            while (!(serial_available() >= 1));
            if (255 == serial_peek()) {
                CRCcheck();
                rx_len = 0;
                rx_array_inx = 0;
                free(rx_buffer);
                return receiveData();
            }
        }

        
        while (serial_available() && rx_array_inx <= rx_len) {
            rx_buffer[rx_array_inx++] = serial_read();
        }

        if (rx_len == (rx_array_inx - 1)) {
            //seem to have got whole message
            //last uint8_t is CS
            calc_CS = CRC8(rx_buffer, rx_len);


        INDICATOR = !INDICATOR;
            if (calc_CS == rx_buffer[rx_array_inx - 1]) {//CS good
                
                // reassembles the data and places it into the receive array according to data address.
                int r;
                for (r = 0; r < rx_len; r = r + 3) {
                    if (rx_buffer[r] < maxDataAddress) {
                        group.parts[0] = rx_buffer[r + 1];
                        group.parts[1] = rx_buffer[r + 2];
                        receiveArrayAddress[(rx_buffer[r])] = group.integer;
                    } else {
                        dataAdressErrorCounter++;
                    }
                }


                if (AKNAKsend) { // if enabled sends an AK
                    unsigned char holder[3];
                    holder[0] = 255;
                    holder[1] = 1;
                    holder[2] = rx_buffer[rx_array_inx - 1];
                    unsigned char crcHolder = CRC8(holder, 3);
                    serial_write(0x06);
                    serial_write(0x85);
                    serial_write(returnAddress);
                    serial_write(moduleAddress);
                    serial_write(3);
                    serial_write(255);
                    serial_write(1);
                    serial_write(rx_buffer[rx_array_inx - 1]);
                    serial_write(crcHolder);
                }



                rx_len = 0;
                rx_array_inx = 0;
                free(rx_buffer);
                return true;
            } else {
                crcErrorCounter++; //increments the counter every time a crc fails

                if (AKNAKsend) { // if enabled sends NAK
                    unsigned char holder[3];
                    holder[0] = 255;
                    holder[1] = 2;
                    holder[2] = rx_buffer[rx_array_inx - 1];
                    unsigned char crcHolder = CRC8(holder, 3);
                    serial_write(0x06);
                    serial_write(0x85);
                    serial_write(returnAddress);
                    serial_write(moduleAddress);
                    serial_write(3);
                    serial_write(255);
                    serial_write(2);
                    serial_write(rx_buffer[rx_array_inx - 1]);
                    serial_write(crcHolder);
                }

                //failed checksum, need to clear this out
                rx_len = 0;
                rx_array_inx = 0;
                free(rx_buffer);
                return false;
            }
        }
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






//#include <xc.h>
//#include <stdbool.h>
//#include <stdlib.h>
//#include "FastTransfer.h"
//#include "PinDef.h"
//
//
//
//
////Captures address of receive array, the max data address, the address of the module, true/false if AKNAKs are wanted and the Serial address
//
//void begin(volatile int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void), int (*stuffavailable)(void), unsigned char (*stuffpeek)(void)) {
//    receiveArrayAddress = ptr;
//    moduleAddress = givenAddress;
//    serial_write = stufftosend;
//    serial_available = stuffavailable;
//    serial_peek = stuffpeek;
//    serial_read = stufftoreceive;
//    maxDataAddress = maxSize / 2;
//    sendStructAddress = (unsigned char*) & ring_buffer;
//    AKNAKsend = error;
//    alignErrorCounter = 0;
//
//}
//
////CRC Calculator
//
//unsigned char CRC8(const unsigned char * data, unsigned char len) {
//    unsigned char crc = 0x00;
//    while (len--) {
//        unsigned char extract = *data++;
//        unsigned char tempI;
//        for (tempI = 8; tempI; tempI--) {
//            unsigned char sum = (crc ^ extract) & 0x01;
//            crc >>= 1;
//            if (sum) {
//                crc ^= polynomial;
//            }
//            extract >>= 1;
//        }
//    }
//    return crc;
//}
//
////Sends out send buffer with a 2 start bytes, where the packet is going, where it came from, the size of the data packet, the data and the crc.
//
//void sendData(unsigned char whereToSend) {
//    //Enable RS485 TX
//    RS_RE_DE = 1;
//    //calculate the crc
//    unsigned char CS = CRC8(sendStructAddress, ring_buffer.count);
//
//    serial_write(0x06); //start address
//    serial_write(0x85); //start address
//    serial_write(whereToSend);
//    serial_write(moduleAddress);
//    serial_write(ring_buffer.count); //length of packet not including the crc
//
//
//    //send the rest of the packet
//    int i;
//    for (i = 0; i < ring_buffer.count; i++) {
//        serial_write(*(sendStructAddress + i));
//    }
//
//    //send the crc
//    serial_write(CS);
//
//    Delay(1);
//    //Disable RS485 TX
//    RS_RE_DE = 0;
//
//    //record the sent message data for aknak check later
//    crcBufS_put(&crc_buffer, whereToSend, CS, 0);
//
//    // clears the buffer after a sending
//    FastTransfer_buffer_flush(&ring_buffer, 1);
//
//}
//
//bool receiveData() {
//
//    //start off by looking for the header bytes. If they were already found in a previous call, skip it.
//    if (rx_len == 0) {
//        //this size check may be redundant due to the size check below, but for now I'll leave it the way it is.
//        if (serial_available() > 4) {
//            //this will block until a 0x06 is found or buffer size becomes less then 3.
//            while (serial_read() != 0x06) {
//                //This will trash any preamble junk in the serial buffer
//                //but we need to make sure there is enough in the buffer to process while we trash the rest
//                //if the buffer becomes too empty, we will escape and try again on the next call
//                alignErrorCounter++; //increments the counter whenever a byte is trashed
//                if (serial_available() < 5)
//                    return false;
//            }
//            if (serial_read() == 0x85) {
//                rx_address = serial_read(); // pulls the address
//                returnAddress = serial_read(); // pulls where the message came from
//                rx_len = serial_read(); // pulls the length
//                //make sure the address received is a match for this module if not throw the packet away
//                if (rx_address != moduleAddress) {
//                    addressErrorCounter++; // increments a counter whenever the wrong address is received
//                    //if the address does not match the buffer is flushed for the size of
//                    //the data packet plus one for the CRC
//                    //int u;
//                    //for (u = 0; u <= (rx_len + 1); u++)
//                    //{
//                    serial_read();
//                    //}
//                    rx_len = 0; // reset length
//                    return false;
//                }
//                // if the address matches the a dynamic buffer is created to store the received data
//                rx_buffer = (unsigned char*) malloc(rx_len + 1);
//            }
//        }
//    }
//
//    //we get here if we already found the header bytes, the address matched what we know, and now we are byte aligned.
//    if (rx_len != 0) {
//
//        //this check is preformed to see if the first data address is a 255, if it is then this packet is an AKNAK
//        if (rx_array_inx == 0) {
//            while (!(serial_available() >= 1));
//            if (255 == serial_peek()) {
//                CRCcheck();
//                rx_len = 0;
//                rx_array_inx = 0;
//                free(rx_buffer);
//                return receiveData();
//            }
//        }
//
//
//        while (serial_available() && rx_array_inx <= rx_len) {
//            rx_buffer[rx_array_inx++] = serial_read();
//        }
//
//        if (rx_len == (rx_array_inx - 1)) {
//            //seem to have got whole message
//            //last uint8_t is CS
//            calc_CS = CRC8(rx_buffer, rx_len);
//
//
//
//            if (calc_CS == rx_buffer[rx_array_inx - 1]) {//CS good
//
//                // reassembles the data and places it into the receive array according to data address.
//                int r;
//                for (r = 0; r < rx_len; r = r + 3) {
//                    if (rx_buffer[r] < maxDataAddress) {
//                        group.parts[0] = rx_buffer[r + 1];
//                        group.parts[1] = rx_buffer[r + 2];
//                        receiveArrayAddress[(rx_buffer[r])] = group.integer;
//                    } else {
//                        dataAdressErrorCounter++;
//                    }
//                }
//
//
//                if (AKNAKsend) { // if enabled sends an AK
//                    unsigned char holder[3];
//                    holder[0] = 255;
//                    holder[1] = 1;
//                    holder[2] = rx_buffer[rx_array_inx - 1];
//                    unsigned char crcHolder = CRC8(holder, 3);
//                    serial_write(0x06);
//                    serial_write(0x85);
//                    serial_write(returnAddress);
//                    serial_write(moduleAddress);
//                    serial_write(3);
//                    serial_write(255);
//                    serial_write(1);
//                    serial_write(rx_buffer[rx_array_inx - 1]);
//                    serial_write(crcHolder);
//                }
//
//
//
//                rx_len = 0;
//                rx_array_inx = 0;
//                free(rx_buffer);
//                return true;
//            } else {
//                crcErrorCounter++; //increments the counter every time a crc fails
//
//                if (AKNAKsend) { // if enabled sends NAK
//                    unsigned char holder[3];
//                    holder[0] = 255;
//                    holder[1] = 2;
//                    holder[2] = rx_buffer[rx_array_inx - 1];
//                    unsigned char crcHolder = CRC8(holder, 3);
//                    serial_write(0x06);
//                    serial_write(0x85);
//                    serial_write(returnAddress);
//                    serial_write(moduleAddress);
//                    serial_write(3);
//                    serial_write(255);
//                    serial_write(2);
//                    serial_write(rx_buffer[rx_array_inx - 1]);
//                    serial_write(crcHolder);
//                }
//
//                //failed checksum, need to clear this out
//                rx_len = 0;
//                rx_array_inx = 0;
//                free(rx_buffer);
//                return false;
//            }
//        }
//    }
//
//
//    return false;
//}
//
//
//// populates what info needs sent and to what data address
//
//void ToSend(unsigned char where, unsigned int what) {
//    FastTransfer_buffer_put(&ring_buffer, where, what);
//}
//
//
//// disassembles the data and places it in a buffer to be sent
//
//void FastTransfer_buffer_put(struct ringBufS *_this, unsigned char towhere, unsigned int towhat) {
//
//    group.integer = towhat;
//
//    if (_this->count < (BUFFER_SIZE - 3)) {
//        _this->buf[_this->head] = towhere;
//        _this->head = FastTransfer_buffer_modulo_inc(_this->head, BUFFER_SIZE);
//        ++_this->count;
//        _this->buf[_this->head] = group.parts[0];
//        _this->head = FastTransfer_buffer_modulo_inc(_this->head, BUFFER_SIZE);
//        ++_this->count;
//        _this->buf[_this->head] = group.parts[1];
//        _this->head = FastTransfer_buffer_modulo_inc(_this->head, BUFFER_SIZE);
//        ++_this->count;
//
//    }
//
//}
//
//
////pulls info out of the send buffer in a first in first out fashion
//
//unsigned char FastTransfer_buffer_get(struct ringBufS* _this) {
//    unsigned char c;
//    if (_this->count > 0) {
//        c = _this->buf[_this->tail];
//        _this->tail = FastTransfer_buffer_modulo_inc(_this->tail, BUFFER_SIZE);
//        --_this->count;
//    } else {
//        c = 0;
//    }
//    return (c);
//}
//
//void *memset(void *s, int c, size_t n);
//
////flushes the send buffer to get it ready for new data
//
//void FastTransfer_buffer_flush(struct ringBufS* _this, const int clearBuffer) {
//    _this->count = 0;
//    _this->head = 0;
//    _this->tail = 0;
//    if (clearBuffer) {
//        memset(_this->buf, 0, sizeof (_this->buf));
//    }
//}
//
//
//// increments counters for the buffer functions
//
//unsigned int FastTransfer_buffer_modulo_inc(const unsigned int value, const unsigned int modulus) {
//    unsigned int my_value = value + 1;
//    if (my_value >= modulus) {
//        my_value = 0;
//    }
//    return (my_value);
//}
//
//
////searches the buffer for the status of a message that was sent
//
//unsigned char AKNAK(unsigned char module) {
//    int r;
//    for (r = 0; r < CRC_COUNT; r++) {
//        if (module == crcBufS_get(&crc_buffer, r, 0)) {
//            return crcBufS_get(&crc_buffer, r, 2);
//        }
//    }
//    return 4;
//}
//
//
////returns align error
//
//unsigned int alignError(void) {
//    return alignErrorCounter;
//}
//
//
////returns CRC error
//
//unsigned int CRCError(void) {
//    return crcErrorCounter;
//}
//
//
////returns address error
//
//unsigned int addressError(void) {
//    return addressErrorCounter;
//}
//
//unsigned int dataAddressError(void) {
//    return dataAdressErrorCounter;
//}
//
//// after a packet is sent records the info of that packet
//
//void crcBufS_put(struct crcBufS* _this, unsigned char address, unsigned char oldCRC, unsigned char status) {
//    _this->buf[_this->head] = address;
//    _this->head++;
//    _this->buf[_this->head] = oldCRC;
//    _this->head++;
//    _this->buf[_this->head] = status;
//    _this->head++;
//    if (_this->head >= CRC_BUFFER_SIZE) {
//        _this->head = 0;
//    }
//}
//
//
//// after a Ak or NAK is received that status is stored
//
//void crcBufS_status_put(struct crcBufS* _this, unsigned char time, unsigned char status) {
//    if (time >= CRC_COUNT) {
//        time = CRC_COUNT - 1;
//    }
//    time = time + 1;
//    int wantedTime = time * 3;
//    if (wantedTime > _this->head) {
//        wantedTime = (CRC_BUFFER_SIZE) - (wantedTime - _this->head);
//        _this->buf[(wantedTime + 2)] = status;
//    } else {
//        _this->buf[(_this->head - wantedTime) + 2] = status;
//    }
//}
//
//
//// pulls data from the AKNAK buffer
//
//unsigned char crcBufS_get(struct crcBufS* _this, unsigned char time, unsigned char space) {
//    if (time >= CRC_COUNT) {
//        time = CRC_COUNT - 1;
//    }
//    if (space >= CRC_DEPTH) {
//        space = CRC_DEPTH - 1;
//    }
//    time = time + 1;
//    int wantedTime = time * 3;
//    if (wantedTime > _this->head) {
//        wantedTime = (CRC_BUFFER_SIZE) - (wantedTime - _this->head);
//        return (_this->buf[(wantedTime + space)]);
//    } else {
//        return (_this->buf[(_this->head - wantedTime) + space]);
//    }
//}
//
//
////when an AK or NAK is received this compares it to the buffer and records the status
//
//void CRCcheck(void) {
//
//    while (!(serial_available() > 3)); // trap makes sure that there are enough bytes in the buffer for the AKNAK check
//
//    unsigned char arrayHolder[3];
//    arrayHolder[0] = serial_read();
//    arrayHolder[1] = serial_read();
//    arrayHolder[2] = serial_read();
//    unsigned char SentCRC = serial_read();
//    unsigned char calculatedCRC = CRC8(arrayHolder, 3);
//
//
//    if (SentCRC == calculatedCRC) {
//
//        int rt;
//        for (rt = 0; rt < CRC_COUNT; rt++) {
//            if (returnAddress == crcBufS_get(&crc_buffer, rt, 0)) {
//                if (arrayHolder[2] == crcBufS_get(&crc_buffer, rt, 1)) {
//                    if (arrayHolder[1] == 1) {
//                        crcBufS_status_put(&crc_buffer, rt, 1);
//                        break;
//                    } else if (arrayHolder[1] == 2) {
//                        crcBufS_status_put(&crc_buffer, rt, 2);
//                        break;
//                    }
//                }
//            }
//        }
//    } else {
//        crcErrorCounter++;
//    } //increments the counter every time a crc fails
//}
//
