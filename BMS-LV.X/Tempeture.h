/* 
 * File:   Tempeture.h
 * Author: richc_000
 *
 * Created on March 25, 2015, 5:30 PM
 */

#ifndef TEMPETURE_H
#define	TEMPETURE_H

#define TEMP_SENSE_PWR LATAbits.LA0 

#define TEMP_ON 0
#define TEMP_OFF 1

extern char Temp_Fault();
extern void Temp_Read();
extern void Temp_Filter();
extern void Temp_Convert();
extern float Tempeture_Get(int channelnum);



#endif	/* TEMPETURE_H */

