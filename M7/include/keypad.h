/*
* Author: Keaton Shelton
* Date: 4/5/2023
*
* Abstract: This is the header file for keypad.c, which contains the logic needed to 
*           read the keypad and return the value of the key pressed.
*
*
*
*
* Revisions:
* 01ks - 4/5/2023 - Initial version
* 02ks - 4/23/2023 - Finalize
*/
#ifndef KEYPAD_H
#define KEYPAD_H
//************ I N C L U D E S ************
#include "ptb.h"
//
//
//
//
//************ D E F I N E S ************
//Key Offsets
#define KEYPAD_KEY0_OFFSET    0b0000000000000000
#define KEYPAD_KEY1_OFFSET    0b0000000000000001
#define KEYPAD_KEY2_OFFSET    0b0000000000000010
#define KEYPAD_KEY3_OFFSET    0b0000000000000011
#define KEYPAD_KEY4_OFFSET    0b0000000000000100
#define KEYPAD_KEY5_OFFSET    0b0000000000000101
#define KEYPAD_KEY6_OFFSET    0b0000000000000110
#define KEYPAD_KEY7_OFFSET    0b0000000000000111
#define KEYPAD_KEY8_OFFSET    0b0000000000001000
#define KEYPAD_KEY9_OFFSET    0b0000000000001001
#define KEYPAD_KEYA_OFFSET    0b0000000000001010
#define KEYPAD_KEYB_OFFSET    0b0000000000001011
#define KEYPAD_KEYC_OFFSET    0b0000000000001100
#define KEYPAD_KEYD_OFFSET    0b0000000000001101
#define KEYPAD_KEYHASH_OFFSET 0b0000000000001110
#define KEYPAD_KEYSTAR_OFFSET 0b0000000000001111

//Row Offsets
#define KEYPAD_ROW0_OFFSET 0b0000000000001000
#define KEYPAD_ROW1_OFFSET 0b0000000000001001
#define KEYPAD_ROW2_OFFSET 0b0000000000001010
#define KEYPAD_ROW3_OFFSET 0b0000000000001011

//Key Masks (for bitwise operations)
#define KEYPAD_KEY0_MASK    0b0000000000000001
#define KEYPAD_KEY1_MASK    0b0000000000000010
#define KEYPAD_KEY2_MASK    0b0000000000000100
#define KEYPAD_KEY3_MASK    0b0000000000001000
#define KEYPAD_KEY4_MASK    0b0000000000010000
#define KEYPAD_KEY5_MASK    0b0000000000100000
#define KEYPAD_KEY6_MASK    0b0000000001000000
#define KEYPAD_KEY7_MASK    0b0000000010000000
#define KEYPAD_KEY8_MASK    0b0000000100000000
#define KEYPAD_KEY9_MASK    0b0000001000000000
#define KEYPAD_KEYA_MASK    0b0000010000000000
#define KEYPAD_KEYB_MASK    0b0000100000000000
#define KEYPAD_KEYC_MASK    0b0001000000000000
#define KEYPAD_KEYD_MASK    0b0010000000000000
#define KEYPAD_KEYHASH_MASK 0b0100000000000000
#define KEYPAD_KEYSTAR_MASK 0b1000000000000000
//
//
//
//
//************ P R O T O T Y P E S ************
//Dr. Bruce' provided delay function
void delay(uint16_t u16t_delay);

//This function reads the keypad and returns a uint16_t containing the value of the key pressed by bitwise placement.
uint16_t keypad_entry(void);

//Interpret the uint16_t value from the keypad and return direct value, meant to be used with the keypad_entry() function
uint8_t keypad_interpret(uint16_t u16t_keyVals);

#endif