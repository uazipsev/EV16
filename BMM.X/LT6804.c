/*!
	LTC6804-2 Multicell Battery Monitor
@verbatim	
	The LTC6804 is a 3rd generation multicell battery stack
	monitor that measures up to 12 series connected battery
	cells with a total measurement error of less than 1.2mV. The
	cell measurement range of 0V to 5V makes the LTC6804
	suitable for most battery chemistries. All 12 cell voltages
	can be captured in 290uS, and lower data acquisition rates
	can be selected for high noise reduction.
	
	Using the LTC6804-2, multiple devices are connected in
	parallel to the host processor, with each device 
	individually addressed.
@endverbatim	
REVISION HISTORY
$Revision: 1000 $
$Date: 2013-12-13 

Copyright (c) 2013, Linear Technology Corp.(LTC)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of Linear Technology Corp.

The Linear Technology Linduino is not affiliated with the official Arduino team.
However, the Linduino is only possible because of the Arduino team's commitment
to the open-source community.  Please, visit http://www.arduino.cc and
http://store.arduino.cc , and consider a purchase that will help fund their
ongoing work.

Copyright 2013 Linear Technology Corp. (LTC)
***********************************************************/

//! @defgroup LTC68042 LTC6804-2: Multicell Battery Monitor

/*! @file
    @ingroup LTC68042
    Library for LTC6804-2 Multicell Battery Monitor
*/

#include <stdint.h>
#include "spi2.h"
#include "LT6804.h"
#include "PinDef.h"
#include "Function.h"


/*
   ADC control Variables for LTC6804
*/
int i = 0;
int current_ic = 0;
int current_byte = 0;

/*!
  6804 conversion command variables.  
*/
int ADCV[2]; //!< Cell Voltage conversion command.
int ADAX[2]; //!< GPIO conversion command.


/*!
  \brief This function will initialize all 6804 variables and the SPI port.

  input: 
  ------
  IC: number of ICs being controlled. The address of the ICs in a LTC6804-2 network will start at 0 and continue in an ascending order.
*/
void LTC6804_initialize()
{
  SPI2_Initialize();
  set_adc(MD_NORMAL,DCP_DISABLED,CELL_CH_ALL,AUX_CH_ALL);
}

/*!******************************************************************************************************************
 \brief Maps  global ADC control variables to the appropriate control bytes for each of the different ADC commands
 
@param[in] int MD The adc conversion mode
@param[in] int DCP Controls if Discharge is permitted during cell conversions
@param[in] int CH Determines which cells are measured during an ADC conversion command
@param[in] int CHG Determines which GPIO channels are measured during Auxiliary conversion command
 
 Command Code: \n
			|command	|  10   |   9   |   8   |   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   | 
			|-----------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|
			|ADCV:	    |   0   |   1   | MD[1] | MD[2] |   1   |   1   |  DCP  |   0   | CH[2] | CH[1] | CH[0] | 
			|ADAX:	    |   1   |   0   | MD[1] | MD[2] |   1   |   1   |  DCP  |   0   | CHG[2]| CHG[1]| CHG[0]| 
 ******************************************************************************************************************/

void set_adc(int MD, //ADC Mode
			 int DCP, //Discharge Permit
			 int CH, //Cell Channels to be measured
			 int CHG //GPIO Channels to be measured
			 )
{
  int md_bits;
  
  md_bits = (MD & 0x02) >> 1;
  ADCV[0] = md_bits + 0x02;
  md_bits = (MD & 0x01) << 7;
  ADCV[1] =  md_bits + 0x60 + (DCP<<4) + CH;
 
  md_bits = (MD & 0x02) >> 1;
  ADAX[0] = md_bits + 0x04;
  md_bits = (MD & 0x01) << 7;
  ADAX[1] = md_bits + 0x60 + CHG ; //LOOK no DCP? 
  
}


