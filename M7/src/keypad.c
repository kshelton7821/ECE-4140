/*
* Author: Keaton Shelton
* Date: 4/5/2023
*
* Abstract: This is keypad.c, which contains the logic needed to 
*           read the keypad and return the value of the key pressed.
*
*
*
*
* Revisions:
* 01ks - 4/5/2023 - Initial version
*/
//**************** I N C L U D E S ****************
#include "keypad.h"

//**************** D E F I N E S ****************
//This function reads the keypad and returns a uint16_t containing the value of the key pressed by bitwise placement.
uint16_t keypad_entry(void)
{
    /*
    * keypad_entry(void) Abstract:
    *  This function reads the keypad and returns a uint16_t containing the value of the key pressed by bitwise placement.
    *  Function will start off with a uint16_t value of 0b0000000000000000. With each bit representing a key on the keypad.
    *  The function will then go through each column and row, setting the corresponding column high and the rest to low and reading the data from the rows.
    *  The correct bit will be set by reading the data from the row and right shifted by the row pin number. After shifting right by the
    *  row pin number to get the bit to the Lsb position, the bit will then be left shifted by the key bit offset to move the bit into the correct bitwise position.
    *  The uint16_t value will then be OR'd with the new bit to set the bit in the correct position until all keys have been covered.
    *  The function will then return the uint16_t value.
    * 
    *  Bitwise placement of keys from Lsb to Msb:
    *  Bits 0-9: 0-9, Bits 10-15: A, B, C, D, #, *
    * 
    *  Example: READ Key 4
    *       (uint16_t)    = (gpio_get(EDUB_KEYPAD_ROW1_PORT, EDUB_KEYPAD_ROW1_PIN) >> KEYPAD_ROW1_OFFSET[8]) << KEYPAD_KEY4_OFFSET[4] => uint16_t w/ bit 4 set
    *  0b0000000000000000 = (0b0000000100000000 >> KEYPAD_ROW1_OFFSET[8]) << KEYPAD_KEY4_OFFSET[4] => 0b0000000000010000
    */

   uint16_t u16t_keyVals = 0b0000000000000000;

    //*********** C O L U M N 0 ***********
    //Disable all columns but Column 0
    EDUB_KEYPAD_COL0_CLEAR();
    EDUB_KEYPAD_COL1_CLEAR();
    EDUB_KEYPAD_COL2_CLEAR();
    EDUB_KEYPAD_COL3_CLEAR();

    //Enable Column 0
    EDUB_KEYPAD_COL0_SET();

    //Small Delay to rid of voltage transients
    delay(50);

    //Read Keys: 1, 4, 7, *
    u16t_keyVals |= (EDUB_KEY1_GETVAL() >> KEYPAD_ROW0_OFFSET) << KEYPAD_KEY1_OFFSET;
    u16t_keyVals |= (EDUB_KEY4_GETVAL() >> KEYPAD_ROW1_OFFSET) << KEYPAD_KEY4_OFFSET;
    u16t_keyVals |= (EDUB_KEY7_GETVAL() >> KEYPAD_ROW2_OFFSET) << KEYPAD_KEY7_OFFSET;
    u16t_keyVals |= (EDUB_KEYSTAR_GETVAL() >> KEYPAD_ROW3_OFFSET) << KEYPAD_KEYSTAR_OFFSET;


    //*********** C O L U M N 1 ***********
    //Disable all columns but Column 1
    EDUB_KEYPAD_COL0_CLEAR();
    EDUB_KEYPAD_COL1_CLEAR();
    EDUB_KEYPAD_COL2_CLEAR();
    EDUB_KEYPAD_COL3_CLEAR();

    //Enable Column 1
    EDUB_KEYPAD_COL1_SET();

    //Small Delay to rid of voltage transients
    delay(50);

    //Read Keys: 2, 5, 8, 0
    u16t_keyVals |= (EDUB_KEY2_GETVAL() >> KEYPAD_ROW0_OFFSET) << KEYPAD_KEY2_OFFSET;
    u16t_keyVals |= (EDUB_KEY5_GETVAL() >> KEYPAD_ROW1_OFFSET) << KEYPAD_KEY5_OFFSET;
    u16t_keyVals |= (EDUB_KEY8_GETVAL() >> KEYPAD_ROW2_OFFSET) << KEYPAD_KEY8_OFFSET;
    u16t_keyVals |= (EDUB_KEY0_GETVAL() >> KEYPAD_ROW3_OFFSET) << KEYPAD_KEY0_OFFSET;


    //*********** C O L U M N 2 ***********
    //Disable all columns but Column 2
    EDUB_KEYPAD_COL0_CLEAR();
    EDUB_KEYPAD_COL1_CLEAR();
    EDUB_KEYPAD_COL2_CLEAR();
    EDUB_KEYPAD_COL3_CLEAR();

    //Enable Column 2
    EDUB_KEYPAD_COL2_SET();

    //Small Delay to rid of voltage transients
    delay(50);

    //Read Keys: 3, 6, 9, #
    u16t_keyVals |= (EDUB_KEY3_GETVAL() >> KEYPAD_ROW0_OFFSET) << KEYPAD_KEY3_OFFSET;
    u16t_keyVals |= (EDUB_KEY6_GETVAL() >> KEYPAD_ROW1_OFFSET) << KEYPAD_KEY6_OFFSET;
    u16t_keyVals |= (EDUB_KEY9_GETVAL() >> KEYPAD_ROW2_OFFSET) << KEYPAD_KEY9_OFFSET;
    u16t_keyVals |= (EDUB_KEYPOUND_GETVAL() >> KEYPAD_ROW3_OFFSET) << KEYPAD_KEYHASH_OFFSET;


    //*********** C O L U M N 3 ***********
    //Disable all columns but Column 3
    EDUB_KEYPAD_COL0_CLEAR();
    EDUB_KEYPAD_COL1_CLEAR();
    EDUB_KEYPAD_COL2_CLEAR();
    EDUB_KEYPAD_COL3_CLEAR();

    //Enable Column 3
    EDUB_KEYPAD_COL3_SET();

    //Small Delay to rid of voltage transients
    delay(50);

    //Read Keys: A, B, C, D
    u16t_keyVals |= (EDUB_KEYA_GETVAL() >> KEYPAD_ROW0_OFFSET) << KEYPAD_KEYA_OFFSET;
    u16t_keyVals |= (EDUB_KEYB_GETVAL() >> KEYPAD_ROW1_OFFSET) << KEYPAD_KEYB_OFFSET;
    u16t_keyVals |= (EDUB_KEYC_GETVAL() >> KEYPAD_ROW2_OFFSET) << KEYPAD_KEYC_OFFSET;
    u16t_keyVals |= (EDUB_KEYD_GETVAL() >> KEYPAD_ROW3_OFFSET) << KEYPAD_KEYD_OFFSET;

    //Set Columns to hight state
    EDUB_KEYPAD_COL0_SET();
    EDUB_KEYPAD_COL1_SET();
    EDUB_KEYPAD_COL2_SET();
    EDUB_KEYPAD_COL3_SET();

    //Return the uint16_t value
    return u16t_keyVals;
}

