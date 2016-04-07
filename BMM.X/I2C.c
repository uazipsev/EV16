#include <xc.h>
#include <stdbool.h>
#include "p33Fxxxx.h"

#include "i2c.h"

unsigned int jDone;


/*=============================================================================
I2C Master Interrupt Service Routine
=============================================================================*/
void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void)
{
		jDone=1;
        IFS1bits.MI2C1IF = 0;		//Clear the DMA0 Interrupt Flag;

}

/*=============================================================================
I2C Slave Interrupt Service Routine
=============================================================================*/
void __attribute__((interrupt, no_auto_psv)) _SI2C1Interrupt(void)
{
	
        IFS1bits.SI2C1IF = 0;		//Clear the DMA0 Interrupt Flag
}



/*=============================================================================
I2C Peripheral Initialisation
=============================================================================*/   
void I2CEMEMinit(I2CEMEM_DRV *i2cMem)
{   
    i2cMem->cmd=0;
    i2cMem->oData=0;

// Configre SCA/SDA pin as open-drain
	//ODCGbits.ODCG2=1;
	//ODCGbits.ODCG3=1;


	I2C1CONbits.A10M=0;
	I2C1CONbits.SCLREL=1;
	I2C1BRG=300;

	I2C1ADD=0;
	I2C1MSK=0;

	I2C1CONbits.I2CEN=1;
	IEC1bits.MI2C1IE = 1;
  	IFS1bits.MI2C1IF = 0;


}

/*=============================================================================
I2C Serial EEPROM, STATE-MACHINE BASED DRIVER
=============================================================================*/                                                             
void I2CEMEMdrv(I2CEMEM_DRV *i2cMem)
{

static int state=0, cntr=0, rtrycntr=0;

    switch(state)
    {
    case 0: 
        if( (i2cMem->cmd == I2C_WRITE)  || (i2cMem->cmd == I2C_READ)  ) 
			state=1;   
          
        break;

	/*==================================*/        
	/* Control/Address Phase			*/
	/*==================================*/
    case 1:
		// Start Condition
		I2C1CONbits.SEN=1;		
		state=state+1;
        break;


    case 2:
        // Start Byte with device select id
	    if(jDone==1)	{ 
			jDone=0;
          	state=state+1;
  			I2C1TRN=(0x00A0)|(((i2cMem->oData->csel)&0x7)<<1);
		}
        break;

    case 3:         
       	// Send address byte 1, if ack is received. Else Retry
        if(jDone==1)	{ 
			jDone=0;
  	
			if(I2C1STATbits.ACKSTAT==1) {		// Ack Not received, Retry

				if(rtrycntr < MAX_RETRY)
					state=18;
				else
					state=16;					// Flag error and exit

			} else {
 
				rtrycntr=0;

            	#if ADDRWIDTH==TWO_BYTE
            	I2C1TRN=((i2cMem->oData->addr)&0xFF00)>>8;
           		state=state+1;
            	#endif
               
            	#if ADDRWIDTH==ONE_BYTE
            	I2C1TRN=((i2cMem->oData->addr));
            	state=state+2;
            	#endif

			}
		}
		break;
    
    
    case 4:
		// Send address byte 2, if ack is received. Else Flag error and exit
      	if(jDone==1)	{ 
			jDone=0;

			if(I2C1STATbits.ACKSTAT==1) {		// Ack Not received, Flag error and exit
				state=16;

			} else {

            	#if ADDRWIDTH==TWO_BYTE
            	I2C1TRN=((i2cMem->oData->addr)&0x00FF);
            	#endif
            	state=state+1;
			}
		}
    	break;
    

    case 5:
		// Read or Write
      	if(jDone==1)	{ 
			jDone=0;

			if(I2C1STATbits.ACKSTAT==1) {		// Ack Not received, Flag error and exit
				state=16;

			} else {

        		if(i2cMem->cmd == I2C_WRITE) 
					state=state+1;   
 
        		if(i2cMem->cmd == I2C_READ) 
					state=8;
			}

		}
        break;

	/*==================================*/        
	/* Write Data Phase			        */
	/*==================================*/

    case 6:
		// Send data
        I2C1TRN=*(i2cMem->oData->buff + cntr); 
        state=state+1;
        cntr=cntr+1;
        break;   

    case 7:  
		// Look for end of data or no Ack
      	if(jDone==1)	{ 
			jDone=0;
			state=state-1;

			if(I2C1STATbits.ACKSTAT==1) {		// Ack Not received, Flag error and exit
				state=16;
			} else {

        		if(cntr== i2cMem->oData->n) 
					state=14;   				// Close the Frame
				}
		}
        break;

	/*==================================*/        
	/* Read Data Phase			        */
	/*==================================*/
    case 8:
		// Repeat Start
 		I2C1CONbits.RSEN=1;	
		state=state+1;
        break;

    case 9:
		// Re-send control byte with W/R=R
	    if(jDone==1)	{ 
			jDone=0;
          	state=state+1;
  			I2C1TRN=(0x00A1)|(((i2cMem->oData->csel)&0x7)<<1);
		}
        break;

    case 10:    
		// Check, if control byte went ok
	    if(jDone==1)	{ 
			jDone=0;
          	state=state+1;

			if(I2C1STATbits.ACKSTAT==1) 		// Ack Not received, Flag error and exit
				state=16;
	
		}
        break;

    case 11:
      	// Receive Enable 
 		I2C1CONbits.RCEN=1;	
        state++;
        break;

    case 12:  
		// Receive data
	    if(jDone==1)	{ 
			jDone=0;
			state=state+1;

			*(i2cMem->oData->buff+cntr)=I2C1RCV;
			cntr++;

        	if(cntr== i2cMem->oData->n) {
				I2C1CONbits.ACKDT=1;		// No ACK		
			} else {
				I2C1CONbits.ACKDT=0;		// ACK
			}

			I2C1CONbits.ACKEN=1;	

		}
		break;

    case 13: 
	    if(jDone==1)	{ 
			jDone=0;
		  	if(cntr== i2cMem->oData->n) 
            	state=state+1;
           	else
            	state=state-2;
         }          
         break;
         
	/*==================================*/        
	/* Stop Sequence			        */
	/*==================================*/
    case 14: 
      	I2C1CONbits.PEN=1;
        state++;
        break;
           
    case 15: 
 	    if(jDone==1)	{ 
			jDone=0;
			state=0;
			cntr=0;
			i2cMem->cmd=0;
		}
      	break;

	/*==================================*/        
	/* Set Error     			        */
	/*==================================*/
    case 16:
       	I2C1CONbits.PEN=1;	
      	state++;
        break;
    
    case 17:
 	    if(jDone==1)	{ 
			jDone=0;
			state=0;
			rtrycntr=0;
			cntr=0;
			i2cMem->cmd=0xFFFF;
		}
      	break;

	/*==================================*/        
	/* Retry         			        */
	/*==================================*/
    case 18:
       	I2C1CONbits.PEN=1;	
      	state++;
		rtrycntr++;
        break;

    case 19:
 	    if(jDone==1)	{ 
			jDone=0;
			state=0;
			cntr=0;
		}
      	break;


 	}     

}