/*!*********************************************************************************************
  \brief Starts cell voltage conversion
  
  Starts ADC conversions of the LTC6804 Cpin inputs.
  The type of ADC conversion done is set using the associated global variables:
 |Variable|Function                                      | 
 |--------|----------------------------------------------|
 | MD     | Determines the filter corner of the ADC      |
 | CH     | Determines which cell channels are converted |
 | DCP    | Determines if Discharge is Permitted	     |
  
***********************************************************************************************/
void LTC6804_adcv()
{

  int cmd[4];
  int temp_pec;
  
  //1
  cmd[0] = ADCV[0];
  cmd[1] = ADCV[1];
  
  //2
  temp_pec = pec15_calc(2, ADCV);
  cmd[2] = (int)(temp_pec >> 8);
  cmd[3] = (int)(temp_pec);
  
  //3
  wakeup_idle (); //This will guarantee that the LTC6804 isoSPI port is awake. This command can be removed.
  
  //4
  LT6020_1_CS = 0;
  spi_write_array(4,cmd);
  LT6020_1_CS = 1;

}
/*
  LTC6804_adcv Function sequence:
  
  1. Load adcv command into cmd array
  2. Calculate adcv cmd PEC and load pec into cmd array
  3. wakeup isoSPI port, this step can be removed if isoSPI status is previously guaranteed
  4. send broadcast adcv command to LTC6804 stack
*/


/*!******************************************************************************************************
 \brief Start an GPIO Conversion
 
  Starts an ADC conversions of the LTC6804 GPIO inputs.
  The type of ADC conversion done is set using the associated global variables:
 |Variable|Function                                      | 
 |--------|----------------------------------------------|
 | MD     | Determines the filter corner of the ADC      |
 | CHG    | Determines which GPIO channels are converted |
 
*********************************************************************************************************/
void LTC6804_adax()
{
  int cmd[4];
  int temp_pec;
 
  cmd[0] = ADAX[0];
  cmd[1] = ADAX[1];
  temp_pec = pec15_calc(2, ADAX);
  cmd[2] = (int)(temp_pec >> 8);
  cmd[3] = (int)(temp_pec);
 
  wakeup_idle (); //This will guarantee that the LTC6804 isoSPI port is awake. This command can be removed.
  LT6020_1_CS = 0;
  spi_write_array(4,cmd);
  LT6020_1_CS = 1;

}
/*
  LTC6804_adax Function sequence:
  
  1. Load adax command into cmd array
  2. Calculate adax cmd PEC and load pec into cmd array
  3. wakeup isoSPI port, this step can be removed if isoSPI status is previously guaranteed
  4. send broadcast adax command to LTC6804 stack
*/


/***********************************************//**
 \brief Reads and parses the LTC6804 cell voltage registers.
 
 The function is used to read the cell codes of the LTC6804.
 This function will send the requested read commands parse the data
 and store the cell voltages in cell_codes variable. 
 
 
@param[in] int reg; This controls which cell voltage register is read back. 
 
          0: Read back all Cell registers 
		  
          1: Read back cell group A 
		  
          2: Read back cell group B 
		  
          3: Read back cell group C 
		  
          4: Read back cell group D 
 
@param[in] int total_ic; This is the number of ICs in the network
 

@param[out] int cell_codes[]; An array of the parsed cell codes from lowest to highest. The cell codes will
  be stored in the cell_codes[] array in the following format:
  |  cell_codes[0]| cell_codes[1] |  cell_codes[2]|    .....     |  cell_codes[11]|  cell_codes[12]| cell_codes[13] |  .....   |
  |---------------|----------------|--------------|--------------|----------------|----------------|----------------|----------|
  |IC1 Cell 1     |IC1 Cell 2      |IC1 Cell 3    |    .....     |  IC1 Cell 12   |IC2 Cell 1      |IC2 Cell 2      | .....    |
 
 @return int8_t, PEC Status.
 
	0: No PEC error detected
  
	-1: PEC error detected, retry read
 *************************************************/
