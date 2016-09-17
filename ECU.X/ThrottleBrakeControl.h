

#ifndef THROTTLEBRAKECONTROL_H
#define	THROTTLEBRAKECONTROL_H

#define GETSAST1 1
#define GETSAST2 2
#define GETSASB1 3
#define GETSASB2 4
#define GETSASBP 5

unsigned int GetSASValue(char request);
char GetSASFalts();
void SetThrotteMax(int val);

#endif	/* XC_HEADER_TEMPLATE_H */

