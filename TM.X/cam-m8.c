/******************
*   CAM-m8Q
*   Derived from PiInTheSky - https://github.com/PiInTheSky/pits/tree/master/tracker
* 
*****************/
#include "cam-m8.h"
#include "UART4.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Functions.h"

char GPSArray[100];

void CamM8Init(){
    UART4_init();
    Delay(1);
    SetCarMode();
    Delay(1);
    setGPS_GNSS();
    Delay(1);
    SetPowerMode();
}

int length = 0;
struct GPS_Data *GPS_Storred;
    
int CamM8Read(){
    char Data = Receive_get4();
    
    if(Data == 0xFF){
        return 0;
    }
    else if(Data == 0x00){
        return 0;
    }
    else if(Data == '$'){
        //printf("$");
        GPSArray[0] = Data;
        length = 1;
    }
    else if(length > 90){
        length = 0;
    }
    else if((length >= 1) && (Data != '\r')){
        GPSArray[length++] = Data;
        //printf("%c",Data);
        if(Data == '\n'){
            UART4_Clear();
            //printf("DataPacket");
            ProcessLine(GPS_Storred, GPSArray, length);
            length = 0;
        }
    }
}

void SetCarMode()
{
    // Send navigation configuration command
    char setNav[] = {0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x05, 0x00, 0xFA, 0x00, 0xFA, 0x00, 0x64, 0x00, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0xDC};
    CamM8CRCCheck(setNav,sizeof(setNav));
    SendUBX(setNav, sizeof(setNav));
	printf ("Setting flight mode\n");
}

void SetPowerMode()
{
    char SavePower = 1;
	char setPSM[] = {0xB5, 0x62, 0x06, 0x11, 0x02, 0x00, 0x08, 0x01, 0x22, 0x92 };
	setPSM[7] = SavePower ? 1 : 0;
	printf ("Setting power-saving %s\n", SavePower ? "ON" : "OFF");
	CamM8CRC(setPSM, sizeof(setPSM));
	SendUBX(setPSM, sizeof(setPSM));
}

void setGPS_GNSS()
{
  // Sets CFG-GNSS to disable everything other than GPS GNSS
  // solution. Failure to do this means GPS power saving 
  // doesn't work. Not needed for MAX7, needed for MAX8's
	char setgnss[] = {
    0xB5, 0x62, 0x06, 0x3E, 0x2C, 0x00, 0x00, 0x00,
    0x20, 0x05, 0x00, 0x08, 0x10, 0x00, 0x01, 0x00,
    0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00,
    0x01, 0x01, 0x03, 0x08, 0x10, 0x00, 0x00, 0x00,
    0x01, 0x01, 0x05, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x01, 0x01, 0x06, 0x08, 0x0E, 0x00, 0x00, 0x00,
    0x01, 0x01, 0xFC, 0x11   };

	printf ("Disabling GNSS\n");

    SendUBX(setgnss, sizeof(setgnss));
}

void SendUBX(char *MSG, int len)
{
    int i = 0;
    while(len != 0){
        Send_put4(MSG[i]);
        i++;
        len--;
    }

}

int CamM8CRCCheck(char *Message, int Count)
{
  unsigned char XOR, i, c;

  XOR = 0;
  for (i = 1; i < (Count-4); i++)
  {
    c = Message[i];
    XOR ^= c;
  }

  //return (Message[Count-4] == '*') && (Message[Count-3] == Hex(XOR >> 4)) && (Message[Count-2] == Hex(XOR & 15));
  return 1;
}

void CamM8CRC(char *Message, int len)
{ 
  int i;
  unsigned char CK_A, CK_B;
  
  CK_A = 0;
  CK_B = 0;

  for (i=2; i<(len-2); i++)
  {
    CK_A = CK_A + Message[i];
    CK_B = CK_B + CK_A;
  }
  
  Message[len-2] = CK_A;
  Message[len-1] = CK_B;
}

float FixPosition(float Position)
{
//	float Minutes, Seconds;
//	
//	Position = Position / 100;
//	
//	//Minutes = trunc(Position);
//	Seconds = fmod(Position, 1);
//
//	return Minutes + Seconds * 5 / 3;
}