int LTC6804_rdcv(int reg,
					 int total_ic,
					 int cell_codes[][12]
					 )
{
 
    int cell_reg = 0;
    int current_cell = 0;
  const int NUM_RX_BYT = 8;
  const int BYT_IN_REG = 6;
  const int CELL_IN_REG = 3;
  
  int *cell_data;
  int pec_error = 0;
  int parsed_cell;
  int received_pec;
  int data_pec;
  int data_counter=0; //data counter
  cell_data = (int *) malloc((NUM_RX_BYT*total_ic)*sizeof(int));
  //1.a
  if (reg == 0)
  {
    //a.i
    for(cell_reg = 1; cell_reg<5; cell_reg++)         			 //executes once for each of the LTC6804 cell voltage registers
    {
      data_counter = 0;
      LTC6804_rdcv_reg(cell_reg, total_ic,cell_data);
      for (current_ic = 0 ; current_ic < total_ic; current_ic++) // executes for every LTC6804 in the stack
      {																 	  // current_ic is used as an IC counter
        //a.ii
		for(current_cell = 0; current_cell<CELL_IN_REG; current_cell++)	 								  // This loop parses the read back data. Loops 
        {														   		  // once for each cell voltages in the register 
          parsed_cell = cell_data[data_counter] + (cell_data[data_counter + 1] << 8);
          cell_codes[current_ic][current_cell  + ((cell_reg - 1) * CELL_IN_REG)] = parsed_cell;
          data_counter = data_counter + 2;
        }
		//a.iii
        received_pec = (cell_data[data_counter] << 8) + cell_data[data_counter+1];
        data_pec = pec15_calc(BYT_IN_REG, &cell_data[current_ic * NUM_RX_BYT ]);
        if(received_pec != data_pec)
        {
          pec_error--;//pec_error = -1;
        }
        data_counter=data_counter+2;
      }
    }
  }
 //1.b
  else
  {
	//b.i
	
    LTC6804_rdcv_reg(reg, total_ic,cell_data);
    for (current_ic = 0 ; current_ic < total_ic; current_ic++) // executes for every LTC6804 in the stack
    {							   									// current_ic is used as an IC counter
		//b.ii
		for(current_cell = 0; current_cell < CELL_IN_REG; current_cell++)   									// This loop parses the read back data. Loops 
		{						   									// once for each cell voltage in the register 
			parsed_cell = cell_data[data_counter] + (cell_data[data_counter+1]<<8);
			cell_codes[current_ic][current_cell + ((reg - 1) * CELL_IN_REG)] = 0x0000FFFF & parsed_cell;
			data_counter= data_counter + 2;
		}
		//b.iii
	    received_pec = (cell_data[data_counter] << 8 )+ cell_data[data_counter + 1];
        data_pec = pec15_calc(BYT_IN_REG, &cell_data[current_ic * NUM_RX_BYT * (reg-1)]);
		if(received_pec != data_pec)
		{
			pec_error--;//pec_error = -1;
		}
	}
  }
 free(cell_data);
 //2
return(pec_error);
}
/*
	LTC6804_rdcv Sequence
	
	1. Switch Statement:
		a. Reg = 0
			i. Read cell voltage registers A-D for every IC in the stack
			ii. Parse raw cell voltage data in cell_codes array
			iii. Check the PEC of the data read back vs the calculated PEC for each read register command
		b. Reg != 0 
			i.Read single cell voltage register for all ICs in stack
			ii. Parse raw cell voltage data in cell_codes array
			iii. Check the PEC of the data read back vs the calculated PEC for each read register command
	2. Return pec_error flag
*/


/***********************************************//**
 \brief Read the raw data from the LTC6804 cell voltage register
 
 The function reads a single cell voltage register and stores the read data
 in the *data point as a byte array. This function is rarely used outside of 
 the LTC6804_rdcv() command. 
 
 @param[in] int reg; This controls which cell voltage register is read back. 
         
          1: Read back cell group A 
		  
          2: Read back cell group B 
		  
          3: Read back cell group C 
		  
          4: Read back cell group D 
		  
 @param[in] int total_ic; This is the number of ICs in the network
 
 @param[out] int *data; An array of the unparsed cell codes 
 *************************************************/
void LTC6804_rdcv_reg(int reg,
					  int total_ic, 
					  int *data
					  )
{
  int cmd[4];
  int temp_pec;
  
  //1
  if (reg == 1)
  {
    cmd[1] = 0x04;
    cmd[0] = 0x00;
  }
  else if(reg == 2)
  {
    cmd[1] = 0x06;
    cmd[0] = 0x00;
  } 
  else if(reg == 3)
  {
    cmd[1] = 0x08;
    cmd[0] = 0x00;
  } 
  else if(reg == 4)
  {
    cmd[1] = 0x0A;
    cmd[0] = 0x00;
  } 

  //2
 
  
  //3
  wakeup_idle (); //This will guarantee that the LTC6804 isoSPI port is awake. This command can be removed.
  
  //4
  for(current_ic = 0; current_ic<total_ic; current_ic++)
  {
	cmd[0] = 0x80 + (current_ic<<3); //Setting address
    temp_pec = pec15_calc(2, cmd);
	cmd[2] = (int)(temp_pec >> 8);
	cmd[3] = (int)(temp_pec); 
	LT6020_1_CS = 0;
	spi_write_read(cmd,4,&data[current_ic*8],8);
	LT6020_1_CS = 1;
  }
}
/*
  LTC6804_rdcv_reg Function Process:
  1. Determine Command and initialize command array
  2. Calculate Command PEC
  3. Wake up isoSPI, this step is optional
  4. Send Global Command to LTC6804 stack
*/


