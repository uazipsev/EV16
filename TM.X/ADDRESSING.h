/* 
 * File:   ADDRESSING.h
 * Author: Zac Kilburn
 *
 * Created on May 27, 2015, 5:35 PM
 */

#ifndef ADDRESSING_H
#define	ADDRESSING_H

#ifdef	__cplusplus
extern "C" {
#endif


#define CLOSE_COMM_TIME 7
#define BOARD_RESEND_MIN 25
#define BOARD_TIMEOUT 50
    //Addresses
#define ECU_ADDRESS 1
#define SAS_ADDRESS 2
#define DDS_ADDRESS 3
#define MCS_ADDRESS 4
#define PDU_ADDRESS 5
#define BMM_ADDRESS 6
#define TM_ADDRESS 7
    
#define TSS_1_ADDRESS 1
#define TSS_2_ADDRESS 2

#ifdef	__cplusplus
}
#endif

#endif	/* ADDRESSING_H */