void ProcessLine(struct GPS_Data *GPS, char *Buffer, int Count)
{
	static int SystemTimeHasBeenSet=0;
	
    float utc_time, latitude, longitude, hdop, altitude;
	int lock, satellites;
	char active, ns, ew, units, timestring[16], speedstring[16] , restofline[80], *ptr, *date, *course;
	int MessageCount = 0;
    if (CamM8CRCCheck(Buffer, Count))
	{
		satellites = 0;
	
		if (strncmp(Buffer+5, "GPGGA", 5) == 0)
		{
			MessageCount++;
			if (sscanf(Buffer+7, "%f,%f,%c,%f,%c,%d,%d,%f,%f,%c", &utc_time, &latitude, &ns, &longitude, &ew, &lock, &satellites, &hdop, &altitude, &units) >= 1)
			{	
				// $GPGGA,124943.00,5157.01557,N,00232.66381,W,1,09,1.01,149.3,M,48.6,M,,*42
				if (satellites >= 2)
				{
                    printf("Data-GGA");
					unsigned long utc_seconds;
					utc_seconds = utc_time;
					GPS->Hours = utc_seconds / 10000;
					GPS->Minutes = (utc_seconds / 100) % 100;
					GPS->Seconds = utc_seconds % 100;
					GPS->Latitude = FixPosition(latitude);
					if (ns == 'S') GPS->Latitude = -GPS->Latitude;
					GPS->Longitude = FixPosition(longitude);
					if (ew == 'W') GPS->Longitude = -GPS->Longitude;
					
//					if (GPS->Altitude <= 0)
//					{
//						//GPS->AscentRate = 0;
//					}
//					else
//					{
//						//GPS->AscentRate = GPS->AscentRate * 0.7 + ((int32_t)altitude - GPS->Altitude) * 0.3;
//					}
					// printf("Altitude=%ld, AscentRate = %.1lf\n", GPS->Altitude, GPS->AscentRate);
					GPS->Altitude = altitude;
					//if (GPS->Altitude > GPS->MaximumAltitude) GPS->MaximumAltitude = GPS->Altitude;
				}
				GPS->Satellites = satellites;
			}
                //printf("GPS\n");
            printf("H:%i M:%i\n",GPS->Hours,GPS->Minutes);
            printf("LAT:%f LONG:%f\n",GPS->Latitude,GPS->Longitude);
            printf("Sat Fixes = %c\n",GPS->Satellites);

		}
		else if (strncmp(Buffer+3, "RMC", 3) == 0)
		{
			speedstring[0] = '\0';
			if (sscanf(Buffer+7, "%[^,],%c,%f,%c,%f,%c,%[^,],%s", timestring, &active, &latitude, &ns, &longitude, &ew, speedstring, restofline) >= 7)
			{			
                printf("Data-RMC");
				// $GPRMC,124943.00,A,5157.01557,N,00232.66381,W,0.039,,200314,,,A*6C
                  
//				ptr = restofline;
//				
//				course = strsep(&ptr, ",");
//
//				date = strsep(&ptr, ",");
//				
//				GPS->Speed = (int)atof(speedstring);
//				GPS->Direction = (int)atof(course);

//				if ((atof(timestring) > 0) && !SystemTimeHasBeenSet)
//				{
//					struct tm tm;
//					char timedatestring[32];
//					//time_t t;
//
//					// Now create a tm structure from our date and time
//					memset(&tm, 0, sizeof(struct tm));
//					sprintf(timedatestring, "%c%c-%c%c-20%c%c %c%c:%c%c:%c%c",
//											date[0], date[1], date[2], date[3], date[4], date[5],
//											timestring[0], timestring[1], timestring[2], timestring[3], timestring[4], timestring[5]);
//					//strptime(timedatestring, "%d-%m-%Y %H:%M:%S", &tm);
//				
//					t = mktime(&tm);
//					if (stime(&t) == -1)
//					{
//						printf("Failed to set system time\n");
//					}
//					else
//					{
//						printf("System time set from GPS time\n");
//						SystemTimeHasBeenSet = 1;
//					}
//				}
			}

		}
		else if (strncmp(Buffer+3, "GSV", 3) == 0)
        {
            // Disable GSV
            printf("Disabling GSV\r\n");
            char setGSV[] = { 0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x39 };
            SendUBX(setGSV, sizeof(setGSV));
        }
		else if (strncmp(Buffer+3, "GLL", 3) == 0)
        {
            // Disable GLL
            printf("Disabling GLL\r\n");
            //char setGLL[] = { 0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x2B };
            //SendUBX(setGLL, sizeof(setGLL));
        }
		else if (strncmp(Buffer+3, "GSA", 3) == 0)
        {
            // Disable GSA
            printf("Disabling GSA\r\n");
            char setGSA[] = { 0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x32 };
            SendUBX(setGSA, sizeof(setGSA));
        }
		else if (strncmp(Buffer+3, "VTG", 3) == 0)
        {
            // Disable VTG
            printf("Disabling VTG\r\n");
            char setVTG[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x05, 0x47};
            SendUBX(setVTG, sizeof(setVTG));
        }
        else
        {
            printf("Unknown NMEA sentence: %s\n", Buffer);
        }
    }
    else
    {
       printf("Bad checksum\r\n");
	}
}

void PrintGPSData(){
    printf("GPS\n");
    printf("H:%u M:%u S:%u\n",GPS_Storred->Hours,GPS_Storred->Minutes,GPS_Storred->Seconds);
    printf("LAT:%f LONG:%f\n",GPS_Storred->Latitude,GPS_Storred->Longitude);
    printf("Sat Fixes = %d\n",GPS_Storred->Satellites);
}