/***********************************************************************************//**
 \brief Reads and parses the LTC6804 auxiliary registers.
 
 The function is used
 to read the  parsed GPIO codes of the LTC6804. This function will send the requested 
 read commands parse the data and store the gpio voltages in aux_codes variable 
 
 @param[in] int reg; This controls which GPIO voltage register is read back. 
		  
          0: Read back all auxiliary registers 
		  
          1: Read back auxiliary group A 
		  
          2: Read back auxiliary group B 
		  
 
 @param[in] int total_ic; This is the number of ICs in the network

 @param[out] int aux_codes[]; An array of the aux codes from lowest to highest. The GPIO codes will
 be stored in the aux_codes[] array in the following format:
 |  aux_codes[0]| aux_codes[1] |  aux_codes[2]|  aux_codes[3]|  aux_codes[4]|  aux_codes[5]| aux_codes[6] |aux_codes[7]|  .....    |
 |--------------|--------------|--------------|--------------|--------------|--------------|--------------|------------|-----------|
 |IC1 GPIO1     |IC1 GPIO2     |IC1 GPIO3     |IC1 GPIO4     |IC1 GPIO5     |IC1 Vref2     |IC2 GPIO1     |IC2 GPIO2   |  .....    |
 
 
 @return int8_t, PEC Status.
 
	0: No PEC error detected
  
	-1: PEC error detected, retry read
 *************************************************/
int LTC6804_rdaux(int reg,
					 int total_ic, 
					 int aux_codes[][6]
					 )
{


  const int NUM_RX_BYT = 8;
  const int BYT_IN_REG = 6;
  const int GPIO_IN_REG = 3;
  int gpio_reg = 0;
  int current_gpio = 0;
  int *data;
  int data_counter = 0; 
  int8_t pec_error = 0;
  int received_pec;
  int data_pec;
  data = (int *) malloc((NUM_RX_BYT*total_ic)*sizeof(int));
  //1.a
  if (reg == 0)
  {
	//a.i
    for(gpio_reg = 1; gpio_reg<3; gpio_reg++)		 	   		 //executes once for each of the LTC6804 aux voltage registers
    {
      data_counter = 0;
      LTC6804_rdaux_reg(gpio_reg, total_ic,data);
      for (current_ic = 0 ; current_ic < total_ic; current_ic++) // This loop executes once for each LTC6804
      {									  								 // current_ic is used as an IC counter
        //a.ii
		for(current_gpio = 0; current_gpio< GPIO_IN_REG; current_gpio++)	// This loop parses GPIO voltages stored in the register
        {								   													
          
          aux_codes[current_ic][current_gpio +((gpio_reg-1)*GPIO_IN_REG)] = data[data_counter] + (data[data_counter+1]<<8);
          data_counter=data_counter+2;
		  
        }
		//a.iii
        received_pec = (data[data_counter]<<8)+ data[data_counter+1];
        data_pec = pec15_calc(BYT_IN_REG, &data[current_ic*NUM_RX_BYT*(gpio_reg-1)]);
        if(received_pec != data_pec)
        {
          pec_error = -1;
        }
       
        data_counter=data_counter+2;
      }
   

    }
  
  }
  else
  {
	//b.i
    LTC6804_rdaux_reg(reg, total_ic, data);
    for (current_ic = 0 ; current_ic < total_ic; current_ic++) // executes for every LTC6804 in the stack
    {							   // current_ic is used as an IC counter
		//b.ii
		for(current_gpio = 0; current_gpio<GPIO_IN_REG; current_gpio++)   // This loop parses the read back data. Loops 
		{						   // once for each aux voltage in the register 
			aux_codes[current_ic][current_gpio +((reg-1)*GPIO_IN_REG)] = 0x0000FFFF & (data[data_counter] + (data[data_counter+1]<<8));
			data_counter=data_counter+2;
		}
		//b.iii
		received_pec = (data[data_counter]<<8) + data[data_counter+1];
        data_pec = pec15_calc(6, &data[current_ic*8*(reg-1)]);
        if(received_pec != data_pec)
        {
          pec_error = -1;
        }
	}
  }
  free(data);
  return (pec_error);
}
/*
	LTC6804_rdaux Sequence
	
	1. Switch Statement:
		a. Reg = 0
			i. Read GPIO voltage registers A-D for every IC in the stack
			ii. Parse raw GPIO voltage data in cell_codes array
			iii. Check the PEC of the data read back vs the calculated PEC for each read register command
		b. Reg != 0 
			i.Read single GPIO voltage register for all ICs in stack
			ii. Parse raw GPIO voltage data in cell_codes array
			iii. Check the PEC of the data read back vs the calculated PEC for each read register command
	2. Return pec_error flag
*/


