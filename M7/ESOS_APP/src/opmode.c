/*
* Author: Josh White
* Date: 4/5/2023
*
* Abstract: This file contains the function defintions for the opmode
*    selection system.
*
*
*
* Revisions:
* 01jw - 4/5/2023 - Initial version
* 02ks - 4/5/2023 - Implement defines in fnst_opmodePriority
*/

#include "opmode.h"


// Updates the opmode struct values
void fnst_opmodeUpdate(st_opmode volatile *pst_opmode, bool b_SW1, bool b_SW2, bool b_SW3, bool b_SW4, bool b_SW5) {
    // Read the switches via defines in main header file
    pst_opmode->b_SW1 = b_SW1;
    pst_opmode->b_SW2 = b_SW2;
    pst_opmode->b_SW3 = b_SW3;
    pst_opmode->b_SW4 = b_SW4;
    pst_opmode->b_SW5 = b_SW5;
}

// Initialize the opmode struct values
void fnst_opmodeInit(st_opmode volatile *pst_opmode) {
    pst_opmode->b_SW1 = false;
    pst_opmode->b_SW2 = false;
    pst_opmode->b_SW3 = false;
    pst_opmode->b_SW4 = false;
    pst_opmode->b_SW5 = false;
}

// Return the highest priority operation.
uint8_t fnst_opmodePriority(st_opmode volatile *pst_opmode) {
    if      (pst_opmode->b_SW1 != 0)   return OPMODE_KEYBOARD; // priority via SW1
    else if (pst_opmode->b_SW2 != 0)   return OPMODE_RM_NON_ALPHA; // downwards
    else if (pst_opmode->b_SW3 != 0)   return OPMODE_TO_UPPER;
    else if (pst_opmode->b_SW4 != 0)   return OPMODE_ENCRYPT;
    else if (pst_opmode->b_SW5 != 0)   return OPMODE_DECRYPT;
    else                                return OPMODE_ECHO; // default
}