/* 
 * File:   cam-m8.h
 * Author: Rick
 *
 * Created on August 14, 2015, 12:28 AM
 */

#ifndef CAM_M8_H
#define	CAM_M8_H

struct GPS_Data {
    unsigned int Hours; // 7 bit address
    unsigned int Minutes; // pin used for sda coresponds to gpio
    unsigned int Seconds; // clock
    float Latitude; // proportional to bus speed
    float Longitude;
	int Altitude;
	int Satellites;			// For serial port GPS
    int Speed;
    int Direction;
	
};

void CamM8Init();
int CamM8Read();
void setGPS_GNSS();
float FixPosition(float Position);
void ProcessLine(struct GPS_Data *GPS, char *Buffer, int Count);
void CamM8CRC(char *Message, int len);
int CamM8CRCCheck(char *Message, int Count);
void SendUBX(char *MSG, int len);
void PrintGPSData();
void SetCarMode();
void SetPowerMode();

//Start info

#define GPS_START 0xB562

//CFG Info

#define UBX_CFG_PRT 0x0600
#define UBX_CFG_MSG 0x0601
#define UBX_CFG_INF 0x0602
#define UBX_CFG_RST 0x0604
#define UBX_CFG_DAT 0x0606
#define UBX_CFG_RATE 0x0608
#define UBX_CFG_CFG 0x0609
#define UBX_CFG_ANT 0x0613
#define UBX_CFG_NMEA 0x0617
#define UBX_CFG_ODO 0x061E
#define UBX_CFG_SBAS 0x0001

#define UBX_CFG_TMODE2 0x0001
#define UBX_CFG_GNSS 0x0001
#define UBX_CFG_TP5 0x0001
#define UBX_CFG_NAVX5 0x0623
#define UBX_CFG_RXM 0x0001
#define UBX_CFG_PM2 0x063B
#define UBX_CFG_PMS 0x0686
#define UBX_CFG_PWR 0x0657
#define UBX_CFG_ITFM 0x0001
#define UBX_CFG_RINV 0x0634
#define UBX_CFG_LOGFILTER 0x0001
#define UBX_CFG_DOSC 0x0661
#define UBX_CFG_ESRC 0x0660
#define UBX_CFG_SMGR 0x0001
#define UBX_CFG_SWI2C 0x0001
#define UBX_CFG_SWI2CDAC 0x0001

#define UBX_ACK_ACK 0x0501
#define UBX_ACK_NAK 0x0500

//Talker ID's

#define Talker_ID_GPS 0x4750        //GP
#define Talker_ID_GLONASS 0x474C    //GL
#define Talker_ID_GALILEO 0x4741    //GA
#define Talker_ID_BEIDOU 0x4742     //GB
#define Talker_ID_GNSS_COMBO 0x474E //GN

//NMEA Message Mnemonic

#define DTM 0xF00A
#define GBQ 0xF044
#define GBS 0xF009
#define GGA 0xF000
#define GLL 0xF001
#define GLQ 0xF043
#define GNQ 0xF042
#define GNS 0xF00D
#define GPQ 0xF040
#define GRS 0xF006
#define GSA 0xF002
#define GST 0xF007
#define GSV 0xF003
#define RMC 0xF004
#define TXT 0xF041
#define VLW 0xF00F
#define VTG 0xF005
#define ZDA 0xF008

//NMEA PUBx Messages

#define CONFIG 0xF141
#define POSITION 0xF100
#define RATE 0xF140
#define SVSTATUS 0xF103
//#define TIME 0xF104







#endif	/* CAM_M8_H */

