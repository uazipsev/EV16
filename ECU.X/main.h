/* 
 * File:   main.h
 * Author: Zac Kilburn
 *
 * Created on May 28, 2015, 10:47 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif


    extern unsigned int brake;
    void updateBrakeLight();
    extern volatile unsigned int time;

    void ledDebug() {
        if (time > 1000) {
            INDICATOR ^= 1;
            time = 0;
        }
    }
    extern void updateComms();
    extern void Delay(int ms);
    extern void Setup(void);


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