/***********************************************//**
 \brief Read the raw data from the LTC6804 auxiliary register
 
 The function reads a single GPIO voltage register and stores thre read data
 in the *data point as a byte array. This function is rarely used outside of 
 the LTC6804_rdaux() command. 
 
 @param[in] int reg; This controls which GPIO voltage register is read back. 
		  
          1: Read back auxiliary group A
		  
          2: Read back auxiliary group B 

         
 @param[in] int total_ic; This is the number of ICs in the stack
 
 @param[out] int *data; An array of the unparsed aux codes 
 *************************************************/
void LTC6804_rdaux_reg(int reg, 
					   int total_ic,
					   int *data
					   )
{
  int cmd[4];
  int cmd_pec;
  
  //1
  if (reg == 1)
  {
    cmd[1] = 0x0C;
    cmd[0] = 0x00;
  }
  else if(reg == 2)
  {
    cmd[1] = 0x0e;
    cmd[0] = 0x00;
  } 
  else
  {
     cmd[1] = 0x0C;
     cmd[0] = 0x00;
  }
  //2
  cmd_pec = pec15_calc(2, cmd);
  cmd[2] = (int)(cmd_pec >> 8);
  cmd[3] = (int)(cmd_pec);
  
  //3
  wakeup_idle (); //This will guarantee that the LTC6804 isoSPI port is awake, this command can be removed.
  //4
   for(current_ic = 0; current_ic<total_ic; current_ic++)
  {
	cmd[0] = 0x80 + (current_ic<<3); //Setting address
    cmd_pec = pec15_calc(2, cmd);
	cmd[2] = (int)(cmd_pec >> 8);
	cmd[3] = (int)(cmd_pec); 
	LT6020_1_CS = 0;
	spi_write_read(cmd,4,&data[current_ic*8],8);
	LT6020_1_CS = 1;
  }
}
/*
  LTC6804_rdaux_reg Function Process:
  1. Determine Command and initialize command array
  2. Calculate Command PEC
  3. Wake up isoSPI, this step is optional
  4. Send Global Command to LTC6804 stack
*/

/********************************************************//**
 \brief Clears the LTC6804 cell voltage registers
 
 The command clears the cell voltage registers and intiallizes 
 all values to 1. The register will read back hexadecimal 0xFF
 after the command is sent.
************************************************************/
void LTC6804_clrcell()
{
  int cmd[4];
  int cmd_pec;
  
  //1
  cmd[0] = 0x07;
  cmd[1] = 0x11;
  
  //2
  cmd_pec = pec15_calc(2, cmd);
  cmd[2] = (int)(cmd_pec >> 8);
  cmd[3] = (int)(cmd_pec );
  
  //3
  wakeup_idle (); //This will guarantee that the LTC6804 isoSPI port is awake. This command can be removed.
  
  //4
  LT6020_1_CS = 0;
  spi_write_read(cmd,4,0,0);
  LT6020_1_CS = 1;
}
/*
  LTC6804_clrcell Function sequence:
  
  1. Load clrcell command into cmd array
  2. Calculate clrcell cmd PEC and load pec into cmd array
  3. wakeup isoSPI port, this step can be removed if isoSPI status is previously guaranteed
  4. send broadcast clrcell command to LTC6804 stack
*/


