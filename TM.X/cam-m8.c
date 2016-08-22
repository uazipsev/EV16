#include "cam-m8.h"
#include "UART4.h"
#include <stdio.h>


void CamM8Init(){
    UART4_init();
}

void CamM8Read(){
    while(Receive_get4() != '$'){   
    }
    if(Receive_get4() == 'G'){
        if(Receive_get4() == 'N'){
            if(Receive_get4() == 'R'){
                if(Receive_get4() == 'M'){
                    if(Receive_get4() == 'C'){
                        printf("Data Packet");
                        UART4_Clear();

                    }          
                }
            }
        }
    }
}

void SetCarMode()
{
    // Send navigation configuration command
    unsigned char setNav[] = {0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x05, 0x00, 0xFA, 0x00, 0xFA, 0x00, 0x64, 0x00, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0xDC};
    SendUBX(setNav, sizeof(setNav));
	printf ("Setting flight mode\n");
}

void SendUBX(unsigned char *MSG, int len)
{
    int i = 0;
    while(len != 0){
        Send_put4(MSG[i]);
        i++;
        len--;
    }

}

int CamM8CRCCheck(unsigned char *Message, int Count)
{
  unsigned char XOR, i, c;

  XOR = 0;
  for (i = 1; i < (Count-4); i++)
  {
    c = Message[i];
    XOR ^= c;
  }

  //return (Message[Count-4] == '*') && (Message[Count-3] == Hex(XOR >> 4)) && (Message[Count-2] == Hex(XOR & 15));
  return 0;
}

void CamM8CRC(unsigned char *Message, int Length)
{ 
  int i;
  unsigned char CK_A, CK_B;
  
  CK_A = 0;
  CK_B = 0;

  for (i=2; i<(Length-2); i++)
  {
    CK_A = CK_A + Message[i];
    CK_B = CK_B + CK_A;
  }
  
  Message[Length-2] = CK_A;
  Message[Length-1] = CK_B;
}