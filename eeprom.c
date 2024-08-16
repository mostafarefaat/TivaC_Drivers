/**********************************************************************************************
 *
 * Module: GPIO
 *
 * File Name: GPIO.c
 *
 * Description: Source file for the TM4C123GH6PM DIO driver for TivaC Built-in Buttons and LEDs
 *
 * Author: Edges for Training Team
 *
 ***********************************************************************************************/
#include "eeprom.h"

#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 369

void Delay_MS(unsigned long long n)
{
    volatile unsigned long long count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n) );
}

static void _EEPROMWaitForDone(void)
{
    //
    // Is the EEPROM still busy?
    //
    while(Read_Port((volatile uint32 *)EEPROM_EEDONE) & EEPROM_EEDONE_WORKING)
    {
        //
        // Spin while EEPROM is busy.
        //
    }
}

uint32 EEPROMInit(void){

    uint32 ui32Status = 0;

    /* Enable clock for EEPROM and wait for clock to start */
    SET_BIT(SYSCTL_RCGCEEPROM_REG,PIN0);
    //while(!(SYSCTL_PREEPROM_REG & 0x01));
    //
    // Insert a small delay (6 cycles + call overhead) to guard against the
    // possibility that this function is called immediately after the EEPROM
    // peripheral is enabled.  Without this delay, there is a slight chance
    // that the first EEPROM register read will fault if you are using a
    // compiler with a ridiculously good optimizer!
    //
    Delay_MS(2);
    //
    // Make sure the EEPROM has finished any ongoing processing.
    //
    _EEPROMWaitForDone();
    //
    // Read the EESUPP register to see if any errors have been reported.
    //
    ui32Status = Read_Port((volatile uint32 *)EEPROM_EESUPP);
    //
    // Did an error of some sort occur during initialization?
    //
    if(ui32Status & (EEPROM_EESUPP_PRETRY | EEPROM_EESUPP_ERETRY))
    {
        return(EEPROM_INIT_ERROR);
    }
    //
    // Perform a second EEPROM reset.
    //
    Write_Pin((volatile uint32 *)SYSCTL_PERIPH_EEPROM0, PIN0, LOGIC_HIGH);
    Delay_MS(1);
    Write_Pin((volatile uint32 *)SYSCTL_PERIPH_EEPROM0, PIN0, LOGIC_LOW);
    //
    // Wait for the EEPROM to complete its reset processing once again.
    //
    Delay_MS(2);
    _EEPROMWaitForDone();

    //
    // Read EESUPP once again to determine if any error occurred.
    //
    ui32Status = Read_Port((volatile uint32 *)EEPROM_EESUPP);
    //
    // Was an error reported following the second reset?
    //
    if(ui32Status & (EEPROM_EESUPP_PRETRY | EEPROM_EESUPP_ERETRY))
    {
        return(EEPROM_INIT_ERROR);
    }
    //
    // The EEPROM does not indicate that any error occurred.
    //
    return(EEPROM_INIT_OK);
}

void EEPROMRead(uint32 *pui32Data, uint32 ui32Address, uint32 ui32Count)
{
    //
    // Set the block and offset appropriately to read the first word.
    //
    (*(volatile uint32 *)EEPROM_EEBLOCK)  = EEPROMBlockFromAddr(ui32Address);
    (*(volatile uint32 *)EEPROM_EEOFFSET) =  OFFSET_FROM_ADDR(ui32Address);
    //
    // Convert the byte count to a word count.
    //
    ui32Count /= 4;
    //
    // Read each word in turn.
    //
    while(ui32Count)
    {
        //
        // Read the next word through the autoincrementing register.
        //
        *pui32Data = Read_Port((volatile uint32 *)EEPROM_EERDWRINC);
        //
        // Move on to the next word.
        //
        pui32Data++;
        ui32Count--;
        //

    }
}

uint32 EEPROMProgram(uint32 *pui32Data, uint32 ui32Address, uint32 ui32Count)
{
    uint32 ui32Status;

    //
    // Make sure the EEPROM is idle before we start.
    //
    do
    {
        //
        // Read the status.
        //
        ui32Status = Read_Port((volatile uint32 *)EEPROM_EESUPP);
    }
    while(ui32Status & EEPROM_EEDONE_WORKING);

    //
    // Set the block and offset appropriately to program the first word.
    //
    (*(volatile uint32 *)EEPROM_EEBLOCK)  = EEPROMBlockFromAddr(ui32Address);
    (*(volatile uint32 *)EEPROM_EEOFFSET) =  OFFSET_FROM_ADDR(ui32Address);
    //
    // Convert the byte count to a word count.
    //
    ui32Count /= 4;
    //
    // Write each word in turn.
    //
    while(ui32Count)
    {
        //
        // Write the next word through the autoincrementing register.
        //
        *(volatile uint32 *)EEPROM_EERDWRINC = *pui32Data;

        //
        // Wait a few cycles.  In some cases, the WRBUSY bit is not set
        // immediately and this prevents us from dropping through the polling
        // loop before the bit is set.
        //
        Delay_MS(1);
        //
        // Wait for the write to complete.
        //
        do
        {
            //
            // Read the status.
            //
            ui32Status = Read_Port((volatile uint32 *)EEPROM_EESUPP);
        }
        while(ui32Status & EEPROM_EEDONE_WORKING);
        //
        // Make sure we completed the write without errors.  Note that we
        // must check this per-word because write permission can be set per
        // block resulting in only a section of the write not being performed.
        //
        if(ui32Status & EEPROM_EEDONE_NOPERM)
        {
            while(1){

            }
        }

        //
        // Move on to the next word.
        //
        pui32Data++;
        ui32Count--;
    }
    //
    // Return the current status to the caller.
    //
    return(*(volatile uint32 *)EEPROM_EEDONE);
}