//Dr. Bruce's provided delay function
void delay(uint16_t delay)
{
    uint16_t i;
    for (i = 0; i < delay; i++)
    {
        __asm__("nop");
    }
}

//Interpret the uint16_t value from the keypad and return direct value, meant to be used with the keypad_entry() function
char keypad_interpret(uint16_t u16t_keyVals)
{
    if (u16t_keyVals == 0b0000000000000000)
    {
        return ' ';
    }
    else if ((u16t_keyVals & KEYPAD_KEY0_MASK) == KEYPAD_KEY0_MASK)
    {
        return '0';
    }
    else if ((u16t_keyVals & KEYPAD_KEY1_MASK) == KEYPAD_KEY1_MASK)
    {
        return '1';
    }
    else if ((u16t_keyVals & KEYPAD_KEY2_MASK) == KEYPAD_KEY2_MASK)
    {
        return '2';
    }
    else if ((u16t_keyVals & KEYPAD_KEY3_MASK) == KEYPAD_KEY3_MASK)
    {
        return '3';
    }
    else if ((u16t_keyVals & KEYPAD_KEY4_MASK) == KEYPAD_KEY4_MASK)
    {
        return '4';
    }
    else if ((u16t_keyVals & KEYPAD_KEY5_MASK) == KEYPAD_KEY5_MASK)
    {
        return '5';
    }
    else if ((u16t_keyVals & KEYPAD_KEY6_MASK) == KEYPAD_KEY6_MASK)
    {
        return '6';
    }
    else if ((u16t_keyVals & KEYPAD_KEY7_MASK) == KEYPAD_KEY7_MASK)
    {
        return '7';
    }
    else if ((u16t_keyVals & KEYPAD_KEY8_MASK) == KEYPAD_KEY8_MASK)
    {
        return '8';
    }
    else if ((u16t_keyVals & KEYPAD_KEY9_MASK) == KEYPAD_KEY9_MASK)
    {
        return '9';
    }
    else if ((u16t_keyVals & KEYPAD_KEYA_MASK) == KEYPAD_KEYA_MASK)
    {
        return 'A';
    }
    else if ((u16t_keyVals & KEYPAD_KEYB_MASK) == KEYPAD_KEYB_MASK)
    {
        return 'B';
    }
    else if ((u16t_keyVals & KEYPAD_KEYC_MASK) == KEYPAD_KEYC_MASK)
    {
        return 'C';
    }
    else if ((u16t_keyVals & KEYPAD_KEYD_MASK) == KEYPAD_KEYD_MASK)
    {
        return 'D';
    }
    else if ((u16t_keyVals & KEYPAD_KEYHASH_MASK) == KEYPAD_KEYHASH_MASK)
    {
        return '#';
    }
    else if ((u16t_keyVals & KEYPAD_KEYSTAR_MASK) == KEYPAD_KEYSTAR_MASK)
    {
        return '*';
    }
}
