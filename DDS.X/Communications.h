/* 
 * File:   Communications.h
 * Author: User
 *
 * Created on May 31, 2015, 8:32 PM
 */

#ifndef COMMUNICATIONS_H
#define	COMMUNICATIONS_H

#define NUM_BUTTONS 8
#define NUM_INDICATORS 6

    void updateComms();
    unsigned int buttonsCollector();
    void respondECU();
    void handleIndicators(int receivedIndicators);
    void DataBarGraphs(unsigned int BGA, unsigned int BGB);
    unsigned int GetDataBarGraphA();
    unsigned int GetDataBarGraphB();

#endif	/* COMMUNICATIONS_H */

