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


    //Addresses
#define ECU_ADDRESS 1
#define SAS_ADDRESS 2
#define DDS_ADDRESS 3
#define MCS_ADDRESS 4
#define PDU_ADDRESS 5
#define BMM_ADDRESS 6
#define TM_ADDRESS 7

    //ECU Data
#define RESPONSE_ADDRESS        0
#define THROTTLE1_SAS           1
#define THROTTLE2_SAS           2
#define BRAKE_SAS               3
#define WHEELSPEED1_SAS         4
#define WHEELSPEED2_SAS         5
#define WHEELSPEED3_SAS         6
#define WHEELSPEED4_SAS         7
#define BUTTONS_DDS             8
#define POWER_STATE             9
#define MCS_FAULT               10
#define DDS_FAULT               11
#define PDU_FAULT               12
#define SAS_FAULT               13
#define BMM_FAULT               14

    //MCS Receive
#define THROTTLE_OUTPUT         1
#define BRAKE_OUTPUT            2
#define OUTPUT_ACTIVE           3

    //PDU Receive
#define POWER_RAILS             1

    //SAS Receive
#define SIGNAL_REQUEST          1
#define WHEELSPEED_REQUEST      2

    //DDS Receive
#define BUTTON_REQUEST          1
#define LED_DDS                 2
#define THROTTLE_DDS            3
#define BRAKE_DDS               4

    //BMM Receive
#define BMM_COMM_STATE          1



#define DEBUG_ADDRESS 9

#define BUS_1_ERROR_DEBUG       1
#define BUS_2_ERROR_DEBUG       2

#define TALK 1
#define LISTEN 0

#ifdef	__cplusplus
}
#endif

#endif	/* ADDRESSING_H */