/***********************************************************//**
 \brief Clears the LTC6804 Auxiliary registers
 
 The command clears the Auxiliary registers and intiallizes 
 all values to 1. The register will read back hexadecimal 0xFF
 after the command is sent.
***************************************************************/
void LTC6804_clraux()
{
  int cmd[4];
  int cmd_pec;
  
  //1
  cmd[0] = 0x07;
  cmd[1] = 0x12;
  
  //2
  cmd_pec = pec15_calc(2, cmd);
  cmd[2] = (int)(cmd_pec >> 8);
  cmd[3] = (int)(cmd_pec);
  
  //3
  wakeup_idle (); //This will guarantee that the LTC6804 isoSPI port is awake.This command can be removed.
  //4
  LT6020_1_CS = 0;
  //spi_write_read(cmd,4,0,0);
  LT6020_1_CS = 1;
}
/*
  LTC6804_clraux Function sequence:
  
  1. Load clraux command into cmd array
  2. Calculate clraux cmd PEC and load pec into cmd array
  3. wakeup isoSPI port, this step can be removed if isoSPI status is previously guaranteed
  4. send broadcast clraux command to LTC6804 stack
*/


/*****************************************************//**
 \brief Write the LTC6804 configuration register 
 
 This command will write the configuration registers of the stacks 
 connected in a stack stack. The configuration is written in descending 
 order so the last device's configuration is written first.
 

@param[in] int total_ic; The number of ICs being written. 
 
@param[in] int *config an array of the configuration data that will be written, the array should contain the 6 bytes for each
 IC in the stack. The lowest IC in the stack should be the first 6 byte block in the array. The array should
 have the following format:
 |  config[0]| config[1] |  config[2]|  config[3]|  config[4]|  config[5]| config[6] |  config[7]|  config[8]|  .....    |
 |-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|
 |IC1 CFGR0  |IC1 CFGR1  |IC1 CFGR2  |IC1 CFGR3  |IC1 CFGR4  |IC1 CFGR5  |IC2 CFGR0  |IC2 CFGR1  | IC2 CFGR2 |  .....    |
 
 The function will calculate the needed PEC codes for the write data
 and then transmit data to the ICs on a stack.
********************************************************/
void LTC6804_wrcfg(int total_ic,int config[][6])
{
  const int BYTES_IN_REG = 6;
  const int CMD_LEN = 4+(8*total_ic);
  int *cmd;
  int temp_pec;
  int cmd_index; //command counter
  
  cmd = (int *)malloc(CMD_LEN*sizeof(int));
  //1
  cmd[0] = 0x00;
  cmd[1] = 0x01;
  cmd[2] = 0x3d;
  cmd[3] = 0x6e;
  
  //2
  cmd_index = 4;
  for (current_ic = total_ic; current_ic > 0; current_ic--) 			// executes for each LTC6804 in stack, 
  {								
    for (current_byte = 0; current_byte < BYTES_IN_REG; current_byte++) // executes for each byte in the CFGR register
    {							// i is the byte counter
	
      cmd[cmd_index] = config[current_ic-1][current_byte]; 		//adding the config data to the array to be sent 
      cmd_index = cmd_index + 1;                
    }
	//3
    temp_pec = (int)pec15_calc(BYTES_IN_REG, &config[current_ic-1][0]);// calculating the PEC for each board
    cmd[cmd_index] = (int)(temp_pec >> 8);
    cmd[cmd_index + 1] = (int)temp_pec;
    cmd_index = cmd_index + 2;
  }
  
  //4
  wakeup_idle (); 															 //This will guarantee that the LTC6804 isoSPI port is awake.This command can be removed.
  //5
   for(current_ic = 0; current_ic<total_ic; current_ic++)
  {
	cmd[0] = 0x80 + (current_ic<<3); //Setting address
    temp_pec = pec15_calc(2, cmd);
	cmd[2] = (int)(temp_pec >> 8);
	cmd[3] = (int)(temp_pec); 
	LT6020_1_CS = 0;
	spi_write_array(4,cmd);
	spi_write_array(8,&cmd[4+(8*current_ic)]);
	LT6020_1_CS = 1;
  }
  free(cmd);
}
/*
	1. Load cmd array with the write configuration command and PEC
	2. Load the cmd with LTC6804 configuration data
	3. Calculate the pec for the LTC6804 configuration data being transmitted
	4. wakeup isoSPI port, this step can be removed if isoSPI status is previously guaranteed
	5. Write configuration of each LTC6804 on the stack

*/

