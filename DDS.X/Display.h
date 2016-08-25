/* 
 * File:   Display.h
 * Author: Rick
 *
 * Created on May 1, 2016, 4:13 AM
 */

#ifndef DISPLAY_H
#define	DISPLAY_H



typedef enum{
    BV,
    BC,
    BT,
    MT,
    MCT,
    FLT
}my_data;

void SetData(my_data data, int numb);
void Setupdisplay();
void Splash();
void Normal();

#endif	/* DISPLAY_H */

