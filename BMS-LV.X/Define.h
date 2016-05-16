/* 
 * File:   Define.h
 * Author: Rick
 *
 * Created on March 25, 2015, 3:39 AM
 */

#ifndef DEFINE_H
#define	DEFINE_H

/*
 *  This is the RS485 ID
 */
#define RS485ID 0x10
/*
 *  Battery cutoffs
 */
//Number of batteries
#define NUMOFBATT 6 // Num of cells - 1
// Battery volt high cutoff
#define BATHIGH 4.21
// Battery volt high cutoff
#define BATBYPON 4.18
// Battery volt high cutoff
#define BATBYPOFF 4.15
// Battery volt low cutoff
#define BATLOW  3.00
// Battery temp cutoff
#define TEMPHIGH 60.5

/*
 * Current Cutouts
 */
#define CURRENTHIGH 25

/*
 *  Avrage Alpha's
 *  The a should be between (1-0)
 *  0.001 = all prev....
 *  1 = no filtering
 */
// Battery Alpha for filter
#define BATALPHA 0.88
// Temp Alpha for filter
#define TEMPALPHA 0.88

/*
 *  NTC #Def
 */
#define THERMISTORNOMINAL 10000
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 10000


#endif	/* DEFINE_H */