/*!******************************************************
 \brief Reads configuration registers of a LTC6804 stack
 



@param[in] int total_ic: number of ICs in the stack

@param[out] int *r_config: array that the function will write configuration data to. The configuration data for each IC 
is stored in blocks of 8 bytes with the configuration data of the lowest IC on the stack in the first 8 bytes 
of the array, the second IC in the second 8 byte etc. Below is an table illustrating the array organization:

|r_config[0]|r_config[1]|r_config[2]|r_config[3]|r_config[4]|r_config[5]|r_config[6]  |r_config[7] |r_config[8]|r_config[9]|  .....    |
|-----------|-----------|-----------|-----------|-----------|-----------|-------------|------------|-----------|-----------|-----------|
|IC1 CFGR0  |IC1 CFGR1  |IC1 CFGR2  |IC1 CFGR3  |IC1 CFGR4  |IC1 CFGR5  |IC1 PEC High |IC1 PEC Low |IC2 CFGR0  |IC2 CFGR1  |  .....    |


@return int8_t PEC Status.
	0: Data read back has matching PEC
 
	-1: Data read back has incorrect PEC
********************************************************/
int LTC6804_rdcfg(int total_ic, int r_config[][8])
{
  const int BYTES_IN_REG = 8;
  int cmd[4];
  int *rx_data;
  int8_t pec_error = 0; 
  int data_pec;
  int received_pec;
  rx_data = (int *) malloc((8*total_ic)*sizeof(int));
  //1
  cmd[0] = 0x00;
  cmd[1] = 0x02;
  cmd[2] = 0x2b;
  cmd[3] = 0x0A;
 
  //2
  wakeup_idle (); //This will guarantee that the LTC6804 isoSPI port is awake. This command can be removed.
  //3
   for(current_ic = 0; current_ic<total_ic; current_ic++)
  {
	cmd[0] = 0x80 + (current_ic<<3); //Setting address
    data_pec = pec15_calc(2, cmd);
	cmd[2] = (int)(data_pec >> 8);
	cmd[3] = (int)(data_pec); 
	LT6020_1_CS = 0;
	spi_write_read(cmd,4,&rx_data[current_ic*8],8);
	LT6020_1_CS = 1;
  }
 
  for (current_ic = 0; current_ic < total_ic; current_ic++) //executes for each LTC6804 in the stack
  { 
    //4.a
    for (current_byte = 0; current_byte < BYTES_IN_REG; current_byte++)
    {
      r_config[current_ic][current_byte] = rx_data[current_byte + (current_ic*BYTES_IN_REG)];
    }
    //4.b
    received_pec = (r_config[current_ic][6]<<8) + r_config[current_ic][7];
    data_pec = pec15_calc(6, &r_config[current_ic][0]);
    if(received_pec != data_pec)
    {
      pec_error = -1;
    }  
  }
  free(rx_data);
  //5
  return(pec_error);
}
/*
	1. Load cmd array with the write configuration command and PEC
	2. wakeup isoSPI port, this step can be removed if isoSPI status is previously guaranteed
	3. read configuration of each LTC6804 on the stack
	4. For each LTC6804 in the stack
	  a. load configuration data into r_config array
	  b. calculate PEC of received data and compare against calculated PEC
	5. Return PEC Error

*/

/*!****************************************************
  \brief Wake isoSPI up from idle state
 Generic wakeup commannd to wake isoSPI up out of idle
 *****************************************************/
void wakeup_idle()
{
  LT6020_1_CS = 0;
  delay_ms(10); //Guarantees the isoSPI will be in ready mode
  LT6020_1_CS = 1;
}

/*!****************************************************
  \brief Wake the LTC6804 from the sleep state
  
 Generic wakeup commannd to wake the LTC6804 from sleep
 *****************************************************/
void wakeup_sleep()
{
  LT6020_1_CS = 0;
  Delay(1); // Guarantees the LTC6804 will be in standby
  LT6020_1_CS = 1;
}
/*!**********************************************************
 \brief calaculates  and returns the CRC15
  

@param[in]  int len: the length of the data array being passed to the function
               
@param[in]  int data[] : the array of data that the PEC will be generated from
  

@return  The calculated pec15 as an unsigned int16_t
***********************************************************/
int pec15_calc(int len, int *data)
{
	int remainder,addr;
	
	remainder = 16;//initialize the PEC
	for(i = 0; i<len;i++) // loops for each byte in data array
	{
		addr = ((remainder>>7)^data[i])&0xff;//calculate PEC table address 
		remainder = (remainder<<8)^crc15Table[addr];
	}
	return(remainder*2);//The CRC15 has a 0 in the LSB so the remainder must be multiplied by 2
}


