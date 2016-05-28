
/**
  Section: Included Files
*/

#include <xc.h>
#include "memory.h"


/**
  Section: Flash Module APIs
*/

uint8_t FLASH_ReadByte(uint32_t flashAddr)
{
    TBLPTRU = (uint8_t)((flashAddr & 0x00FF0000) >> 16);
    TBLPTRH = (uint8_t)((flashAddr & 0x0000FF00)>> 8);
    TBLPTRL = (uint8_t)(flashAddr & 0x000000FF);

    asm("TBLRD");

    return (TABLAT);
}

uint16_t FLASH_ReadWord(uint32_t flashAddr)
{
    return ((((uint16_t)FLASH_ReadByte(flashAddr+1))<<8)|(FLASH_ReadByte(flashAddr)));
}

void FLASH_WriteByte(uint32_t flashAddr, uint8_t *flashRdBufPtr, uint8_t byte)
{
    uint32_t blockStartAddr = (uint32_t)(flashAddr & ((END_FLASH-1) ^ (ERASE_FLASH_BLOCKSIZE-1)));
    uint8_t offset = (uint8_t)(flashAddr & (ERASE_FLASH_BLOCKSIZE-1));
    uint8_t i;

    // Entire row will be erased, read and save the existing data
    for (i=0; i<ERASE_FLASH_BLOCKSIZE; i++)
    {
        flashRdBufPtr[i] = FLASH_ReadByte((blockStartAddr+i));
    }

    // Load byte at offset
    flashRdBufPtr[offset] = byte;

    // Writes buffer contents to current block
    FLASH_WriteBlock(blockStartAddr, flashRdBufPtr);
}

int8_t FLASH_WriteBlock(uint32_t writeAddr, uint8_t *flashWrBufPtr)
{
    uint32_t blockStartAddr  = (uint32_t )(writeAddr & ((END_FLASH-1) ^ (ERASE_FLASH_BLOCKSIZE-1)));
    uint8_t GIEBitValue = INTCONbits.GIE;     // Save interrupt enable
    uint8_t i;

    // Flash write must start at the beginning of a row
    if( writeAddr != blockStartAddr )
    {
        return -1;
    }

    // Block erase sequence
    FLASH_EraseBlock(writeAddr);

    // Block write sequence
    TBLPTRU = (uint8_t)((writeAddr & 0x00FF0000) >> 16);    // Load Table point register
    TBLPTRH = (uint8_t)((writeAddr & 0x0000FF00)>> 8);
    TBLPTRL = (uint8_t)(writeAddr & 0x000000FF);

    // Write block of data
    for (i=0; i<WRITE_FLASH_BLOCKSIZE; i++)
    {
        TABLAT = flashWrBufPtr[i];  // Load data byte

        if (i == (WRITE_FLASH_BLOCKSIZE-1))
        {
            asm("TBLWT");
        }
        else
        {
            asm("TBLWTPOSTINC");
        }
    }

    EECON1bits.EEPGD = 1;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    INTCONbits.GIE = 0; // Disable interrupts
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;  // Start program

    EECON1bits.WREN = 0;    // Disable writes to memory
    INTCONbits.GIE = GIEBitValue;   // Restore interrupt enable

    return 0;
}

void FLASH_EraseBlock(uint32_t baseAddr)
{
    uint8_t GIEBitValue = INTCONbits.GIE;   // Save interrupt enable

    TBLPTRU = (uint8_t)((baseAddr & 0x00FF0000) >> 16);
    TBLPTRH = (uint8_t)((baseAddr & 0x0000FF00)>> 8);
    TBLPTRL = (uint8_t)(baseAddr & 0x000000FF);

    EECON1bits.EEPGD = 1;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    EECON1bits.FREE = 1;
    INTCONbits.GIE = 0; // Disable interrupts
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    INTCONbits.GIE = GIEBitValue;   // Restore interrupt enable
}

/**
  Section: Data EEPROM Module APIs
*/

void DATAEE_WriteByte(uint8_t bAdd, uint8_t bData)
{
    uint8_t GIEBitValue = INTCONbits.GIE;

    EEADR = (bAdd & 0xFF);
    EEDATA = bData;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    INTCONbits.GIE = 0;     // Disable interrupts
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    // Wait for write to complete
    while (EECON1bits.WR)
    {
    }

    EECON1bits.WREN = 0;
    INTCONbits.GIE = GIEBitValue;   // Restore interrupt enable
}

uint8_t DATAEE_ReadByte(uint8_t bAdd)
{
    EEADR = (bAdd & 0xFF);
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 0;
    EECON1bits.RD = 1;
    NOP();  // NOPs may be required for latency at high frequencies
    NOP();

    return (EEDATA);
}
/**
 End of File
*/