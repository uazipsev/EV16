/* 
 * File:   Communications.h
 * Author: User
 *
 * Created on May 31, 2015, 8:32 PM
 */

#ifndef COMMUNICATIONS_H
#define	COMMUNICATIONS_H

#ifdef	__cplusplus
extern "C" {
#endif
    unsigned int throttle, brake;
    void updateComms();
    unsigned int buttonsCollector();
    extern void Delay(int wait);
    void respondECU();
    void handleIndicators(int receivedIndicators);
    void TBbarGraphs(int t, int b);
#ifdef	__cplusplus
}
#endif

#endif	/* COMMUNICATIONS_H */