/*!
 \brief Writes an array of bytes out of the SPI port
 
 @param[in] int len length of the data array being written on the SPI port
 @param[in] int data[] the data array to be written on the SPI port
 
*/
void spi_write_array(int len, // Option: Number of bytes to be written on the SPI port
					 int data[] //Array of bytes to be written on the SPI port
					 )
{
  for(i = 0; i < len; i++)
  {
     SPI2_Exchange8bit((char)data[i]);
  }
}
/*!
 \brief Writes and read a set number of bytes using the SPI port.

@param[in] int tx_data[] array of data to be written on the SPI port
@param[in] int tx_len length of the tx_data array
@param[out] int rx_data array that read data will be written too. 
@param[in] int rx_len number of bytes to be read from the SPI port.

*/

void spi_write_read(int tx_Data[],//array of data to be written on SPI port 
					int tx_len, //length of the tx data arry
					int *rx_data,//Input: array that will store the data read by the SPI port
					int rx_len //Option: number of bytes to be read from the SPI port
					)
{
    
  for(i = 0; i < tx_len; i++)
  {
   rx_data[i] = SPI2_Exchange8bit(tx_Data[i]);

  }

//  for(int i = 0; i < rx_len; i++)
//  {
//    rx_data[i] = (int)spi_read(0xFF);
//  }

}

/*

void Setting_Config_Register(int GPIO, int Ref, int SWTRD, int ADCOPT, int VOV, int VUV, int Cell_Dis[], int DCTO) {
    int Cell_Discharge_Total = 0; // Total Value based on the array that is given
    int Cell_Num_MinusOne = 0; // Counter Variable
    
    // Calculating CELL_Discharge_Total
    while (Cell_Num_MinusOne < 12) {
        if (Cell_Dis[Cell_Num_MinusOne] == true) {
            switch (Cell_Num_MinusOne) {
                case 0:
                    Cell_Discharge_Total = Cell_Discharge_Total + Discharge_Cell_1;
                    break;
                case 1:
                    Cell_Discharge_Total = Cell_Discharge_Total + Discharge_Cell_2;
                    break;
                case 2:
                    Cell_Discharge_Total = Cell_Discharge_Total + Discharge_Cell_3;
                    break;
                case 3:
                    Cell_Discharge_Total = Cell_Discharge_Total + Discharge_Cell_4;
                    break;
                case 4:
                    Cell_Discharge_Total = Cell_Discharge_Total + Discharge_Cell_5;
                    break;
                case 5:
                    Cell_Discharge_Total = Cell_Discharge_Total + Discharge_Cell_6;
                    break;
                case 6:
                    Cell_Discharge_Total = Cell_Discharge_Total + Discharge_Cell_7;
                    break;
                case 7:
                    Cell_Discharge_Total = Cell_Discharge_Total + Discharge_Cell_8;
                    break;
                case 8:
                    Cell_Discharge_Total = Cell_Discharge_Total + Discharge_Cell_9;
                    break;
                case 9:
                    Cell_Discharge_Total = Cell_Discharge_Total + Discharge_Cell_10;
                    break;
                case 10:
                    Cell_Discharge_Total = Cell_Discharge_Total + Discharge_Cell_11;
                    break;
                case 11:
                    Cell_Discharge_Total = Cell_Discharge_Total + Discharge_Cell_12;
                    break;
            }

        }
        Cell_Num_MinusOne = Cell_Num_MinusOne + 1;
    }

    //Ref=REFON Cell_Dis[]= DCC[]]
     
    // Calaculating Each Register
    Config_Value[0]= GPIO+ Ref+SWTRD+ADCOPT;// First Register Look at table 36 of 680412fb for details.
    Config_Value[1]= VUV& 0xFF; // Ands with the First 8 bits
    Config_Value[2]= ((VUV & 0xF00)>> 8)+ ((VOV & 0x0F) <<4); // Finish Last bits of VUV start with VOV
    Config_Value[3]= (VOV& 0xFF0)>>4;       // Finish VOV setup
    Config_Value[4]= Cell_Discharge_Total& 0xFF; //First  8 Bits of DCC
    Config_Value[5]= ((Cell_Discharge_Total& 0xF00)>>8) + (DCTO<< 4); // Combined DCTO and the Last 4 bits of DCC
}   
*/




