/* 
 * File:   SlaveAddressing.h
 * Author: User
 *
 * Created on June 10, 2015, 8:08 PM
 */

#ifndef SLAVEADDRESSING_H
#define	SLAVEADDRESSING_H

#ifdef	__cplusplus
extern "C" {
#endif

#define NUM_FAILS_TO_FAULT 4

#define NUMSLAVES    14
#define TEMPPERSLAVE 10
#define BATTPERSLAVE 10

#define BATTERYV    1
#define BATTERY1V   1
#define BATTERY2V   2
#define BATTERY3V   3
#define BATTERY4V   4
#define BATTERY5V   5
#define BATTERY6V   6
#define BATTERY7V   7
#define BATTERY8V   8
#define BATTERY9V   9
#define BATTERY10V  10

#define BATTERYT    11
#define BATTERY1T   11
#define BATTERY2T   12
#define BATTERY3T   13
#define BATTERY4T   14
#define BATTERY5T   15
#define BATTERY6T   16
#define BATTERY7T   17
#define BATTERY8T   18
#define BATTERY9T   19
#define BATTERY10T   20

#define SLAVE_ADDRESS_SEND 21
#define BATTERYFAULT 22
#define FAULTINGBATTERY 23

#define BATTERYV_ECU 31
#define BATTERYT_ECU 41


#define DDS_BMS_LED        5
#define DDS_ACTIVE_LED     3
#define DDS_IMD_INDICATOR  2
#define DDS_START_BUTTON   4
#define DDS_DEBUG_BUTTON   6

#ifdef	__cplusplus
}
#endif

#endif	/* SLAVEADDRESSING_H */

